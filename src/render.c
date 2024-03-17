/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:29:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/16 19:25:53 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include "draw_line.h"
#include "projections.h"
#include "events_utils.h"
#include "transformations.h"
#include "typedefs.h"

static t_vec2	render_isometric(float x, float y, float z, t_fdf *fdf)
{
	t_vec3	point3d;
	t_vec3	transformation;
	t_vec2	projection;

	point3d.x = x;
	point3d.y = y;
	point3d.z = z;
	scale(&transformation, point3d, &fdf->map.scale);
	rotate(&transformation, transformation, &fdf->map.table);
	isometric_transform(&transformation, transformation);
	translate(&transformation, transformation, &fdf->map.translate);
	orthographic_projection(&projection, fdf, transformation);
	return (projection);
}

void	render(t_fdf *fdf)
{
	int		i;
	int		j;
	t_vec2	last;
	t_vec2	projection;
	t_list	*line;

	i = 0;
	line = fdf->map.data;
	while (line != NULL)
	{
		j = 0;
		while (j < fdf->map.num_values)
		{
			projection = render_isometric((float)(j) - fdf->map.center.x,
					(float)(i) - fdf->map.center.y,
					((t_value *)line->content)[j].altitude - fdf->map.center.z,
					fdf);
			if (j)
				draw_line(&fdf->img, last, projection,
					((t_value *)line->content)[j].color);
			if (i)
				draw_line(&fdf->img, fdf->map.last_row[j], projection,
					((t_value *)line->content)[j].color);
			last = projection;
			fdf->map.last_row[j] = last;
			j++;
		}
		line = line->next;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
}

int	update_frame(t_fdf *fdf)
{
	if (!fdf->transform || fdf->transform == K_MOD)
		return (0);
	if (fdf->transform & K_W && !(fdf->transform & K_MOD))
	{
		fdf->map.table.x--;
		if (fdf->map.table.x < 0)
			fdf->map.table.x = SIZE_TRIGO_TABLE - 1;
	}
	if (fdf->transform & K_S && !(fdf->transform & K_MOD))
	{
		fdf->map.table.x++;
		if (fdf->map.table.x >= SIZE_TRIGO_TABLE)
			fdf->map.table.x = 0;
	}
	if (fdf->transform & K_D && !(fdf->transform & K_MOD))
	{
		fdf->map.table.y--;
		if (fdf->map.table.y < 0)
			fdf->map.table.y = SIZE_TRIGO_TABLE - 1;
	}
	if (fdf->transform & K_A && !(fdf->transform & K_MOD))
	{
		fdf->map.table.y++;
		if (fdf->map.table.y >= SIZE_TRIGO_TABLE)
			fdf->map.table.y = 0;
	}
	if (fdf->transform & K_Q && !(fdf->transform & K_MOD))
	{
		fdf->map.table.z++;
		if (fdf->map.table.z >= SIZE_TRIGO_TABLE)
			fdf->map.table.z = 0;
	}
	if (fdf->transform & K_E && !(fdf->transform & K_MOD))
	{
		fdf->map.table.z--;
		if (fdf->map.table.z < 0)
			fdf->map.table.z = SIZE_TRIGO_TABLE - 1;
	}
	if (fdf->transform & K_W && fdf->transform & K_MOD)
		fdf->map.translate.y -= 2.f;
	if (fdf->transform & K_S && fdf->transform & K_MOD)
		fdf->map.translate.y += 2.f;
	if (fdf->transform & K_D && fdf->transform & K_MOD)
		fdf->map.translate.x += 2.f;
	if (fdf->transform & K_A && fdf->transform & K_MOD)
		fdf->map.translate.x -= 2.f;
	if (fdf->transform & K_Q && fdf->transform & K_MOD)
		fdf->map.translate.z -= 2.f;
	if (fdf->transform & K_E && fdf->transform & K_MOD)
		fdf->map.translate.z += 2.f;
	if (fdf->transform & K_MINUS)
	{
		fdf->map.scale.z -= 0.125f;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = -0.125f;
	}
	if (fdf->transform & K_EQUAL)
	{
		fdf->map.scale.z += 0.125f;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = 0.125f;
	}
	reset_map(fdf);
	render(fdf);
	return (0);
}
