/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/07 20:24:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "typedefs.h"
#include "utils.h"

static char	init_datalow(t_vec2 *dst, t_vec2 *start, t_vec2 *end)
{
	char	yi;

	dst->x = end->x - start->x;
	dst->y = end->y - start->y;
	yi = 1;
	if (dst->y < 0)
	{
		dst->y = ~dst->y + 1;
		yi = -1;
	}
	return (yi);
}

static char	init_datahigh(t_vec2 *dst, t_vec2 *start, t_vec2 *end)
{
	char	xi;

	dst->x = end->x - start->x;
	dst->y = end->y - start->y;
	xi = 1;
	if (dst->x < 0)
	{
		dst->x = ~dst->x + 1;
		xi = -1;
	}
	return (xi);
}

static void	draw_linelow(t_img *img, t_vec2 start, t_vec2 end, int color)
{
	t_vec2	dst;
	int		error;
	char	yi;

	yi = init_datalow(&dst, &start, &end);
	error = 2 * dst.y - dst.x;
	while (start.x <= end.x)
	{
		if (start.x >= img->width)
			break ;
		if (start.x >= 0 && start.y >= 0 && start.y < img->height)
			put_pixel(img, start.x, start.y, color);
		if (error > 0)
		{
			start.y += yi;
			error += 2 * (dst.y - dst.x);
		}
		else
			error += 2 * dst.y;
		start.x++;
	}
}

static void	draw_linehigh(t_img *img, t_vec2 start, t_vec2 end, int color)
{
	t_vec2	dst;
	int		error;
	char	xi;

	xi = init_datahigh(&dst, &start, &end);
	error = 2 * dst.x - dst.y;
	while (start.y <= end.y)
	{
		if (start.y >= img->height)
			break ;
		if (start.x >= 0 && start.y >= 0 && start.x < img->width)
			put_pixel(img, start.x, start.y, color);
		if (error > 0)
		{
			start.x += xi;
			error += 2 * (dst.x - dst.y);
		}
		else
			error += 2 * dst.x;
		start.y++;
	}
}

void	draw_line(t_img *img, t_vec2 start, t_vec2 end, int color)
{
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			draw_linelow(img, end, start, color);
		else
			draw_linelow(img, start, end, color);
	}
	else
	{
		if (start.y > end.y)
			draw_linehigh(img, end, start, color);
		else
			draw_linehigh(img, start, end, color);
	}
}
