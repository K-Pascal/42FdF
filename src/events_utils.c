/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:56:34 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/29 15:31:27 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"

#include "typedefs.h"

#define DEFAULT_INV_FOV 144.f

void	reset_map(t_fdf *fdf)
{
	ft_bzero(fdf->img.data, fdf->img.size_line * fdf->img.height);
	mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
}

float	my_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	reset_configuration(t_fdf *fdf)
{
	fdf->map.table.x = 0;
	fdf->map.table.y = 0;
	fdf->map.table.z = 0;
	fdf->map.scale.x = (float)fdf->img.width / 2.f / (float)fdf->map.num_values;
	fdf->map.scale.y = (float)fdf->img.height / 2.f / (float)fdf->map.num_lines;
	fdf->map.scale.z = 1.f;
	fdf->map.translate.x = 0.f;
	fdf->map.translate.y = 0.f;
	fdf->map.translate.z = 0.f;
	fdf->map.pos.x = fdf->img.width / 2;
	fdf->map.pos.y = fdf->img.height / 2;
	fdf->map.inv_fov = DEFAULT_INV_FOV;
}
