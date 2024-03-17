/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:20:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 19:02:25 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <X11/keysymdef.h>
#include <X11/X.h>

#include "minilibx-linux/mlx.h"

#include "events_utils.h"
#include "render.h"
#include "typedefs.h"

int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	if (button == Button1)
	{
		fdf->map.pos.x = x;
		fdf->map.pos.y = y;
	}
	else
		scroll_event(button, fdf);
	redraw_map(fdf);
	return (1);
}

int	key_released(int keycode, t_fdf *fdf)
{
	key_transform_release(keycode, fdf);
	if (keycode == ' ')
		fdf->transform &= ~K_MOD;
	else if (keycode == '-')
		fdf->transform &= ~K_MINUS;
	else if (keycode == '=')
		fdf->transform &= ~K_EQUAL;
	return (0);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fdf->mlx_ptr);
	else if (key_menu_pressed(keycode, fdf))
		redraw_map(fdf);
	key_transform_pressed(keycode, fdf);
	if (keycode == ' ')
		fdf->transform |= K_MOD;
	else if (keycode == '-')
		fdf->transform |= K_MINUS;
	else if (keycode == '=')
		fdf->transform |= K_EQUAL;
	return (0);
}
