/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:09:16 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/20 03:11:20 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	buffer_size(char *str, char delimiter, int i)
{
	while (str && *str)
	{
		if (*str != delimiter && (str[1] == delimiter || !str[1]))
			++i;
		++str;
	}
	return (i);
}

static int	freed_content(char **content, int elems, int free_content)
{
	if (free_content)
		while (elems--)
			free(content[elems]);
	return (free_content);
}

char	**ft_split(char const *__str, char delimiter)
{
	char	**result;
	char	*str;
	int		elems;
	int		i;

	str = (char *)__str;
	elems = ((i = 0));
	result = malloc(sizeof(char *) * buffer_size(str, delimiter, 1));
	if (!result || !str)
		return (NULL);
	while (*str)
	{
		if (*str != delimiter && (str[1] == delimiter || !str[1]))
		{
			result[elems++] = ft_substr(str - i, 0, i + 1);
			i = 0;
			if (freed_content(result, elems - 1, !result[elems - 1]))
				return (free(result), NULL);
		}
		else if (*str != delimiter)
			++i;
		++str;
	}
	return ((result[elems] = NULL), result);
}
