/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:06 by mstaali           #+#    #+#             */
/*   Updated: 2024/03/09 19:05:46 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

/* get_next_line */
# define BUFFER_SIZE 10240

/* libft */
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strdup(const char *str);

/* utils */
void	error(void);
void	error_mssg(void);
void	execute(char *av, char **envp);
char	*find_path(char *cmd, char **envp);

/* bonus */
void	error_mssg_bonus(void);
int		get_next_line(char **line);
void	here_doc(char *limiter, int ac);
int		which_open(char *av, char *flag);

#endif