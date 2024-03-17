/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:43:23 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/14 15:55:34 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

# include "typedefs.h"

void	rotate(t_vec3 *rotated, t_vec3 input, t_trigo_table *table);
void	translate(t_vec3 *translated, t_vec3 input, t_vec3 *translate);
void	scale(t_vec3 *translated, t_vec3 input, t_vec3 *scale);

#endif
