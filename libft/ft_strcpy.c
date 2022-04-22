/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:46:06 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/21 05:47:42 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dest, char *src, int limit)
{	
	int	i;

	if (!dest || !src)
		return ;
	i = -1;
	while (++i, src[i] && i < limit)
		dest[i] = src[i];
}
