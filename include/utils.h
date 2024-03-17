/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:52:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/04 19:28:21 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "typedefs.h"

void	init_mapdata(t_fdf *fdf, char const pathname[]);
void	init_mlx(t_fdf *fdf);
void	deinit_prog(t_fdf *fdf);

#endif
