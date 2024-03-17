/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:56:34 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 17:50:38 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "defines.h"
#include <X11/keysymdef.h>
#include <X11/X.h>

#include "typedefs.h"

#define DEFAULT_INV_FOV 144.f

void	reset_configuration(t_fdf *fdf)
{
	fdf->map.scale.x = (float)fdf->img.width / 2.f / (float)fdf->map.num_values;
	fdf->map.scale.y = (float)fdf->img.height / 2.f / (float)fdf->map.num_lines;
	fdf->map.scale.z = 1.f;
	fdf->map.translate.x = 0.f;
	fdf->map.translate.y = 0.f;
	if (fdf->map.num_values > fdf->map.num_lines)
		fdf->map.translate.z = -(float)fdf->map.num_values;
	else
		fdf->map.translate.z = -(float)fdf->map.num_lines;
	fdf->map.pos.x = fdf->img.width / 2;
	fdf->map.pos.y = fdf->img.height / 2;
	fdf->map.inv_fov = DEFAULT_INV_FOV;
	fdf->map.fov = 1.f / tanf(3.14159f / fdf->map.inv_fov);
	fdf->map.table.angle_x = 0.f;
	fdf->map.table.angle_y = 0.f;
	fdf->map.table.angle_z = 0.f;
	fdf->map.table.x.cos = 1.f;
	fdf->map.table.x.sin = 0.f;
	fdf->map.table.y.cos = 1.f;
	fdf->map.table.y.sin = 0.f;
	fdf->map.table.z.cos = 1.f;
	fdf->map.table.z.sin = 0.f;
}

void	scroll_event(int button, t_fdf *fdf)
{
	if (button == Button4)
	{
		fdf->map.scale.x *= 1.1f;
		fdf->map.scale.y *= 1.1f;
		if (fdf->map.proj_mode == P_ORTHO)
			fdf->map.scale.z *= 1.1f;
		else
			fdf->map.inv_fov *= 1.1f;
		fdf->map.fov = 1.f / tanf(3.14159f / fdf->map.inv_fov);
	}
	else if (button == Button5)
	{
		fdf->map.scale.x *= 0.9f;
		fdf->map.scale.y *= 0.9f;
		if (fdf->map.proj_mode == P_ORTHO)
			fdf->map.scale.z *= 0.9f;
		else
			fdf->map.inv_fov *= 0.9f;
		fdf->map.fov = 1.f / tanf(3.14159f / fdf->map.inv_fov);
	}
}

void	key_transform_release(int keycode, t_fdf *fdf)
{
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
	else if (keycode == 'j')
		fdf->transform &= ~K_J;
	else if (keycode == 'i')
		fdf->transform &= ~K_I;
	else if (keycode == 'l')
		fdf->transform &= ~K_L;
	else if (keycode == 'k')
		fdf->transform &= ~K_K;
	else if (keycode == 'u')
		fdf->transform &= ~K_U;
	else if (keycode == 'o')
		fdf->transform &= ~K_O;
}

int	key_menu_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == '0')
		reset_configuration(fdf);
	else if (keycode == '1')
	{
		reset_configuration(fdf);
		fdf->map.proj_mode = P_ORTHO;
	}
	else if (keycode == '2')
	{
		reset_configuration(fdf);
		fdf->map.proj_mode = P_PERSP;
	}
	else if (keycode == '5')
		fdf->map.view_mode = V_NONE;
	else if (keycode == '6')
		fdf->map.view_mode = V_ISOM;
	else if (keycode == '7')
		fdf->map.view_mode = V_CABI;
	else
		return (0);
	return (1);
}

void	key_transform_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == 'd')
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
	else if (keycode == 'j')
		fdf->transform |= K_J;
	else if (keycode == 'i')
		fdf->transform |= K_I;
	else if (keycode == 'l')
		fdf->transform |= K_L;
	else if (keycode == 'k')
		fdf->transform |= K_K;
	else if (keycode == 'u')
		fdf->transform |= K_U;
	else if (keycode == 'o')
		fdf->transform |= K_O;
}
