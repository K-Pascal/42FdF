/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:02:09 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 17:48:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_UTILS_H
# define EVENTS_UTILS_H

# include "typedefs.h"

void	reset_configuration(t_fdf *fdf);
void	scroll_event(int button, t_fdf *fdf);
void	key_transform_release(int keycode, t_fdf *fdf);
int		key_menu_pressed(int keycode, t_fdf *fdf);
void	key_transform_pressed(int keycode, t_fdf *fdf);

#endif
