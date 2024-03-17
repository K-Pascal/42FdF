/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:20:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/16 19:05:16 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <X11/keysymdef.h>
#include <X11/X.h>

#include "minilibx-linux/mlx.h"

#include "typedefs.h"
#include "render.h"
#include "events_utils.h"

int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	if (button == Button1)
	{
		fdf->map.pos.x = x;
		fdf->map.pos.y = y;
		reset_map(fdf);
		render(fdf);
	}
	if (button == Button4)
	{
		fdf->map.scale.x *= 1.1f;
		fdf->map.scale.y *= 1.1f;
		fdf->map.scale.z *= 1.1f;
		reset_map(fdf);
		render(fdf);
	}
	else if (button == Button5)
	{
		fdf->map.scale.x *= 0.9f;
		fdf->map.scale.y *= 0.9f;
		fdf->map.scale.z *= 0.9f;
		reset_map(fdf);
		render(fdf);
	}
	return (1);
}

int	key_released(int keycode, t_fdf *fdf)
{
	if (!keycode)
		return (0);
	if (keycode == 'd')
		fdf->transform &= ~K_D;
	else if (keycode == 'a')
		fdf->transform &= ~K_A;
	else if (keycode == 'w')
		fdf->transform &= ~K_W;
	else if (keycode == 's')
		fdf->transform &= ~K_S;
	else if (keycode == 'q')
		fdf->transform &= ~K_Q;
	else if (keycode == 'e')
		fdf->transform &= ~K_E;
	else if (keycode == ' ')
		fdf->transform &= ~K_MOD;
	else if (keycode == '-')
		fdf->transform &= ~K_MINUS;
	else if (keycode == '=')
		fdf->transform &= ~K_EQUAL;
	return (0);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (!keycode)
		return (0);
	if (keycode == XK_Escape)
		mlx_loop_end(fdf->mlx_ptr);
	else if (keycode == '0')
	{
		reset_configuration(fdf);
		reset_map(fdf);
		render(fdf);
	}
	else if (keycode == 'd')
		fdf->transform |= K_D;
	else if (keycode == 'a')
		fdf->transform |= K_A;
	else if (keycode == 'w')
		fdf->transform |= K_W;
	else if (keycode == 's')
		fdf->transform |= K_S;
	else if (keycode == 'q')
		fdf->transform |= K_Q;
	else if (keycode == 'e')
		fdf->transform |= K_E;
	else if (keycode == ' ')
		fdf->transform |= K_MOD;
	else if (keycode == '-')
		fdf->transform |= K_MINUS;
	else if (keycode == '=')
		fdf->transform |= K_EQUAL;
	return (0);
}
