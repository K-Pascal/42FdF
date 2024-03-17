/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:52:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/16 19:01:06 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "typedefs.h"

void	init_mapdata(t_fdf *fdf, char pathname[]);
void	init_mlx(t_fdf *fdf);
void	init_trigo_table(t_trigo_table *table);
void	deinit_prog(t_fdf *fdf);


#endif
