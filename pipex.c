/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:36:41 by mstaali           #+#    #+#             */
/*   Updated: 2024/02/26 17:42:21 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		error_mssg();
}
