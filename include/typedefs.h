/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:54:41 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/26 15:22:53 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

#include <stddef.h>

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_win
{
	void	*ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_fdf
{
	void	*mlx_ptr;
	t_win	win;
	t_img	img;
}	t_fdf;

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_info
{
	size_t	num_lines;
	size_t	num_values;
}	t_info;

#endif
