/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:43:23 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/29 19:32:18 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

# include "typedefs.h"

void	rotate(float output[4][4], t_trigo_table *table);
void	translate(float output[4][4], t_vec3 *translate);
void	scale(float output[4][4], t_vec3 *scale);
void	isometric_transform(float output[4][4]);
void	cabinet_transform(float output[4][4]);

#endif
