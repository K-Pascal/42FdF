/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:46:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:22:34 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTIONS_H
# define PROJECTIONS_H

# include "typedefs.h"

void	orthographic_projection(t_vec2 *output, t_fdf *fdf, t_vec3 point3d);
void	perspective_projection(float output[4][4],
			float aspect_ratio, float fov);

#endif
