/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:46:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/09 17:35:19 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTIONS_H
# define PROJECTIONS_H

# include "typedefs.h"

void	orthographic_projection(t_vec2 *output, t_fdf *fdf, t_vec3 point3d);
void	isometric_transform(t_vec3 *output, t_vec3 input, t_map *map);

#endif
