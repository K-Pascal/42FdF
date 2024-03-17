/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:43:23 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 14:44:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "typedefs.h"

t_vec3	rotate_x(t_vec3 point3d, float angle);
t_vec3	rotate_y(t_vec3 point3d, float angle);
t_vec3	rotate_z(t_vec3 point3d, float angle);

#endif
