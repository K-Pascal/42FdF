/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:29:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/29 19:57:49 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include "draw_line.h"
#include "projections.h"
#include "events_utils.h"
#include "transformations.h"
#include "matrix.h"
#include "typedefs.h"

int my_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static t_vec3 render_perspective(float x, float y, float z, t_fdf *fdf)
{
	t_vec3		point3d;
	t_mat4x4	mat_world;
	t_mat4x4	transform;

	point3d.x = x;
	point3d.y = y;
	point3d.z = z;
	mat_identity(mat_world.m);
	if (fdf->map.proj_mode == P_PERSP)
		perspective_projection(transform.m, &fdf->img, fdf->map.inv_fov);
	else
		mat_identity(transform.m);
	mat_world = mat_mult_mat(mat_world, transform);
	translate(transform.m, &fdf->map.translate);
	transform.m[2][3] -= my_max(fdf->map.num_lines, fdf->map.num_values);
	mat_world = mat_mult_mat(mat_world, transform);
	if (fdf->map.view_mode == V_ISOM)
		isometric_transform(transform.m);
	else if (fdf->map.view_mode == V_CABI)
		cabinet_transform(transform.m);
	else
		mat_identity(transform.m);
	mat_world = mat_mult_mat(mat_world, transform);
	rotate(transform.m, &fdf->map.table);
	mat_world = mat_mult_mat(mat_world, transform);
	if (fdf->map.proj_mode == P_ORTHO)
		scale(transform.m, &fdf->map.scale);
	else
		mat_identity(transform.m);
	mat_world = mat_mult_mat(mat_world, transform);
	point3d = mat_mult_vec(mat_world, point3d);
	return (point3d);
}

void	render(t_fdf *fdf)
{
	int		i;
	int		j;
	t_vec2	last;
	t_vec2	projection;
	t_vec3	point3d;
	t_list	*line;

	i = 0;
	line = fdf->map.data;
	while (line != NULL)
	{
		j = 0;
		while (j < fdf->map.num_values)
		{
			float	z;
			z = ((t_value *)line->content)[j].altitude - fdf->map.center.z;
			if (fdf->map.proj_mode == P_PERSP)
				z *= fdf->map.scale.z;

			point3d = render_perspective((float)(j) - fdf->map.center.x,
					(float)(i) - fdf->map.center.y,
					z,
					fdf);
			orthographic_projection(&projection, fdf, point3d);
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

#include <sys/time.h>

long long get_actual_time(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000ll + t.tv_usec / 1000ll);
}

int	update_frame(t_fdf *fdf)
{
	float				delta_time;

	if (fdf->prev_time == 0ll)
		delta_time = 0.f;
	else
		delta_time = (float)(get_actual_time() - fdf->prev_time) / 1000.f;
	fdf->prev_time = get_actual_time();
	if (fdf->transform == K_NONE || fdf->transform == K_MOD)
		return (0);
	if (fdf->transform & K_W)
	{
		fdf->map.table.x += fdf->map.angle_offset * delta_time;
		if (fdf->map.table.x >= (float)SIZE_TRIGO_TABLE)
			fdf->map.table.x -= (float)SIZE_TRIGO_TABLE;
	}
	if (fdf->transform & K_S)
	{
		fdf->map.table.x -= fdf->map.angle_offset * delta_time;
		if (fdf->map.table.x < 0.f)
			fdf->map.table.x += (float)SIZE_TRIGO_TABLE;
	}
	if (fdf->transform & K_D)
	{
		fdf->map.table.y += fdf->map.angle_offset * delta_time;
		if (fdf->map.table.y >= (float)SIZE_TRIGO_TABLE)
			fdf->map.table.y -= (float)SIZE_TRIGO_TABLE;
	}
	if (fdf->transform & K_A)
	{
		fdf->map.table.y -= fdf->map.angle_offset * delta_time;
		if (fdf->map.table.y < 0.f)
			fdf->map.table.y += (float)SIZE_TRIGO_TABLE;
	}
	if (fdf->transform & K_Q)
	{
		fdf->map.table.z -= fdf->map.angle_offset * delta_time;
		if (fdf->map.table.z < 0.f)
			fdf->map.table.z += (float)SIZE_TRIGO_TABLE;
	}
	if (fdf->transform & K_E)
	{
		fdf->map.table.z += fdf->map.angle_offset * delta_time;
		if (fdf->map.table.z >= (float)SIZE_TRIGO_TABLE)
			fdf->map.table.z -= (float)SIZE_TRIGO_TABLE;
	}
	if (fdf->transform & K_I)
		fdf->map.translate.y -= fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_K)
		fdf->map.translate.y += fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_L)
		fdf->map.translate.x += fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_J)
		fdf->map.translate.x -= fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_U)
		fdf->map.translate.z -= fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_O)
		fdf->map.translate.z += fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_MINUS)
	{
		if (fdf->transform & K_MOD)
			fdf->map.scale.z -= 10.f * delta_time;
		else
			fdf->map.scale.z -= 1.f * delta_time;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = -1.f;
	}
	if (fdf->transform & K_EQUAL)
	{
		if (fdf->transform & K_MOD)
			fdf->map.scale.z += 10.f * delta_time;
		else
			fdf->map.scale.z += 1.f * delta_time;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = 1.f;
	}
	reset_map(fdf);
	render(fdf);
	return (0);
}
