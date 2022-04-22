/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:27:52 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/22 05:30:22 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*free_all(int items, ...)
{
	va_list	list;
	void	*node;

	va_start(list, items);
	while (items--)
	{
		free((node = va_arg(list, void *)));
		node = NULL;
	}
	return (va_end(list), NULL);
}
