/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 04:22:06 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/21 05:40:01 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strlcat(char *dest, const char *__src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	dest_size;
	char	*src;

	src = (char *)__src;
	dest_size = ft_strlen(dest);
	i = dest_size;
	j = 0;
	while (src[j] && (i + 1) < n)
		dest[i++] = src[j++];
	if (n > 0 && dest_size <= n)
		dest[i] = '\0';
}
