/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:52:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/07 15:39:38 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "typedefs.h"

void	put_pixel(t_img	*img, int x, int y, int color);
void	init_trigo_table(t_trigo table[SIZE_TRIGO_TABLE]);
int		min(int a, int b);

#endif
