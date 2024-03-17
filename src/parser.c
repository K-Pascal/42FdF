/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:12:35 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/12 17:12:24 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "typedefs.h"

static char	parse_mapinfo(t_map *info, int fd)
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
		if (info->num_values != (int)ft_countwords(str, ' '))
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

void	store_mapvalue(t_value data[], char str[])
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		data[i].altitudes = (float)ft_atoi(str);
		if (*str == '+' || *str == '-')
			str++;
		while (ft_isdigit(*str))
			str++;
		if (*str == ',')
		{
			str++;
			if (*str == '0')
				str++;
			if (*str == 'x' || *str == 'X')
				str++;
			data[i].color = ft_atoibase(str, "0123456789abcdef");
			if (data[i].color == 0)
				data[i].color = ft_atoibase(str, "0123456789ABCDEF");
		}
		else
			data[i].color = 0xFFFFFFFF;
		while (*str != '\0' && !ft_isspace(*str))
			str++;
		i++;
	}
}

static char	parse_mapdata(t_map *map, int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (i < map->num_lines)
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
		store_mapvalue(&map->data[i * map->num_values], str);
		free(str);
		i++;
	}
	return (1);
}

void	get_mapinfo(t_map *info, char const pathname[])
{
	int		fd;
	char	status;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	info->num_lines = 0;
	info->num_values = 0;
	status = parse_mapinfo(info, fd);
	if (close(fd) == -1)
		perror("get_mapinfo():close()");
	if (!status)
		exit(EXIT_FAILURE);
	info->data = ft_calloc(info->num_lines * info->num_values, sizeof(t_value));
	if (info->data == NULL)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
}

char	get_mapdata(t_map *map, char const pathname[])
{
	int		fd;
	char	status;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	status = parse_mapdata(map, fd);
	if (close(fd) == -1)
		perror("get_mapdata():close()");
	return (status);
}
