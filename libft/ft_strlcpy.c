/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:15:20 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/20 04:37:52 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strlcpy(char *dest, char *src, int n)
{	
	int		i;

	i = -1;
	while (++i, src[i] && (i + 1) < n)
		dest[i] = src[i];
	if (n > 0)
		dest[i] = '\0';
}
