/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:12:35 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/05 19:53:13 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "typedefs.h"

static char	parse_mapinfo(t_info *info, int fd)
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
	info->num_values = ft_countwords(str, ' ');
	while (str != NULL)
	{
		if (info->num_values != ft_countwords(str, ' '))
		{
			ft_putendl_fd("Invalid map !", STDERR_FILENO);
			free(str);
			return (0);
		}
		free(str);
		info->num_lines++;
		str = get_next_line(fd);
	}
	return (1);
}

static char	store_mapvalue(int arr_ints[], char str[])
{
	size_t	i;
	char	**arr_str;

	arr_str = ft_split(str, ' ');
	if (arr_str == NULL)
	{
		perror("store_mapvalue():ft_split()");
		return (0);
	}
	i = 0;
	while (arr_str[i] != NULL)
	{
		arr_ints[i] = ft_atoi(arr_str[i]);
		i++;
	}
	ft_freeall(arr_str);
	return (1);
}

static char	parse_mapdata(int arr_ints[], int fd, t_info *info)
{
	size_t	i;
	char	*str;
	char	status;

	i = 0;
	while (i < info->num_lines)
	{
		str = get_next_line(fd);
		if (str == NULL)
		{
			if (errno)
				perror("parse_mapdata():get_next_line()");
			else
				ft_putendl_fd("Incomplete map !", STDERR_FILENO);
			return (0);
		}
		status = store_mapvalue(&arr_ints[i * info->num_values], str);
		free(str);
		if (!status)
			return (0);
		i++;
	}
	return (1);
}

void	get_mapinfo(t_info *info, char const pathname[])
{
	int		fd;
	char	status;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	status = parse_mapinfo(info, fd);
	if (close(fd) == -1)
		perror("get_mapinfo():close()");
	if (!status)
		exit(EXIT_FAILURE);
}

char	get_mapdata(int arr_ints[], char const pathname[], t_info *info)
{
	int		fd;
	char	status;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	status = parse_mapdata(arr_ints, fd, info);
	if (close(fd) == -1)
		perror("get_mapdata():close()");
	return (status);
}
