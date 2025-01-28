/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:25:05 by elliot            #+#    #+#             */
/*   Updated: 2025/01/28 22:10:10 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <stdlib.h>

int		msg(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

void	ft_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int 	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	pid_t	pid2;
	int		status;
	if (argc != 5)
		return (msg("Invalid numbers of arguments\n"));
	args = ft_calloc(sizeof(t_pipe), 1);
	pipe(args->pipefd)
	pid = fork();
	if (pid == -1) {
        perror("fork failed");
        exit (1);
    }
	if (pid == 0)
		cmd1(args, argv, envp);
	else
		pid2 = fork();
	if (pid2 == 0)
		cmd2(args, argv, envp);
	closefd(args);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status, 0);
	free(args);
	return (1);
}
