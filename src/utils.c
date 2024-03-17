/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:51:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/07 15:38:14 by pnguyen-         ###   ########.fr       */
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

void	init_trigo_table(t_trigo table[SIZE_TRIGO_TABLE])
{
	int			i;
	float		angle;
	float const	angle_offset = 2.f * M_PI / SIZE_TRIGO_TABLE;

	angle = 0.f;
	i = 0;
	while (i < SIZE_TRIGO_TABLE)
	{
		table[i].cos = cosf(angle);
		table[i].sin = sinf(angle);
		angle += angle_offset;
		i++;
	}
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

