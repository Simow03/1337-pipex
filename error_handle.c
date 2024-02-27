/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:37:38 by mstaali           #+#    #+#             */
/*   Updated: 2024/02/27 19:40:40 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_mssg(void)
{
	ft_putstr_fd ("\n\n\033[1;31;4m! INVALID ARGUMENTS !\033[0m"
		"\n\n\n\033[4mUSAGE:\033[0m\n\t./pipex [file_input] [cmd1] [cmd2]"
		" [file_output]\n\n", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	ft_putstr_fd ("\n\n\033[1;31;4m Error! :\033[0m\n\n", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
