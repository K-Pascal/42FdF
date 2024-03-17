/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:56:45 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/06 16:20:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "typedefs.h"

void	get_mapinfo(t_map *info, char const pathname[]);
char	get_mapdata(t_map *map, char const pathname[]);

#endif
