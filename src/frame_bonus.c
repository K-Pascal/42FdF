/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:14:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:17:47 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "frame_utils_bonus.h"
#include "render.h"
#include "typedefs.h"

static long long	get_actual_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000ll + t.tv_usec / 1000ll);
}

int	update_frame(t_fdf *fdf)
{
	float	delta_time;

	if (fdf->prev_time == 0ll)
		delta_time = 0.f;
	else
		delta_time = (float)(get_actual_time() - fdf->prev_time) / 1000.f;
	fdf->prev_time = get_actual_time();
	if (fdf->transform == K_NONE || fdf->transform == K_MOD)
		return (0);
	rotate_x(delta_time, fdf);
	rotate_y(delta_time, fdf);
	rotate_z(delta_time, fdf);
	translate_xyz(delta_time, fdf);
	scale_z(delta_time, fdf);
	redraw_map(fdf);
	return (0);
}
