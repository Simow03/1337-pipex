/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:36:49 by mstaali           #+#    #+#             */
/*   Updated: 2024/03/07 00:01:44 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

char	*check_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!strncmp(envp[i], "PATH", 4))
			return (envp[i]);
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*b4_cmd;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		b4_cmd = ft_strjoin(paths[i], "/");
		path = ft_strjoin(b4_cmd, cmd);
		free(b4_cmd);
		if (access(path, F_OK & X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK & X_OK) == 0)
		if (execve(cmd[0], cmd, NULL) == -1)
			error();
	if (!check_envp(envp))
		error();
	path = find_path(cmd[0], envp);
	i = -1;
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}
