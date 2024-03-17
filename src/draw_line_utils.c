/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:14:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/15 19:18:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	*(int *)(img->data
			+ img->size_line * y
			+ img->bpp * x
			)
		= color;
}

int	my_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
