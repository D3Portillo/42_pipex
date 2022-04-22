/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:46:38 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/21 05:47:23 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t size)
{
	char	*result;
	int		i;

	if (!src)
		return (NULL);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i, i < (int)size)
		result[i] = src[start + i];
	result[i] = '\0';
	return (result);
}
