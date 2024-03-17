/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:41:59 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/13 18:14:16 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "typedefs.h"

void	rotate(t_vec3 *rotated, t_vec3 input, t_trigo_table *table)
{
	t_vec3	temp;

	temp.x = input.x;
	temp.y = input.y * table->trigo[table->x].cos
		+ input.z * table->trigo[table->x].sin;
	temp.z = -input.y * table->trigo[table->x].sin
		+ input.z * table->trigo[table->x].cos;
	input.x = temp.x * table->trigo[table->y].cos
		- temp.z * table->trigo[table->y].sin;
	input.y = temp.y;
	input.z = temp.x * table->trigo[table->y].sin
		+ temp.z * table->trigo[table->y].cos;
	rotated->x = input.x * table->trigo[table->z].cos
		- input.y * table->trigo[table->z].sin;
	rotated->y = input.x * table->trigo[table->z].sin
		+ input.y * table->trigo[table->z].cos;
	rotated->z = input.z;
}

void	translate(t_vec3 *translated, t_vec3 input, t_vec3 *translate)
{
	translated->x = input.x + translate->x;
	translated->y = input.y + translate->y;
	translated->z = input.z + translate->z;
}

void	scale(t_vec3 *translated, t_vec3 input, t_vec3 *scale)
{
	translated->x = input.x * scale->x;
	translated->y = input.y * scale->y;
	translated->z = input.z * scale->z;
}
