/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:12:35 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/15 17:18:12 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser_utils.h"
#include "typedefs.h"

static int	add_to_node(t_list **data, char str[], int num_values)
{
	t_list			*node;
	static t_list	*current;

	node = store_mapvalue(str, num_values);
	if (node == NULL)
		return (0);
	if (current == NULL)
	{
		current = node;
		*data = current;
	}
	else
	{
		current->next = node;
		current = current->next;
	}
	return (1);
}

static int	read_file(t_map *info, int fd, char str[])
{
	int	status;

	while (str != NULL)
	{
		status = info->num_values == (int)ft_countwords(str, ' ');
		if (!status)
		{
			ft_putendl_fd("Invalid map !", STDERR_FILENO);
			break ;
		}
		status = add_to_node(&(info->data), str, info->num_values);
		if (!status)
			break ;
		free(str);
		info->num_lines++;
		str = get_next_line(fd);
	}
	if (status)
		return (1);
	ft_lstclear(&(info->data), &free);
	free(str);
	return (0);
}

static int read_map(t_map *info, int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (str == NULL)
	{
		if (errno)
			perror("parse_mapinfo():get_next_line()");
		else
			ft_putendl_fd("Empty map !", STDERR_FILENO);
		return (0);
	}
	info->num_values = (int)ft_countwords(str, ' ');
	return (read_file(info, fd, str));
}

void	get_mapinfo(t_map *info, char const pathname[])
{
	int		fd;
	int		status;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	info->num_lines = 0;
	info->num_values = 0;
	status = read_map(info, fd);
	if (close(fd) == -1)
		perror("get_mapinfo():close()");
	if (!status)
		exit(EXIT_FAILURE);
}
