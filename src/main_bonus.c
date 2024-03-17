/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:26:11 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minilibx-linux/mlx.h"

#include "frame_bonus.h"
#include "render.h"
#include "typedefs.h"
#include "utils.h"

void		reset_configuration(t_fdf *fdf);
static void	init_scene_data(t_fdf *fdf);

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_bzero(&fdf, sizeof(fdf));
	init_mapdata(&fdf, argv[1]);
	init_mlx(&fdf);
	reset_configuration(&fdf);
	init_scene_data(&fdf);
	render(&fdf);
	mlx_loop_hook(fdf.mlx_ptr, &update_frame, &fdf);
	mlx_loop(fdf.mlx_ptr);
	deinit_prog(&fdf);
	return (0);
}

static void	init_scene_data(t_fdf *fdf)
{
	fdf->transform = K_NONE;
	fdf->prev_time = 0ll;
	fdf->map.view_mode = V_ISOM;
	fdf->map.proj_mode = P_ORTHO;
	fdf->img.aspect_ratio = (float)fdf->img.height / (float)fdf->img.width;
}
