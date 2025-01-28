/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:28 by elliot            #+#    #+#             */
/*   Updated: 2025/01/28 14:58:51 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


void	invalidcommand(t_pipe *args)
{
	msg("Invalid Command\n");
	free(args);
	exit(1);
}

char	*findcmd(t_pipe *args, char **envp)
{
	int		i;
	char	*tmp;
	char	**path;
	
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, args->cmd[0]);
		printf("tmp: %s\n", tmp);
		if (!access(tmp, X_OK))
		{
			ft_free(path);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free(path);
	return (NULL);
}

void	cmd1(t_pipe *args, char **argv, char **envp)
{
	char *tmp;
	
	args->infile = open(argv[1], O_RDONLY);
	if (args->infile == -1)
	{
		perror(MISS_INFILE);
		exit (1);
	}
	dup2(args->infile, STDIN_FILENO);
	close(args->infile);
	args->cmd = ft_split(argv[2], ' ');
	tmp = findcmd(args, envp);
	if (!tmp)
	{
		invalidcommand(args);
		exit(1);
	}
	dup2(args->pipefd[1], STDOUT_FILENO);
	close(args->pipefd[0]);
	close(args->pipefd[1]);
	execve(tmp, args->cmd, envp);
	free(tmp);
}

void	cmd2(t_pipe *args, char **argv, char **envp)
{
	char *tmp;
	
	printf("test\n");
	args->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 644);
	{
		perror(MISS_OUTFILE);
		exit (1);
	}
	dup2(args->outfile, STDOUT_FILENO);
	close(args->outfile);
	args->cmd = ft_split(argv[3], ' ');
	tmp = ft_strjoin("/bin/", args->cmd[0]);
	if (access(tmp, 0))
	{
		invalidcommand(args);
		free(tmp);
		exit(1);
	}
	dup2(args->pipefd[0], STDIN_FILENO);
	close(args->pipefd[1]);
	close(args->pipefd[0]);
	execve(tmp, args->cmd, envp);
	free(tmp);
}
