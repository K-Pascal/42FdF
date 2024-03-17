/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/29 19:51:29 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

#include "events_utils.h"
#include "render.h"
#include "typedefs.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	init_mapdata(&fdf, argv[1]);
	init_trigo_table(&fdf.map.table);
	init_mlx(&fdf);
	fdf.transform = K_NONE;
	fdf.map.translate_offset = (float)(my_min(fdf.map.num_values,
			fdf.map.num_lines));
	fdf.prev_time = 0ll;
	fdf.map.view_mode = V_ISOM;
	fdf.map.proj_mode = P_ORTHO;
	reset_configuration(&fdf);
	render(&fdf);
	mlx_loop(fdf.mlx_ptr);
	deinit_prog(&fdf);
	return (0);
}
