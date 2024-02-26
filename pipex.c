/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:36:41 by mstaali           #+#    #+#             */
/*   Updated: 2024/02/26 21:41:36 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process1(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein < 0)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(av[2], envp);
}

static void	child_process2(char **av, char **envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (fileout < 0)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 < 0)
			error();
		if (pid1 == 0)
			child_process1(av, envp, fd);
		pid2 = fork();
		if (pid2 < 0)
			error();
		if (pid2 == 0)
			child_process2(av, envp, fd);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
	else
		error_mssg();
}
