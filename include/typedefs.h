/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:54:41 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 18:05:25 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# define SIZE_TRIGO_TABLE 36

# include <stddef.h>

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

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	char	*data;
	int		bytes_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_win
{
	void	*ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_trigo
{
	float	cos;
	float	sin;
}	t_trigo;

typedef struct s_trigo_table
{
	t_trigo	trigo[SIZE_TRIGO_TABLE];
	int		x;
	int		y;
	int		z;
}	t_trigo_table;

typedef struct s_map
{
	int				*altitudes;
	size_t			num_lines;
	size_t			num_values;
	t_vec2			pos;
	int				translation_offset;
	t_trigo_table	table;
}	t_map;

typedef struct s_fdf
{
	void	*mlx_ptr;
	t_win	win;
	t_img	img;
	t_map	map;
}	t_fdf;

#endif
