/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:51:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/29 16:54:55 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	*(int *)(img->data
			+ (img->size_line * y)
			+ ((img->bits_per_pixel / 8) * x)
			)
		= color;
}
