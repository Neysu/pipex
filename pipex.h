/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:22:26 by elliot            #+#    #+#             */
/*   Updated: 2025/01/30 22:49:42 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef MISS_INFILE
#  define MISS_INFILE "Infile error"
# endif
# ifndef MISS_OUTFILE
#  define MISS_OUTFILE "outfile error"
# endif

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_pipe
{
	int		pipefd[2];
	char	**cmd;
	int		infile;
	int		outfile;

}	t_pipe;

int		msg(char *s);

char	*findcmd(t_pipe *args, char **envp);

void	ft_free(char **arr);
void	closefd(t_pipe *args);
void	invalidcommand(t_pipe *args);
void	errorfd(char *file, t_pipe *args);
void	cmd2(t_pipe *args, char **argv, char **envp);
void	cmd1(t_pipe *args, char **argv, char **envp);

#endif