/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:41:59 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 14:44:20 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "typedefs.h"

t_vec3	rotate_x(t_vec3 point3d, float angle)
{
	t_vec3	rotated;

	rotated.x = point3d.x;
	rotated.y = (int)((float)point3d.y * cos(angle) + (float)point3d.z * sin(angle));
	rotated.z = (int)(-(float)point3d.y * sin(angle) + (float)point3d.z * cos(angle));
	return (rotated);
}

t_vec3	rotate_y(t_vec3 point3d, float angle)
{
	t_vec3	rotated;

	rotated.x = (int)((float)point3d.x * cos(angle) - (float)point3d.z * sin(angle));
	rotated.y = point3d.y;
	rotated.z = (int)((float)point3d.x * sin(angle) + (float)point3d.z * cos(angle));
	return (rotated);
}

t_vec3	rotate_z(t_vec3 point3d, float angle)
{
	t_vec3	rotated;

	rotated.x = (int)((float)point3d.x * cos(angle) - (float)point3d.y * sin(angle));
	rotated.y = (int)((float)point3d.x * sin(angle) + (float)point3d.y * cos(angle));
	rotated.z = point3d.z;
	return (rotated);
}
