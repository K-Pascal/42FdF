/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_utils_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:09:36 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:24:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_UTILS_BONUS_H
# define FRAME_UTILS_BONUS_H

# include "typedefs.h"

void	rotate_x(float delta_time, t_fdf *fdf);
void	rotate_y(float delta_time, t_fdf *fdf);
void	rotate_z(float delta_time, t_fdf *fdf);
void	translate_xyz(float delta_time, t_fdf *fdf);
void	scale_z(float delta_time, t_fdf *fdf);

#endif
