/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:13:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 19:07:20 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "projections.h"
#include "transformations.h"
#include "typedefs.h"

static t_mat4x4	project_translate(t_fdf *fdf)
{
	t_mat4x4	mat_world;
	t_mat4x4	transform;

	mat_identity(mat_world.m);
	if (fdf->map.proj_mode == P_PERSP)
		perspective_projection(transform.m,
			fdf->img.aspect_ratio, fdf->map.fov);
	else
		mat_identity(transform.m);
	mat_world = mat_mult_mat(mat_world, transform);
	translate(transform.m, &fdf->map.translate);
	if (fdf->map.proj_mode == P_ORTHO)
	{
		transform.m[0][3] *= fdf->map.scale.x;
		transform.m[1][3] *= fdf->map.scale.y;
	}
	mat_world = mat_mult_mat(mat_world, transform);
	return (mat_world);
}

static t_mat4x4	rotate_scale(t_fdf *fdf)
{
	t_mat4x4	mat_world;
	t_mat4x4	transform;

	mat_identity(mat_world.m);
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
	return (mat_world);
}

t_vec3	transform_points(float x, float y, float z, t_fdf *fdf)
{
	t_vec3		point3d;
	t_mat4x4	mat_world;

	point3d.x = x;
	point3d.y = y;
	point3d.z = z;
	mat_world = mat_mult_mat(project_translate(fdf),
			rotate_scale(fdf));
	point3d = mat_mult_vec(mat_world, point3d);
	return (point3d);
}
