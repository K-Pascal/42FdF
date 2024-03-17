/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:43:23 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 18:32:05 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "typedefs.h"

t_vec3	rotate_x(t_vec3 point3d, t_trigo trigo);
t_vec3	rotate_y(t_vec3 point3d, t_trigo trigo);
t_vec3	rotate_z(t_vec3 point3d, t_trigo trigo);

#endif
