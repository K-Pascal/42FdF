/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:51:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/29 14:25:31 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"

#include "events.h"
#include "parser.h"
#include "render.h"
#include "typedefs.h"

static int	start_mlx(t_fdf *fdf)
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
	t_list	*current;
	float	center_z;
	int		i;

	get_mapinfo(&fdf->map, pathname);
	fdf->map.last_row = malloc(fdf->map.num_values * sizeof(t_vec2));
	if (fdf->map.last_row == NULL)
	{
		perror("init_mapdata():malloc()");
		ft_lstclear(&(fdf->map.data), &free);
		exit(EXIT_FAILURE);
	}
	if (SIZE_TRIGO_TABLE <= 4)
		fdf->map.angle_offset = 1;
	else
		fdf->map.angle_offset = SIZE_TRIGO_TABLE / 2;
	fdf->map.center.x = (float)(fdf->map.num_values - 1) / 2.f;
	fdf->map.center.y = (float)(fdf->map.num_lines - 1) / 2.f;
	center_z = 0.f;
	current = fdf->map.data;
	while (current != NULL)
	{
		i = 0;
		while (i < fdf->map.num_values)
		{
			center_z += ((t_value *)current->content)[i].altitude;
			i++;
		}
		current = current->next;
	}
	fdf->map.center.z = center_z / (float)(fdf->map.num_values * fdf->map.num_lines);
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
	mlx_loop_hook(fdf->mlx_ptr, &update_frame, fdf);
}

void	init_trigo_table(t_trigo_table *table)
{
	int			i;
	float		angle;
	float const	angle_offset = 2.f * 3.14159f / SIZE_TRIGO_TABLE;

	angle = 0.f;
	i = 0;
	while (i < SIZE_TRIGO_TABLE)
	{
		table->trigo[i].cos = cosf(angle);
		table->trigo[i].sin = sinf(angle);
		angle += angle_offset;
		i++;
	}
	table->x = 0;
	table->y = 0;
	table->z = 0;
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
