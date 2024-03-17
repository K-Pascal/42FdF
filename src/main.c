/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/02 17:14:04 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

#include <unistd.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysymdef.h>

#include "minilibx-linux/mlx.h"

#include "libft/libft.h"

#include "parser.h"
#include "typedefs.h"
#include "utils.h"
#include "draw_line.h"

int	close_mlx(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img.ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win.ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		close_mlx(fdf);
	}
	if (keycode == 'a')
	{
		ft_putendl_fd("test", STDOUT_FILENO);
	}
	return (0);
}

#include <math.h>

t_vec3	rotate_x(t_vec3 point3d, double angle)
{
	t_vec3	rotated;

	rotated.x = point3d.x;
	rotated.y = (int)((double)point3d.y * cos(angle) + (double)point3d.z * sin(angle));
	rotated.z = (int)(-(double)point3d.y * sin(angle) + (double)point3d.z * cos(angle));
	return (rotated);
}

t_vec3	rotate_y(t_vec3 point3d, double angle)
{
	t_vec3	rotated;

	rotated.x = (int)((double)point3d.x * cos(angle) - (double)point3d.z * sin(angle));
	rotated.y = point3d.y;
	rotated.z = (int)((double)point3d.x * sin(angle) + (double)point3d.z * cos(angle));
	return (rotated);
}

t_vec3	rotate_z(t_vec3 point3d, double angle)
{
	t_vec3	rotated;

	rotated.x = (int)((double)point3d.x * cos(angle) - (double)point3d.y * sin(angle));
	rotated.y = (int)((double)point3d.x * sin(angle) + (double)point3d.y * cos(angle));
	rotated.z = point3d.z;
	return (rotated);
}

t_vec2	orthographic_projection(t_vec2 pos, t_vec3 point3d)
{
	t_vec2	projection;

	projection.x = pos.x + point3d.x;
	projection.y = pos.y + point3d.y;
	return (projection);
}

t_vec2	isometric_projection(t_vec2 pos, t_vec3 point3d)
{
	double const	angle_x = asin(tan(M_PI / 6));
	double const	angle_y = M_PI / 4;

	return (orthographic_projection(pos, rotate_x(rotate_y(point3d, angle_y), angle_x)));
}


void	draw_cube(t_fdf *fdf, t_vec2 pos, int length)
{
	t_vec3	points[8];

	points[0].x = -length;
	points[0].y = -length;
	points[0].z = -length;

	points[1].x = +length;
	points[1].y = -length;
	points[1].z = -length;

	points[2].x = +length;
	points[2].y = +length;
	points[2].z = -length;

	points[3].x = -length;
	points[3].y = +length;
	points[3].z = -length;

	points[4].x = -length;
	points[4].y = -length;
	points[4].z = +length;

	points[5].x = +length;
	points[5].y = -length;
	points[5].z = +length;

	points[6].x = +length;
	points[6].y = +length;
	points[6].z = +length;

	points[7].x = -length;
	points[7].y = +length;
	points[7].z = +length;

	t_vec3	centroid = {0, 0, 0};
	for (int i = 0; i < 8; i++)
	{
		centroid.x += points[i].x;
		centroid.y += points[i].y;
		centroid.z += points[i].z;
	}
	centroid.x /= 8;
	centroid.y /= 8;
	centroid.z /= 8;

	t_vec2	projected[8];
	for (double angle = 0.0; angle < 2 * M_PI; angle += M_PI / 8)
	{
		for (int i = 0; i < 8; i++)
		{
			//points[i].x -= centroid.x;
			//points[i].y -= centroid.y;
			//points[i].z -= centroid.z;
			//projected[i] = isometric_projection(pos, points[i]);
			t_vec3	rotated = rotate_y(points[i], angle);
			projected[i] = orthographic_projection(pos, rotated);
			//projected[i] = orthographic_projection(pos, points[i]);
			//points[i].x += centroid.x;
			//points[i].y += centroid.y;
			//points[i].z += centroid.z;
		}
		for (int i = 0; i < 8; i++)
		{
			if ((i + 1) % 4 != 0)
				draw_line(&fdf->img, &projected[i], &projected[i + 1]);
			else
				draw_line(&fdf->img, &projected[i], &projected[4 * (i / 4)]);
			if (i < 4)
				draw_line(&fdf->img, &projected[i], &projected[i + 4]);
		}
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
		sleep(1);
		mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
		ft_memset(fdf->img.data, 0, fdf->img.size_line * fdf->img.height);
	}
}


#include <stdio.h>
void	draw_box(t_img *img)
{
	t_vec2	points[4] = {
		{0, 0},
		{0, img->height - 1},
		{img->width - 1, img->height - 1},
		{img->width - 1, 0}};

	for (int i = 0; i < 3; i++)
		draw_line(img, &points[i], &points[i + 1]);
	draw_line(img, &points[3], &points[0]);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_info	info;
	int		*arr_ints;

	if (argc < 2)
		return (EXIT_FAILURE);
	info.num_lines = 0;
	info.num_values = 0;
	arr_ints = get_map(argv[1], &info);
	printf("%zu, %zu\n", info.num_lines, info.num_values);
	fdf.mlx_ptr = mlx_init();
	mlx_get_screen_size(fdf.mlx_ptr, &fdf.win.width, &fdf.win.height);
	fdf.win.ptr = mlx_new_window(fdf.mlx_ptr, fdf.win.width, fdf.win.height, "test");
	fdf.img.width = fdf.win.width;
	fdf.img.height = fdf.win.height;
	fdf.img.ptr = mlx_new_image(fdf.mlx_ptr, fdf.img.width, fdf.img.height);
	fdf.img.data = mlx_get_data_addr(fdf.img.ptr, &fdf.img.bits_per_pixel, &fdf.img.size_line, &fdf.img.endian);
	printf("%d %d %d\n", fdf.img.bits_per_pixel, fdf.img.size_line, fdf.img.endian);

	draw_box(&fdf.img);
	t_vec2	pos = {fdf.img.width / 2, fdf.img.height / 2};
	//draw_cube(&fdf, pos, 50);
	//pos.x = 300;
//	draw_cube(&fdf, pos, 50);
	t_vec3	c = {((info.num_values - 1) * (fdf.img.width / 2 / info.num_values)) / 2,
	   ((info.num_lines - 1) * (fdf.img.height / 2 / info.num_lines)) / 2,
	   0};

	t_vec2	*last_row = malloc(info.num_values * sizeof(last_row));
	for (size_t i = 0; i < info.num_lines; i++)
	{
		t_vec2	last;
		for (size_t j = 0; j < info.num_values; j++)
		{
			t_vec3 point3d = {
				j * (fdf.img.width / 2 / info.num_values) - c.x,
				i * (fdf.img.height / 2 / info.num_lines) - c.y,
				arr_ints[i * info.num_values + j] * min(fdf.img.width / info.num_values, fdf.img.height / info.num_lines) / 10
			};
			//t_vec3 rotated = rotate_z(point3d, M_PI / 4);
			//rotated = rotate_y(rotated, M_PI / 6);
			//rotated = rotate_z(rotated, M_PI / 6);
			t_vec2 projection = isometric_projection(pos, point3d);
			//t_vec2 projection = isometric_projection(pos, rotated);
			//t_vec2 projection = orthographic_projection(pos, rotated);
			if (j)
				draw_line(&fdf.img, &last, &projection);
			if (i)
				draw_line(&fdf.img, &last_row[j], &projection);
			last = projection;
			last_row[j] = last;
		}
	}
	free(last_row);
	free(arr_ints);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win.ptr, fdf.img.ptr, 0, 0);
	mlx_hook(fdf.win.ptr, KeyPress, KeyPressMask, &key_pressed, &fdf);
	mlx_hook(fdf.win.ptr, DestroyNotify, NoEventMask, &close_mlx, &fdf);
	mlx_loop(fdf.mlx_ptr);
	mlx_destroy_image(fdf.mlx_ptr, fdf.img.ptr);
	mlx_destroy_window(fdf.mlx_ptr, fdf.win.ptr);
	mlx_destroy_display(fdf.mlx_ptr);
	free(fdf.mlx_ptr);
	return (0);
}