/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/13 18:18:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <X11/X.h>

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

#include "draw_line.h"
#include "events.h"
#include "parser.h"
#include "render.h"
#include "typedefs.h"
#include "utils.h"

int		start_mlx(t_fdf *fdf);
void	init_mapdata(t_fdf *fdf, char pathname[]);
void	init_mlx(t_fdf *fdf);
void	deinit_prog(t_fdf *fdf);

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	float	len;

	if (argc != 2)
		return (EXIT_FAILURE);
	init_mapdata(&fdf, argv[1]);
	init_trigo_table(&fdf.map.table);
	init_mlx(&fdf);
	len = (float)(fdf.img.width >> 1);
	if (len <= fdf.map.num_values)
		fdf.map.scale.x = 1.f;
	else
		fdf.map.scale.x = len / (float)fdf.map.num_values;
	len = (float)(fdf.img.height >> 1);
	if (len <= fdf.map.num_lines)
		fdf.map.scale.y = 1.f;
	else
		fdf.map.scale.y = len / (float)fdf.map.num_lines;
	fdf.map.scale.z = 1.f;
	fdf.map.pos.x = fdf.img.width >> 1;
	fdf.map.pos.y = fdf.img.height >> 1;
	fdf.transform = K_NONE;
	mlx_loop(fdf.mlx_ptr);
	deinit_prog(&fdf);
	return (0);
}

int	start_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (0);
	mlx_get_screen_size(fdf->mlx_ptr, &fdf->win.width, &fdf->win.height);
	fdf->win.width >>= 1;
	fdf->win.height >>= 1;
	fdf->win.ptr = mlx_new_window(fdf->mlx_ptr,
			fdf->win.width, fdf->win.height, "FdF");
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
		free(fdf->map.data);
		free(fdf->map.last_row);
		exit(EXIT_FAILURE);
	}
	fdf->map.last_row = malloc(fdf->map.num_values * sizeof(t_vec3));
	if (fdf->map.last_row == NULL)
	{
		perror("malloc()");
		free(fdf->map.data);
		exit(EXIT_FAILURE);
	}
	fdf->map.center.x = (float)(fdf->map.num_values >> 1);
	fdf->map.center.y = (float)(fdf->map.num_lines >> 1);
	fdf->map.center.z = 0.f;
	fdf->map.translate.x = 0.f;
	fdf->map.translate.y = 0.f;
	fdf->map.translate.z = 0.f;
}

void	init_mlx(t_fdf *fdf)
{
	if (!start_mlx(fdf))
	{
		ft_putendl_fd("Failed to initialize mlx", STDERR_FILENO);
		free(fdf->map.data);
		free(fdf->map.last_row);
		exit(EXIT_FAILURE);
	}
	fdf->img.data = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bytes_per_pixel,
			&fdf->img.size_line, &fdf->img.endian);
	fdf->img.bytes_per_pixel >>= 3;
	mlx_hook(fdf->win.ptr, KeyPress, KeyPressMask, &key_pressed, fdf);
	mlx_hook(fdf->win.ptr, KeyRelease, KeyReleaseMask, &key_released, fdf);
	mlx_hook(fdf->win.ptr, ButtonPress, ButtonPressMask, &mouse_pressed, fdf);
	mlx_hook(fdf->win.ptr, DestroyNotify, NoEventMask,
		&mlx_loop_end, fdf->mlx_ptr);
	mlx_loop_hook(fdf->mlx_ptr, update_frame, fdf);
}

void	deinit_prog(t_fdf *fdf)
{
	free(fdf->map.data);
	free(fdf->map.last_row);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img.ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win.ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
}
