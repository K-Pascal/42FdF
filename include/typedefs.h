/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:54:41 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/08 21:04:36 by pnguyen-         ###   ########.fr       */
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
	float	x;
	float	y;
	float	z;
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
	int				num_lines;
	int				num_values;
	t_vec2			pos;
	int				translation_offset;
	t_trigo_table	table;
	t_vec3			scale;
	t_vec3			center;
	t_vec3			*last_row;
}	t_map;

typedef enum e_transform
{
	K_NONE = 0,
	K_ROTATE_X = (1u << 0),
	K_RROTATE_X = (1u << 1),
	K_ROTATE_Y = (1u << 2),
	K_RROTATE_Y = (1u << 3),
	K_ROTATE_Z = (1u << 4),
	K_RROTATE_Z = (1u << 5),
	K_MOVE = (1u << 6),
	K_MOD = (1u << 7)
}	t_transform;

typedef struct s_fdf
{
	void		*mlx_ptr;
	t_win		win;
	t_img		img;
	t_map		map;
	t_transform	transform;
}	t_fdf;

#endif
