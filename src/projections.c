/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:45:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 19:21:26 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

void	orthographic_projection(t_vec2 *output, t_fdf const *fdf,
		t_vec3 point3d)
{
	output->x = point3d.x + fdf->map.pos.x;
	output->y = point3d.y + fdf->map.pos.y;
}

void	perspective_projection(float output[4][4],
		float aspect_ratio, float fov)
{
	float const	z_far = 1000.f;
	float const	z_near = .1f;

	output[0][0] = aspect_ratio * fov;
	output[0][1] = 0.f;
	output[0][2] = 0.f;
	output[0][3] = 0.f;
	output[1][0] = 0.f;
	output[1][1] = fov;
	output[1][2] = 0.f;
	output[1][3] = 0.f;
	output[2][0] = 0.f;
	output[2][1] = 0.f;
	output[2][2] = z_far / (z_far - z_near);
	output[2][3] = 1.f;
	output[3][0] = 0.f;
	output[3][1] = 0.f;
	output[3][2] = -(z_far * z_near) / (z_far - z_near);
	output[3][3] = 0.f;
}
