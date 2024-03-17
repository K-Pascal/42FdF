/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:41:59 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/22 17:30:12 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "typedefs.h"

//void	rotate(t_vec3 *rotated, t_vec3 input, t_trigo_table *table)
//{
//	t_vec3	temp;
//
//	temp.x = input.x;
//	temp.y = input.y * table->trigo[table->x].cos
//		+ input.z * table->trigo[table->x].sin;
//	temp.z = -input.y * table->trigo[table->x].sin
//		+ input.z * table->trigo[table->x].cos;
//	input.x = temp.x * table->trigo[table->y].cos
//		- temp.z * table->trigo[table->y].sin;
//	input.y = temp.y;
//	input.z = temp.x * table->trigo[table->y].sin
//		+ temp.z * table->trigo[table->y].cos;
//	rotated->x = input.x * table->trigo[table->z].cos
//		- input.y * table->trigo[table->z].sin;
//	rotated->y = input.x * table->trigo[table->z].sin
//		+ input.y * table->trigo[table->z].cos;
//	rotated->z = input.z;
//}
//
//void	translate(t_vec3 *translated, t_vec3 input, t_vec3 *translate)
//{
//	translated->x = input.x + translate->x;
//	translated->y = input.y + translate->y;
//	translated->z = input.z + translate->z;
//}
//
//void	scale(t_vec3 *translated, t_vec3 input, t_vec3 *scale)
//{
//	translated->x = input.x * scale->x;
//	translated->y = input.y * scale->y;
//	translated->z = input.z * scale->z;
//}

void	rotate(float output[4][4], t_trigo_table *table)
{
	output[0][0] = table->trigo[table->y].cos * table->trigo[table->z].cos;
	output[0][1] = table->trigo[table->x].sin
		* table->trigo[table->y].sin * table->trigo[table->z].cos
		- table->trigo[table->x].cos * table->trigo[table->z].sin;
	output[0][2] = table->trigo[table->x].cos
		* table->trigo[table->y].sin * table->trigo[table->z].cos
		+ table->trigo[table->x].sin * table->trigo[table->z].sin;
	output[0][3] = 0.f;
	output[1][0] = table->trigo[table->y].cos * table->trigo[table->z].sin;
	output[1][1] = table->trigo[table->x].sin
		* table->trigo[table->y].sin * table->trigo[table->z].sin
		+ table->trigo[table->x].cos * table->trigo[table->z].cos;
	output[1][2] = table->trigo[table->x].cos
		* table->trigo[table->y].sin * table->trigo[table->z].sin
		- table->trigo[table->x].sin * table->trigo[table->z].cos;
	output[1][3] = 0.f;
	output[2][0] = -table->trigo[table->y].sin;
	output[2][1] = table->trigo[table->x].sin * table->trigo[table->y].cos;
	output[2][2] = table->trigo[table->x].cos * table->trigo[table->y].cos;
	output[2][3] = 0.f;
	output[3][0] = 0.f;
	output[3][1] = 0.f;
	output[3][2] = 0.f;
	output[3][3] = 1.f;
}

void	translate(float output[4][4], t_vec3 *translate)
{
	output[0][0] = 1.f;
	output[0][1] = 0.f;
	output[0][2] = 0.f;
	output[0][3] = translate->x;
	output[1][0] = 0.f;
	output[1][1] = 1.f;
	output[1][2] = 0.f;
	output[1][3] = translate->y;
	output[2][0] = 0.f;
	output[2][1] = 0.f;
	output[2][2] = 1.f;
	output[2][3] = translate->z;
	output[3][0] = 0.f;
	output[3][1] = 0.f;
	output[3][2] = 0.f;
	output[3][3] = 1.f;
}

void	scale(float output[4][4], t_vec3 *scale)
{
	output[0][0] = scale->x;
	output[0][1] = 0.f;
	output[0][2] = 0.f;
	output[0][3] = 0.f;
	output[1][0] = 0.f;
	output[1][1] = scale->y;
	output[1][2] = 0.f;
	output[1][3] = 0.f;
	output[2][0] = 0.f;
	output[2][1] = 0.f;
	output[2][2] = scale->z;
	output[2][3] = 0.f;
	output[3][0] = 0.f;
	output[3][1] = 0.f;
	output[3][2] = 0.f;
	output[3][3] = 1.f;
}

void	mat_identity(float output[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			output[i][j] = (float)(i == j);
			j++;
		}
		i++;
	}
}

//void	isometric_transform(t_vec3 *output, t_vec3 input)
//{
//	float const	invsqrt_6 = 0.40825f;
//	float const	sqrt_3 = 1.73205f;
//	float const	sqrt_2 = 1.41421f;
//
//	input.y -= input.z;
//	input.z += input.y;
//	input.y -= input.z;
//	output->x = invsqrt_6 * sqrt_3 * (
//			input.x
//			- input.z);
//	output->y = invsqrt_6 * (
//			input.x
//			+ (2.f * input.y)
//			+ input.z);
//	output->z = invsqrt_6 * sqrt_2 * (
//			input.x
//			- input.y
//			+ input.z);
//}

void	isometric_transform(float output[4][4])
{
	float const	invsqrt_6 = 0.40825f;
	float const	sqrt_3 = 1.73205f;
	float const	sqrt_2 = 1.41421f;

	output[0][0] = invsqrt_6 * sqrt_3;
	output[0][1] = -invsqrt_6 * sqrt_3;
	output[0][2] = 0.f;
	output[0][3] = 0.f;
	output[1][0] = invsqrt_6;
	output[1][1] = invsqrt_6;
	output[1][2] = -2.f * invsqrt_6;
	output[1][3] = 0.f;
	output[2][0] = invsqrt_6 * sqrt_2;
	output[2][1] = invsqrt_6 * sqrt_2;
	output[2][2] = invsqrt_6 * sqrt_2;
	output[2][3] = 0.f;
	output[3][0] = 0.f;
	output[3][1] = 0.f;
	output[3][2] = 0.f;
	output[3][3] = 1.f;
}
