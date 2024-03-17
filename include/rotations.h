/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:43:23 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/08 15:41:53 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "typedefs.h"

void	rotate_x(t_vec3 *rotated, t_vec3 input, t_trigo *trigo);
void	rotate_y(t_vec3 *rotated, t_vec3 input, t_trigo *trigo);
void	rotate_z(t_vec3 *rotated, t_vec3 input, t_trigo *trigo);

#endif
