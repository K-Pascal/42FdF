/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:56:45 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/05 17:47:15 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "typedefs.h"

void	get_mapinfo(t_info *info, char const pathname[]);
char	get_mapdata(int arr_int[], char const pathname[], t_info *info);

#endif
