/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:41:59 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/07 15:36:49 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "typedefs.h"

t_vec3	rotate_x(t_vec3 point3d, t_trigo trigo)
{
	t_vec3	rotated;

	rotated.x = point3d.x;
	rotated.y = (int)((float)point3d.y * trigo.cos + (float)point3d.z * trigo.sin);
	rotated.z = (int)(-(float)point3d.y * trigo.sin + (float)point3d.z * trigo.cos);
	return (rotated);
}

t_vec3	rotate_y(t_vec3 point3d, t_trigo trigo)
{
	t_vec3	rotated;

	rotated.x = (int)((float)point3d.x * trigo.cos - (float)point3d.z * trigo.sin);
	rotated.y = point3d.y;
	rotated.z = (int)((float)point3d.x * trigo.sin + (float)point3d.z * trigo.cos);
	return (rotated);
}

t_vec3	rotate_z(t_vec3 point3d, t_trigo trigo)
{
	t_vec3	rotated;

	rotated.x = (int)((float)point3d.x * trigo.cos - (float)point3d.y * trigo.sin);
	rotated.y = (int)((float)point3d.x * trigo.sin + (float)point3d.y * trigo.cos);
	rotated.z = point3d.z;
	return (rotated);
}
