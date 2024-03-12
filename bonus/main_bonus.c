/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:46:53 by mstaali           #+#    #+#             */
/*   Updated: 2024/03/12 17:06:55 by mstaali          ###   ########.fr       */
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute(av, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	last_command(char *av, char **envp, int fileout)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fileout, STDOUT_FILENO);
		execute(av, envp);
	}
	close(STDIN_FILENO);
	while (wait(NULL) != -1)
		continue ;
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
		last_command(av[ac - 2], envp, fileout);
	}
	else
		error_mssg_bonus();
}
