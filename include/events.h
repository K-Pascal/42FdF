/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:26:27 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:23:28 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "typedefs.h"

int	mouse_pressed(int button, int x, int y, t_fdf *fdf);
int	key_released(int keycode, t_fdf *fdf);
int	key_pressed(int keycode, t_fdf *fdf);

#endif
