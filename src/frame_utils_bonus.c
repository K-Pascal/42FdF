/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:05:43 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:06:53 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "typedefs.h"

#define MY_PI 3.14159f

void	rotate_x(float delta_time, t_fdf *fdf)
{
	if (fdf->transform & K_W)
	{
		fdf->map.table.angle_x += MY_PI * delta_time;
		while (fdf->map.table.angle_x > MY_PI)
			fdf->map.table.angle_x -= 2.f * MY_PI;
		fdf->map.table.x.cos = cosf(fdf->map.table.angle_x);
		fdf->map.table.x.sin = sinf(fdf->map.table.angle_x);
	}
	if (fdf->transform & K_S)
	{
		fdf->map.table.angle_x -= MY_PI * delta_time;
		while (fdf->map.table.angle_x < -MY_PI)
			fdf->map.table.angle_x += 2.f * MY_PI;
		fdf->map.table.x.cos = cosf(fdf->map.table.angle_x);
		fdf->map.table.x.sin = sinf(fdf->map.table.angle_x);
	}
}

void	rotate_y(float delta_time, t_fdf *fdf)
{
	if (fdf->transform & K_D)
	{
		fdf->map.table.angle_y += MY_PI * delta_time;
		while (fdf->map.table.angle_y > MY_PI)
			fdf->map.table.angle_y -= 2.f * MY_PI;
		fdf->map.table.y.cos = cosf(fdf->map.table.angle_y);
		fdf->map.table.y.sin = sinf(fdf->map.table.angle_y);
	}
	if (fdf->transform & K_A)
	{
		fdf->map.table.angle_y -= MY_PI * delta_time;
		while (fdf->map.table.angle_y < -MY_PI)
			fdf->map.table.angle_y += 2.f * MY_PI;
		fdf->map.table.y.cos = cosf(fdf->map.table.angle_y);
		fdf->map.table.y.sin = sinf(fdf->map.table.angle_y);
	}
}

void	rotate_z(float delta_time, t_fdf *fdf)
{
	if (fdf->transform & K_Q)
	{
		fdf->map.table.angle_z -= MY_PI * delta_time;
		while (fdf->map.table.angle_z > MY_PI)
			fdf->map.table.angle_z -= 2.f * MY_PI;
		fdf->map.table.z.cos = cosf(fdf->map.table.angle_z);
		fdf->map.table.z.sin = sinf(fdf->map.table.angle_z);
	}
	if (fdf->transform & K_E)
	{
		fdf->map.table.angle_z += MY_PI * delta_time;
		while (fdf->map.table.angle_z < -MY_PI)
			fdf->map.table.angle_z += 2.f * MY_PI;
		fdf->map.table.z.cos = cosf(fdf->map.table.angle_z);
		fdf->map.table.z.sin = sinf(fdf->map.table.angle_z);
	}
}

void	translate_xyz(float delta_time, t_fdf *fdf)
{
	if (fdf->transform & K_I)
		fdf->map.translate.y -= fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_K)
		fdf->map.translate.y += fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_L)
		fdf->map.translate.x += fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_J)
		fdf->map.translate.x -= fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_U)
		fdf->map.translate.z -= fdf->map.translate_offset * delta_time;
	if (fdf->transform & K_O)
		fdf->map.translate.z += fdf->map.translate_offset * delta_time;
}

void	scale_z(float delta_time, t_fdf *fdf)
{
	if (fdf->transform & K_MINUS)
	{
		if (fdf->transform & K_MOD)
			fdf->map.scale.z -= 10.f * delta_time;
		else
			fdf->map.scale.z -= 1.f * delta_time;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = -1.f;
	}
	if (fdf->transform & K_EQUAL)
	{
		if (fdf->transform & K_MOD)
			fdf->map.scale.z += 10.f * delta_time;
		else
			fdf->map.scale.z += 1.f * delta_time;
		if (fdf->map.scale.z == 0.f)
			fdf->map.scale.z = 1.f;
	}
}
