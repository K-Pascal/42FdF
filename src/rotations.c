/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:41:59 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/08 15:42:29 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "typedefs.h"

void	rotate_x(t_vec3 *rotated, t_vec3 input, t_trigo *trigo)
{
	rotated->x = input.x;
	rotated->y = input.y * trigo->cos + input.z * trigo->sin;
	rotated->z = -input.y * trigo->sin + input.z * trigo->cos;
}

void	rotate_y(t_vec3 *rotated, t_vec3 input, t_trigo *trigo)
{
	rotated->x = input.x * trigo->cos - input.z * trigo->sin;
	rotated->y = input.y;
	rotated->z = input.x * trigo->sin + input.z * trigo->cos;
}

void	rotate_z(t_vec3 *rotated, t_vec3 input, t_trigo *trigo)
{
	rotated->x = input.x * trigo->cos - input.y * trigo->sin;
	rotated->y = input.x * trigo->sin + input.y * trigo->cos;
	rotated->z = input.z;
}
