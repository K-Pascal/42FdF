/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:29:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 18:08:29 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#include "render_utils.h"
#include "typedefs.h"

void	render(t_fdf *fdf)
{
	int		y;
	t_list	*line;

	y = 0;
	line = fdf->map.data;
	while (line != NULL)
	{
		render_row(line, y, fdf);
		line = line->next;
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win.ptr, fdf->img.ptr, 0, 0);
}

void	redraw_map(t_fdf *fdf)
{
	ft_bzero(fdf->img.data, fdf->img.size_line * fdf->img.height);
	mlx_clear_window(fdf->mlx_ptr, fdf->win.ptr);
	render(fdf);
}
