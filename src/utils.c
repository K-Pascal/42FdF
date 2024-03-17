/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:51:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/08 13:47:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

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

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
