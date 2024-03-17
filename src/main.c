/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/05 14:26:50 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minilibx-linux/mlx.h"

#include "render.h"
#include "typedefs.h"
#include "utils.h"

#define SCALE_Z	5.f

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
	mlx_loop(fdf.mlx_ptr);
	deinit_prog(&fdf);
	return (0);
}

static void	init_scene_data(t_fdf *fdf)
{
	t_list	*node;
	int		i;

	node = fdf->map.data;
	while (node != NULL)
	{
		i = 0;
		while (i < fdf->map.num_values)
		{
			((t_value *)node->content)[i].color = 0xFFFFFFFF;
			i++;
		}
		node = node->next;
	}
	fdf->map.scale.z = SCALE_Z;
	fdf->transform = K_NONE;
	fdf->prev_time = 0ll;
	fdf->map.view_mode = V_ISOM;
	fdf->map.proj_mode = P_ORTHO;
	fdf->img.aspect_ratio = (float)fdf->img.height / (float)fdf->img.width;
}
