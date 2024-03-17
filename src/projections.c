/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:45:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/12 18:45:41 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotations.h"
#include "typedefs.h"

void	orthographic_projection(t_vec2 *output, t_fdf *fdf, t_vec3 point3d)
{
	output->x = point3d.x + fdf->map.pos.x;
	output->y = point3d.y + fdf->map.pos.y;
}

void	isometric_transform(t_vec3 *output, t_vec3 input)
{
	float const	invsqrt_6 = 0.40825f;
	float const	sqrt_3 = 1.73205f;
	float const	sqrt_2 = 1.41421f;

	input.y -= input.z;
	input.z += input.y;
	input.y -= input.z;
	output->x = invsqrt_6 * sqrt_3 * (
				input.x
				- input.z);
	output->y = invsqrt_6 * (
				input.x
				+ (2.f * input.y)
				+ input.z);
	output->z = invsqrt_6 * sqrt_2 * (
				input.x
				- input.y
				+ input.z);
}
