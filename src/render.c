/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:29:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/13 15:38:02 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include "draw_line.h"
#include "projections.h"
#include "rotations.h"
#include "typedefs.h"
#include "utils.h"

void	render_isometric(t_fdf *fdf)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < fdf->map.num_lines)
	{
		t_vec2	last;
		j = 0;
		while (j < fdf->map.num_values)
		{
			t_vec3 point3d = {
				j - fdf->map.center.x,
				i - fdf->map.center.y,
				fdf->map.data[k].altitudes
			};
			t_vec3 transformation;
			scale(&transformation, point3d, &fdf->map.scale);
			rotate(&transformation, transformation, &fdf->map.table);
			isometric_transform(&transformation, transformation);
			translate(&transformation, transformation, &fdf->map.translate);
			t_vec2 projection;
			orthographic_projection(&projection, fdf, transformation);
			if (j)
				draw_line(&fdf->img, last, projection, fdf->map.data[k].color);
			if (i)
				draw_line(&fdf->img, fdf->map.last_row[j], projection, fdf->map.data[k].color);
			last = projection;
			fdf->map.last_row[j] = last;
			j++;
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
}

int update_frame(t_fdf *fdf)
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
	render_isometric(fdf);
	return (0);
}
