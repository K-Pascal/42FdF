/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:46:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 18:32:16 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTIONS_H
# define PROJECTIONS_H

# include "typedefs.h"

t_vec2	orthographic_projection(t_vec2 pos, t_vec3 point3d);
t_vec2	isometric_projection(t_vec2 pos, t_vec3 point3d, t_map *map);

#endif
