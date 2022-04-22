/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:45:45 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/21 05:47:20 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *source)
{
	int		size;
	char	*dest;

	if (!source)
		return (NULL);
	size = ft_strlen(source);
	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, source, size);
	dest[size] = '\0';
	return (dest);
}
