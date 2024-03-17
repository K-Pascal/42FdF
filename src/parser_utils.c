/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:02:35 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/15 16:30:56 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "typedefs.h"

static char	*parse_values(t_value value[], size_t index, char str[])
{
	value[index].altitudes = (float)ft_atoi(str);
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
		value[index].color = ft_atoibase(str, "0123456789abcdef");
		if (!value[index].color)
			value[index].color = ft_atoibase(str, "0123456789ABCDEF");
	}
	else
		value[index].color = 0xFFFFFFFF;
	return (str);
}

static void	parse_line(t_value value[], char str[])
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		str = parse_values(value, i, str);
		while (*str != '\0' && !ft_isspace(*str))
			str++;
		i++;
	}
}

t_list	*store_mapvalue(char str[], int num_values)
{
	t_list	*node;
	t_value	*value;

	value = malloc(num_values * sizeof(t_value));
	if (value == NULL)
	{
		perror("store_mapvalue():malloc()");
		return (NULL);
	}
	parse_line(value, str);
	node = ft_lstnew(value);
	if (node == NULL)
	{
		perror("store_mapvalue():ft_lstnew()");
		return (NULL);
	}
	return (node);
}
