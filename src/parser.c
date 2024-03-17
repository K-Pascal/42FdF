/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:12:35 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/05 15:34:19 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "typedefs.h"

char	read_file_info(int fd, t_info *info)
{
	char	*str;

	str = get_next_line(fd);
	if (str == NULL)
	{
		perror("get_next_line()");
		return (0);
	}
	info->num_values = ft_countwords(str, ' ');
	while (str != NULL)
	{
		info->num_lines++;
		if (info->num_values != ft_countwords(str, ' '))
		{
			ft_putendl_fd("Invalid map !", STDOUT_FILENO);
			free(str);
			return (0);
		}
		free(str);
		str = get_next_line(fd);
	}
	return (1);
}

void	get_info(char const pathname[], t_info *info)
{
	int		fd;
	char	status;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	status = read_file_info(fd, info);
	if (close(fd) == -1)
		perror("close()");
	if (!status)
		exit(EXIT_FAILURE);
}

int	*get_map(char const pathname[], t_info *info)
{
	int		fd;
	char	*str;
	char	**arr_str;
	int		*arr_int;
	size_t	i;
	size_t	j;

	get_info(pathname, info);
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	arr_int = malloc(info->num_lines * info->num_values * sizeof(int));
	if (arr_int == NULL)
	{
		close(fd);
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < info->num_lines)
	{
		str = get_next_line(fd);
		if (str == NULL)
		{
			perror("get_map():get_next_line()");
			close(fd);
			free(arr_int);
			exit(EXIT_FAILURE);
		}
		arr_str = ft_split(str, ' ');
		free(str);
		if (arr_str == NULL)
		{
			perror("ft_split()");
			close(fd);
			free(arr_int);
			exit(EXIT_FAILURE);
		}
		j = 0;
		while (arr_str[j] != NULL)
		{
			arr_int[i * info->num_values + j] = ft_atoi(arr_str[j]);
			j++;
		}
		ft_freeall(arr_str);
		i++;
	}
	close(fd);
	return (arr_int);
}