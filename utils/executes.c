/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:25:32 by dcerrito          #+#    #+#             */
/*   Updated: 2022/05/08 13:52:24 by dcerrito       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*get_path(char *program, char **environ)
{
	char	**paths;
	char	*full_path;
	char	*root_path;
	int		i;

	i = -1;
	paths = ((full_path = (root_path = NULL)), NULL);
	while (program && environ[++i])
	{
		if (ft_strnstr(environ[i], "PATH=", 5))
		{
			paths = ft_split(&environ[i][5], ':');
			i = -1;
			while (free_all(2, root_path, full_path), paths)
			{
				root_path = ft_strjoin(paths[++i], "/");
				full_path = ft_strjoin(root_path, program);
				if (!root_path || !full_path)
					return (free_all(3, paths, root_path, full_path));
				if (access(full_path, F_OK) == F_OK)
					return (free_all(2, paths, root_path), full_path);
			}
		}
	}
	return (NULL);
}

int	executes(char *arg, char **environ)
{
	char	**path_args;
	char	*path;
	int		result;

	path_args = ft_split(arg, ' ');
	path = get_path(path_args[0], environ);
	if (!path || !path_args)
		result = -1;
	else
		result = execve(path, &path_args[0], environ);
	return (free_all(2, path, path_args), result);
}
