/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/08 14:09:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysymdef.h>

#include "minilibx-linux/mlx.h"

#include "libft/libft.h"

#include "draw_line.h"
#include "parser.h"
#include "projections.h"
#include "typedefs.h"
#include "utils.h"

void	render_isometric(t_fdf *fdf)
{
	int		i;
	int		j;
	t_vec3	c;
	int		scale_x;
	int		scale_y;

	if ((fdf->img.width >> 1) <= fdf->map.num_values)
		scale_x = 1;
	else
		scale_x = ((fdf->img.width >> 1) / fdf->map.num_values);
	if ((fdf->img.height >> 1) <= fdf->map.num_lines)
		scale_y = 1;
	else
		scale_y = ((fdf->img.height >> 1) / fdf->map.num_lines);
	c.x = ((fdf->map.num_values - 1) * scale_x) / 2;
	c.y = ((fdf->map.num_lines - 1) * scale_y) / 2;
	c.z = 0;
	t_vec2	*last_row = malloc(fdf->map.num_values * sizeof(*last_row));
	if (last_row == NULL)
		return ;
	i = 0;
	while (i < fdf->map.num_lines)
	{
		t_vec2	last;
		j = 0;
		while (j < fdf->map.num_values)
		{
			t_vec3 point3d = {
				j * scale_x - c.x,
				i * scale_y - c.y,
				fdf->map.altitudes[i * fdf->map.num_values + j] * fdf->map.z_normalize
				//fdf->map.altitudes[i * fdf->map.num_values + j] * min(fdf->img.width / fdf->map.num_values, fdf->img.height / fdf->map.num_lines) / fdf->map.z_normalize
			};
			t_vec2 projection = isometric_projection(fdf->map.pos, point3d, &fdf->map);
			if (j)
				draw_line(&fdf->img, last, projection, 0xFF808080 + (point3d.z % 0xFF << 8));
			if (i)
				draw_line(&fdf->img, last_row[j], projection, 0xFF808080 + (point3d.z % 0xFF << 8));
			last = projection;
			last_row[j] = last;
			j++;
		}
		i++;
	}
	free(last_row);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
}

void	reset_map(t_fdf *fdf)
{
	ft_memset(fdf->img.data, 0, fdf->img.size_line * fdf->img.height);
	mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == XK_Escape)
		mlx_loop_end(fdf->mlx_ptr);
	else if (keycode == '0')
	{
		reset_map(fdf);
		fdf->map.table.x = 0;
		fdf->map.table.y = 0;
		render_isometric(fdf);
	}
	else if (keycode == 'd')
	{
		fdf->map.pos.x += fdf->map.translation_offset;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == 'a')
	{
		fdf->map.pos.x -= fdf->map.translation_offset;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == 'w')
	{
		fdf->map.pos.y -= fdf->map.translation_offset;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == 's')
	{
		fdf->map.pos.y += fdf->map.translation_offset;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == XK_Right)
	{
		fdf->map.table.y--;
		if (fdf->map.table.y < 0)
			fdf->map.table.y = SIZE_TRIGO_TABLE - 1;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == XK_Left)
	{
		fdf->map.table.y++;
		if (fdf->map.table.y >= SIZE_TRIGO_TABLE)
			fdf->map.table.y = 0;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == XK_Up)
	{
		fdf->map.table.x--;
		if (fdf->map.table.x < 0)
			fdf->map.table.x = SIZE_TRIGO_TABLE - 1;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == XK_Down)
	{
		fdf->map.table.x++;
		if (fdf->map.table.x >= SIZE_TRIGO_TABLE)
			fdf->map.table.x = 0;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == '-')
	{
		fdf->map.z_normalize -= 2;
		if (!fdf->map.z_normalize)
			fdf->map.z_normalize = -1;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == '=')
	{
		fdf->map.z_normalize += 2;
		if (!fdf->map.z_normalize)
			fdf->map.z_normalize = 1;
		reset_map(fdf);
		render_isometric(fdf);
	}
	return (0);
}

//void	draw_cube(t_fdf *fdf, t_vec2 pos, int length)
//{
//	t_vec3	points[8];
//
//	points[0].x = -length;
//	points[0].y = -length;
//	points[0].z = -length;
//
//	points[1].x = +length;
//	points[1].y = -length;
//	points[1].z = -length;
//
//	points[2].x = +length;
//	points[2].y = +length;
//	points[2].z = -length;
//
//	points[3].x = -length;
//	points[3].y = +length;
//	points[3].z = -length;
//
//	points[4].x = -length;
//	points[4].y = -length;
//	points[4].z = +length;
//
//	points[5].x = +length;
//	points[5].y = -length;
//	points[5].z = +length;
//
//	points[6].x = +length;
//	points[6].y = +length;
//	points[6].z = +length;
//
//	points[7].x = -length;
//	points[7].y = +length;
//	points[7].z = +length;
//
//	t_vec3	centroid = {0, 0, 0};
//	for (int i = 0; i < 8; i++)
//	{
//		centroid.x += points[i].x;
//		centroid.y += points[i].y;
//		centroid.z += points[i].z;
//	}
//	centroid.x /= 8;
//	centroid.y /= 8;
//	centroid.z /= 8;
//
//	t_vec2	projected[8];
//	for (float angle = 0.0; angle < 2 * M_PI; angle += M_PI / 8)
//	{
//		for (int i = 0; i < 8; i++)
//		{
//			//points[i].x -= centroid.x;
//			//points[i].y -= centroid.y;
//			//points[i].z -= centroid.z;
//			//projected[i] = isometric_projection(pos, points[i]);
//			t_vec3	rotated = rotate_y(points[i], angle);
//			projected[i] = orthographic_projection(pos, rotated);
//			//projected[i] = orthographic_projection(pos, points[i]);
//			//points[i].x += centroid.x;
//			//points[i].y += centroid.y;
//			//points[i].z += centroid.z;
//		}
//		for (int i = 0; i < 8; i++)
//		{
//			if ((i + 1) % 4 != 0)
//				draw_line(&fdf->img, projected[i], projected[i + 1]);
//			else
//				draw_line(&fdf->img, projected[i], projected[4 * (i / 4)]);
//			if (i < 4)
//				draw_line(&fdf->img, projected[i], projected[i + 4]);
//		}
//		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
//		sleep(1);
//		mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
//		ft_memset(fdf->img.data, 0, fdf->img.size_line * fdf->img.height);
//	}
//}

char	start_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (0);
	mlx_get_screen_size(fdf->mlx_ptr, &fdf->win.width, &fdf->win.height);
	fdf->win.ptr = mlx_new_window(fdf->mlx_ptr, fdf->win.width, fdf->win.height, "FdF");
	if (fdf->win.ptr == NULL)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		return (0);
	}
	fdf->img.width = fdf->win.width;
	fdf->img.height = fdf->win.height;
	fdf->img.ptr = mlx_new_image(fdf->mlx_ptr, fdf->img.width, fdf->img.height);
	if (fdf->img.ptr == NULL)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win.ptr);
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		return (0);
	}
	return (1);
}

void	init_prog(t_fdf *fdf, char pathname[])
{
	fdf->map.num_lines = 0;
	fdf->map.num_values = 0;
	get_mapinfo(&fdf->map, pathname);
	fdf->map.altitudes = malloc(fdf->map.num_lines * fdf->map.num_values * sizeof(int));
	if (fdf->map.altitudes == NULL)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	if (!get_mapdata(&fdf->map, pathname))
	{
		free(fdf->map.altitudes);
		exit(EXIT_FAILURE);
	}
	if (!start_mlx(fdf))
	{
		ft_putendl_fd("Failed to initialize mlx", STDERR_FILENO);
		free(fdf->map.altitudes);
		exit(EXIT_FAILURE);
	}
	fdf->img.data = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bytes_per_pixel,
			&fdf->img.size_line, &fdf->img.endian);
	fdf->img.bytes_per_pixel >>= 3;
	init_trigo_table(&fdf->map.table);
}

void	deinit_prog(t_fdf *fdf)
{
	free(fdf->map.altitudes);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img.ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win.ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	init_prog(&fdf, argv[1]);
	fdf.map.pos.x = fdf.img.width >> 1;
	fdf.map.pos.y = fdf.img.height >> 1;
	fdf.map.translation_offset = min(fdf.img.width >> 1, fdf.img.height >> 1) / 50;
	fdf.map.z_normalize = 1;
	mlx_hook(fdf.win.ptr, KeyPress, KeyPressMask, key_pressed, &fdf);
	mlx_hook(fdf.win.ptr, DestroyNotify, NoEventMask, &mlx_loop_end, fdf.mlx_ptr);
	mlx_loop(fdf.mlx_ptr);
	deinit_prog(&fdf);
	return (0);
}
