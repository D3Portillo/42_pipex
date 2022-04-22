/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 03:08:54 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/21 06:52:14 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../includes/core.h"

char	**ft_split(char const *str, char delimiter);
void	ft_strcpy(char *dest, char *src, int limit);
char	*ft_strdup(char *source);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strlcat(char *dest, const char *src, size_t n);
void	ft_strlcpy(char *dest, char *src, int n);
int		ft_strlen(char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *src, unsigned int start, size_t size);

#endif