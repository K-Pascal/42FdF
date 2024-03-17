/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:45:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 14:45:44 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

t_vec2	orthographic_projection(t_vec2 pos, t_vec3 point3d)
{
	t_vec2	projection;

	projection.x = pos.x + point3d.x;
	projection.y = pos.y + point3d.y;
	return (projection);
}

t_vec2	isometric_projection(t_vec2 pos, t_vec3 point3d)
{
	float const	invsqrt_6 = 0.408248f;
	float const	sqrt_3 = 1.732051f;
	float const	sqrt_2 = 1.414214f;
	t_vec3		rotated;

	point3d.x = point3d.x;
	point3d.y -= point3d.z;
	point3d.z += point3d.y;
	point3d.y -= point3d.z;
	rotated.x = (int)(invsqrt_6 * sqrt_3 * (
						(float)point3d.x
					- (float)point3d.z));
	rotated.y = (int)(invsqrt_6 * (
						(float)point3d.x
					+ (float)(point3d.y << 1)
					+ (float)point3d.z));
	rotated.z = (int)(invsqrt_6 * sqrt_2 * (
						(float)point3d.x
					- (float)point3d.y
					+ (float)point3d.z));
	pos.x += rotated.x;
	pos.y += rotated.y;
	return (pos);
}

