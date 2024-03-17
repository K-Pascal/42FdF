/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:51:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/14 15:48:53 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"

#include "typedefs.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	*(int *)(img->data
			+ img->size_line * y
			+ img->bytes_per_pixel * x
			)
		= color;
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

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int	my_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

void	reset_map(t_fdf *fdf)
{
	ft_bzero(fdf->img.data, fdf->img.size_line * fdf->img.height);
	mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
}
