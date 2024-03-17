/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:36:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/19 18:58:38 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# else
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

typedef struct s_line
{
	char	*content;
	int		len;
	int		size;
}	t_line;

int		isendl(char const s[], int n);

#endif
