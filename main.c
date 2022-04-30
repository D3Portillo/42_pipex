/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:15:34 by dcerrito          #+#    #+#             */
/*   Updated: 2022/04/30 22:57:26 by dcerrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

extern char	**environ;

static int	werror(char *text)
{
	char	*error_text;
	int		fd;

	fd = STDERR_FILENO;
	error_text = text;
	if (!text)
		error_text = strerror(errno);
	write(fd, "\n=======PIPEX=======\n", 21);
	write(fd, "ERROR, ", 7);
	write(fd, error_text, ft_strlen(error_text));
	write(fd, "\n", 1);
	return (exit(EXIT_FAILURE), EXIT_FAILURE);
}

static int	fork_and_run(int fd[2], int stdin, int stdout, char *command)
{
	int	child;

	child = fork();
	if (child < 0)
		return (werror("Failed to fork()"));
	if (child == 0)
	{
		dup2(stdout, STDOUT_FILENO);
		dup2(stdin, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (executes(command, environ) < 0)
			return (werror("Couldn't find command"));
	}
	return (child);
}

int	main(int argc, char **argv)
{
	int	in_file;
	int	out_file;
	int	fd[2];
	int	childs[2];

	if (argc != 5)
		return (werror("Expected \"./pipex infile cmd1 cmd2 outfile\""));
	if (!environ)
		return (werror("No env found :("));
	unlink(argv[4]);
	in_file = open(argv[1], O_RDONLY);
	if (in_file < 0)
		return (werror("Infile not found :("));
	out_file = open(argv[4], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (pipe(fd) < 0)
		return (werror("Failed to pipe()"));
	childs[0] = fork_and_run(fd, in_file, fd[1], argv[2]);
	childs[1] = fork_and_run(fd, fd[0], out_file, argv[3]);
	close(fd[0]);
	close(fd[1]);
	waitpid(childs[0], NULL, 0);
	waitpid(childs[1], NULL, 0);
	return (EXIT_SUCCESS);
}
