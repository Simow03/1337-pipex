/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:46:53 by mstaali           #+#    #+#             */
/*   Updated: 2024/03/10 18:13:04 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	child_process(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	filein;
	int	fileout;
	int	i;

	if (ac >= 5)
	{
		if (ft_strlen(av[1]) == 8 && ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = which_open(av[ac - 1], "append");
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			filein = which_open(av[1], "rdonly");
			fileout = which_open(av[ac - 1], "trunc");
			dup2(filein, STDIN_FILENO);
		}
		while (i < ac - 2)
			child_process(av[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
	error_mssg_bonus();
}
