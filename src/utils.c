/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:51:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 19:20:12 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"

#include "events.h"
#include "parser.h"
#include "typedefs.h"

static int	start_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (0);
	mlx_get_screen_size(fdf->mlx_ptr, &fdf->win.width, &fdf->win.height);
	fdf->win.width /= 2;
	fdf->win.height /= 2;
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

static void	init_mapvalues(t_map *map)
{
	t_list	*current;
	float	center_z;
	int		i;

	if (map->num_values < map->num_lines)
		map->translate_offset = (float)(map->num_values);
	else
		map->translate_offset = (float)(map->num_lines);
	map->center.x = (float)(map->num_values - 1) / 2.f;
	map->center.y = (float)(map->num_lines - 1) / 2.f;
	center_z = 0.f;
	current = map->data;
	while (current != NULL)
	{
		i = 0;
		while (i < map->num_values)
		{
			center_z += ((t_value *)current->content)[i].altitude;
			i++;
		}
		current = current->next;
	}
	map->center.z = center_z
		/ (float)(map->num_values * map->num_lines);
}

void	init_mapdata(t_fdf *fdf, char const pathname[])
{
	get_mapinfo(&fdf->map, pathname);
	fdf->map.last_row = malloc(fdf->map.num_values * sizeof(t_vec2));
	if (fdf->map.last_row == NULL)
	{
		perror("init_mapdata():malloc()");
		ft_lstclear(&(fdf->map.data), &free);
		exit(EXIT_FAILURE);
	}
	init_mapvalues(&fdf->map);
}

void	init_mlx(t_fdf *fdf)
{
	if (!start_mlx(fdf))
	{
		ft_putendl_fd("Failed to initialize mlx", STDERR_FILENO);
		ft_lstclear(&(fdf->map.data), &free);
		free(fdf->map.last_row);
		exit(EXIT_FAILURE);
	}
	fdf->img.data = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bpp,
			&fdf->img.size_line, &fdf->img.endian);
	fdf->img.bpp /= 8;
	mlx_hook(fdf->win.ptr, KeyPress, KeyPressMask, &key_pressed, fdf);
	mlx_hook(fdf->win.ptr, KeyRelease, KeyReleaseMask, &key_released, fdf);
	mlx_hook(fdf->win.ptr, ButtonPress, ButtonPressMask, &mouse_pressed, fdf);
	mlx_hook(fdf->win.ptr, DestroyNotify, NoEventMask,
		&mlx_loop_end, fdf->mlx_ptr);
}

void	deinit_prog(t_fdf *fdf)
{
	ft_lstclear(&(fdf->map.data), &free);
	free(fdf->map.last_row);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img.ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win.ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
}
