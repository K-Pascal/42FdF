/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:23:35 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/22 15:53:43 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "typedefs.h"

typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

t_mat4x4	mat_mult_mat(t_mat4x4 left, t_mat4x4 right);
t_vec3		mat_mult_vec(t_mat4x4 matrix, t_vec3 input);

#endif
