/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/29 17:24:53 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "typedefs.h"
#include "utils.h"

static void	draw_line_low(t_img *img, t_vec2 *start, t_vec2 *end)
{
	int	dx;
	int	dy;
	int	error;
	int	yi;

	dx = end->x - start->x;
	dy = end->y - start->y;
	yi = 1;
	if (dy < 0)
	{
		dy = -dy;
		yi = -1;
	}
	error = 2 * dy - dx;
	int	x;
	int	y;

	x = start->x;
	y = start->y;
	while (x <= end->x)
	{
		if (x >= img->width || y >= img->height)
			break ;
		if (x >= 0 && y >= 0)
			put_pixel(img, x, y, 0XFFFFFFFF);
		if (error > 0)
		{
			y += yi;
			error += 2 * (dy - dx);
		}
		else
			error += 2 * dy;
		x++;
	}
}

static void	draw_line_high(t_img *img, t_vec2 *start, t_vec2 *end)
{
	int	dx;
	int	dy;
	int	error;
	int	xi;

	dx = end->x - start->x;
	dy = end->y - start->y;
	xi = 1;
	if (dx < 0)
	{
		dx = -dx;
		xi = -1;
	}
	error = 2 * dx - dy;
	int	x;
	int	y;

	x = start->x;
	y = start->y;
	while (y <= end->y)
	{
		if (x >= img->width || y >= img->height)
			break ;
		if (x >= 0 && y >= 0)
			put_pixel(img, x, y, 0X00FFFFFFFF);
		if (error > 0)
		{
			x += xi;
			error += 2 * (dx - dy);
		}
		else
			error += 2 * dx;
		y++;
	}
}

void	draw_line(t_img *img, t_vec2 *start, t_vec2 *end)
{
	if (abs(end->y - start->y) < abs(end->x - start->x))
	{
		if (start->x > end->x)
			draw_line_low(img, end, start);
		else
			draw_line_low(img, start, end);
	}
	else
	{
		if (start->y > end->y)
			draw_line_high(img, end, start);
		else
			draw_line_high(img, start, end);
	}
}
