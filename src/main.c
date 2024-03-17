/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/08 18:47:40 by pnguyen-         ###   ########.fr       */
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
	int		k;

	i = 0;
	k = 0;
	while (i < fdf->map.num_lines)
	{
		t_vec3	last;
		j = 0;
		while (j < fdf->map.num_values)
		{
			t_vec3 point3d = {
				j - fdf->map.center.x,
				i - fdf->map.center.y,
				fdf->map.altitudes[k] * fdf->map.scale.z
			};
			t_vec3 view;
			isometric_view(&view, point3d, &fdf->map);
			t_vec2 projection;
			orthographic_projection(&projection, fdf, view);
			t_vec2 last_proj;
			if (j)
			{
				orthographic_projection(&last_proj, fdf, last);
				draw_line(&fdf->img, last_proj, projection, 0xFFFFFFFF);
			}
			if (i)
			{
				orthographic_projection(&last_proj, fdf, fdf->map.last_row[j]);
				draw_line(&fdf->img, last_proj, projection, 0xFFFFFFFF);
			}
			last = view;
			fdf->map.last_row[j] = last;
			j++;
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
}

void	reset_map(t_fdf *fdf)
{
	ft_bzero(fdf->img.data, fdf->img.size_line * fdf->img.height);
	mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
}

int mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fdf->map.scale.x *= 1.1f;
		fdf->map.scale.y *= 1.1f;
//		fdf->map.scale.z *= 1.1f;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (button == 5)
	{
		fdf->map.scale.x *= 0.9f;
		fdf->map.scale.y *= 0.9f;
//		fdf->map.scale.z *= 0.9f;
		reset_map(fdf);
		render_isometric(fdf);
	}
	return (1);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fdf->mlx_ptr);
	else if (keycode == '0')
	{
		fdf->map.table.x = 0;
		fdf->map.table.y = 0;
		reset_map(fdf);
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
		fdf->map.scale.z -= 0.125f;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = -0.125f;
		reset_map(fdf);
		render_isometric(fdf);
	}
	else if (keycode == '=')
	{
		fdf->map.scale.z += 0.125f;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = 0.125f;
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

void	init_mapdata(t_fdf *fdf, char pathname[])
{
	get_mapinfo(&fdf->map, pathname);
	if (!get_mapdata(&fdf->map, pathname))
	{
		free(fdf->map.altitudes);
		free(fdf->map.last_row);
		exit(EXIT_FAILURE);
	}
	fdf->map.last_row = malloc(fdf->map.num_values * sizeof(t_vec3));
	if (fdf->map.last_row == NULL)
	{
		perror("malloc()");
		free(fdf->map.altitudes);
		exit(EXIT_FAILURE);
	}
	fdf->map.center.x = (float)(fdf->map.num_values >> 1);
	fdf->map.center.y = (float)(fdf->map.num_lines >> 1);
	fdf->map.center.z = 0.f;
}

void	init_mlx(t_fdf *fdf)
{
	if (!start_mlx(fdf))
	{
		ft_putendl_fd("Failed to initialize mlx", STDERR_FILENO);
		free(fdf->map.altitudes);
		free(fdf->map.last_row);
		exit(EXIT_FAILURE);
	}
	fdf->img.data = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bytes_per_pixel,
			&fdf->img.size_line, &fdf->img.endian);
	fdf->img.bytes_per_pixel >>= 3;
	mlx_hook(fdf->win.ptr, KeyPress, KeyPressMask, key_pressed, fdf);
	mlx_hook(fdf->win.ptr, ButtonPress, ButtonPressMask, &mouse_pressed, fdf);
	mlx_hook(fdf->win.ptr, DestroyNotify, NoEventMask, &mlx_loop_end, fdf->mlx_ptr);
}

void	deinit_prog(t_fdf *fdf)
{
	free(fdf->map.altitudes);
	free(fdf->map.last_row);
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
	init_mapdata(&fdf, argv[1]);
	init_trigo_table(&fdf.map.table);
	init_mlx(&fdf);
	fdf.map.pos.x = fdf.img.width >> 1;
	fdf.map.pos.y = fdf.img.height >> 1;
	fdf.map.translation_offset = min(fdf.img.width >> 1, fdf.img.height >> 1) >> 5;
	if ((fdf.img.width >> 1) <= fdf.map.num_values)
		fdf.map.scale.x = 1;
	else
		fdf.map.scale.x = ((float)(fdf.img.width >> 1) / (float)fdf.map.num_values);
	if ((fdf.img.height >> 1) <= fdf.map.num_lines)
		fdf.map.scale.y = 1.f;
	else
		fdf.map.scale.y = ((float)(fdf.img.height >> 1) / (float)fdf.map.num_lines);
	fdf.map.scale.z = 0.125f;
	mlx_loop(fdf.mlx_ptr);
	deinit_prog(&fdf);
	return (0);
}
