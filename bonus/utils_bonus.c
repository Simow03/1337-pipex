/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:17:57 by mstaali           #+#    #+#             */
/*   Updated: 2024/03/10 18:39:09 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	which_open(char *av, char *flag)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(flag, "append", 6) == 0)
		fd = open(av, O_CREAT | O_RDWR | O_APPEND, 0744);
	else if (ft_strncmp(flag, "trunc", 5) == 0)
		fd = open(av, O_CREAT | O_RDWR | O_TRUNC, 0744);
	else if (ft_strncmp(flag, "rdonly", 6) == 0)
		fd = open(av, O_RDONLY);
	if (fd < 0)
		error();
	return (fd);
}

static void	check_line(char *line, char *limiter, int *fd)
{
	write(0, "> ", 2);
	while (get_next_line(&line))
	{
		if (ft_strlen(line) == (ft_strlen(limiter) + 1)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			exit(EXIT_SUCCESS);
		write(0, "> ", 2);
		write(fd[1], line, ft_strlen(line));
	}
}

void	here_doc(char *limiter, int ac)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	line = NULL;
	if (ac < 6)
		error_mssg_bonus();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		check_line(line, limiter, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
