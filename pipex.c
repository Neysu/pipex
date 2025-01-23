/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:25:05 by elliot            #+#    #+#             */
/*   Updated: 2025/01/23 16:22:55 by elliot           ###   ########.fr       */
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
	int		pid;
	t_pipe	*args;
	
	args = ft_calloc(sizeof(t_pipe), 1);
	if (argc != 5)
		return (msg("Invalid numbers of arguments\n"));
	pipe(args->pipefd);
	pid = fork();
	if (pid == -1) {
        perror("fork failed");
        return (1);
    }
	if (pid == 0)
		cmd1(args, argv, envp);
	else
		pid = fork();
	if (pid == 0)
		cmd2(args, argv, envp);
	close(args->pipefd[0]);
	close(args->pipefd[1]);
	wait(NULL);
	wait(NULL);
	free(args);
	return (1);
}