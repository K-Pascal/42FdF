/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:29:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 19:07:06 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

#include "draw_line.h"
#include "projections.h"
#include "render_utils.h"
#include "typedefs.h"

static void	render_row(t_list *line, int y, t_fdf *fdf);

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

static void	render_lines(t_list *line, int y, int x, t_fdf *fdf)
{
	float	z;
	t_vec2	projection;
	t_vec3	point3d;

	z = ((t_value *)line->content)[x].altitude - fdf->map.center.z;
	if (fdf->map.proj_mode == P_PERSP)
		z *= fdf->map.scale.z;
	point3d = transform_points((float)(x) - fdf->map.center.x,
			(float)(y) - fdf->map.center.y,
			z,
			fdf);
	orthographic_projection(&projection, fdf, point3d);
	if (x)
		draw_line(&fdf->img, fdf->map.last, projection,
			((t_value *)line->content)[x].color);
	if (y)
		draw_line(&fdf->img, fdf->map.last_row[x], projection,
			((t_value *)line->content)[x].color);
	fdf->map.last = projection;
	fdf->map.last_row[x] = projection;
}

static void	render_row(t_list *line, int y, t_fdf *fdf)
{
	int	x;
	int	num_values;

	num_values = fdf->map.num_values;
	x = 0;
	while (x < num_values)
	{
		render_lines(line, y, x, fdf);
		x++;
	}
}
