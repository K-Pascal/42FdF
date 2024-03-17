/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:09:13 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/01 18:36:56 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4x4	mat_mult_mat(t_mat4x4 left, t_mat4x4 right)
{
	t_mat4x4	output;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			output.m[j][i] = left.m[j][0] * right.m[0][i]
				+ left.m[j][1] * right.m[1][i]
				+ left.m[j][2] * right.m[2][i]
				+ left.m[j][3] * right.m[3][i];
			j++;
		}
		i++;
	}
	return (output);
}

t_vec3	mat_mult_vec(t_mat4x4 matrix, t_vec3 input)
{
	float	w;
	t_vec3	output;

	w = matrix.m[3][0] * input.x + matrix.m[3][1] * input.y
		+ matrix.m[3][2] * input.z + matrix.m[3][3];
	output.x = matrix.m[0][0] * input.x + matrix.m[0][1] * input.y
		+ matrix.m[0][2] * input.z + matrix.m[0][3];
	output.y = matrix.m[1][0] * input.x + matrix.m[1][1] * input.y
		+ matrix.m[1][2] * input.z + matrix.m[1][3];
	output.z = matrix.m[2][0] * input.x + matrix.m[2][1] * input.y
		+ matrix.m[2][2] * input.z + matrix.m[2][3];
	if (w != 0.f)
	{
		output.x /= w;
		output.y /= w;
		output.z /= w;
	}
	return (output);
}

void	mat_identity(float m[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = (float)(i == j);
			j++;
		}
		i++;
	}
}
