/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:36:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/19 18:56:59 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "get_next_line.h"

static void	absorb_buffer(t_line *line, char buffer[BUFFER_SIZE + 1]);
static void	my_alloccpy(t_line *line, int size);
static void	my_realloc(t_line *line, int targetsize);
static char	append_line(t_line *line, char buffer[BUFFER_SIZE + 1], int bytes);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		bytes;
	t_line		line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	absorb_buffer(&line, buffer);
	if (line.content != NULL && buffer[0] != '\0')
		return (line.content);
	line.size = line.len + 1;
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		bytes = append_line(&line, buffer, bytes);
		if (bytes <= 0)
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes == -1)
		free(line.content);
	if (bytes == -1 || (bytes <= 0 && line.len == 0))
		return (NULL);
	my_alloccpy(&line, line.len + 1);
	return (line.content);
}

static void	absorb_buffer(t_line *line, char buffer[BUFFER_SIZE + 1])
{
	int		pos;
	int		isnl;

	line->len = 0;
	if (buffer[0] == '\0')
	{
		line->content = NULL;
		return ;
	}
	pos = isendl(buffer, BUFFER_SIZE + 1);
	isnl = buffer[pos] == '\n';
	line->content = malloc((pos + 1 + isnl) * sizeof(char));
	if (line->content == NULL)
		return ;
	if (pos != -1)
		line->len = pos + isnl;
	else
		line->len = ft_strlen(buffer);
	ft_strlcpy(line->content, buffer, line->len + 1);
	if (pos != -1)
		ft_strlcpy(buffer, buffer + pos + isnl, BUFFER_SIZE + 1 - pos);
	else
		buffer[0] = '\0';
}

static char	append_line(t_line *line, char buffer[BUFFER_SIZE + 1], int bytes)
{
	int		i;
	char	no_end;

	i = isendl(buffer, bytes);
	no_end = i == -1;
	if (!no_end)
		bytes = i + (buffer[i] == '\n');
	my_realloc(line, line->len + bytes + 1);
	if (line->content == NULL)
		return (-1);
	ft_strlcpy(line->content + line->len, buffer, bytes + 1);
	line->len += bytes;
	if (no_end)
		buffer[0] = '\0';
	else
	{
		ft_strlcpy(buffer, buffer + i + 1, BUFFER_SIZE - i);
		buffer[BUFFER_SIZE - i] = '\0';
	}
	return (no_end);
}

static void	my_realloc(t_line *line, int newsize)
{
	while (line->size < newsize)
	{
		line->size *= 2;
		if (line->size < newsize)
			continue ;
		my_alloccpy(line, line->size);
	}
}

static void	my_alloccpy(t_line *line, int size)
{
	char	*temp;

	temp = malloc(size * sizeof(char));
	if (temp == NULL)
	{
		free(line->content);
		line->content = NULL;
		return ;
	}
	if (line->content != NULL)
		ft_strlcpy(temp, line->content, line->len + 1);
	free(line->content);
	line->content = temp;
}
