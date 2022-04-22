/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:25:32 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/22 05:36:11 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*get_path(char *program, char **environ)
{
	char	**parsed_env;
	char	*full_path;
	char	*root_path;
	int		i;

	i = -1;
	while (program && environ[++i])
	{
		if (ft_strnstr(environ[i], "PATH=", 5))
		{
			parsed_env = ft_split(&environ[i][5], ':');
			i = -1;
			while (parsed_env && parsed_env[++i])
			{
				root_path = ft_strjoin(parsed_env[i], "/");
				full_path = ft_strjoin(root_path, program);
				if (!root_path || !full_path)
					break ;
				if (access(full_path, F_OK) == F_OK)
					return (free_all(2, parsed_env, root_path), full_path);
			}
		}
	}
	return (free_all(3, parsed_env, root_path, full_path));
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
