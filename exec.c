/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:28 by elliot            #+#    #+#             */
/*   Updated: 2025/01/28 14:23:50 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	invalidcommand(t_pipe *args)
{
	msg("Invalid Command\n");
	free(args);
	exit(1);
}

void	cmd1(t_pipe *args, char **argv, char **envp)
{
	char *tmp;
	
	args->infile = open(argv[1], O_RDONLY);
	if (args->infile == -1)
	{
		perror(MISS_INFILE);
		free(args);
		exit (1);
	}
	dup2(args->infile, STDIN_FILENO);
	close(args->infile);
	args->cmd = ft_split(argv[2], ' ');
	tmp = ft_strjoin("/bin/", args->cmd[0]);
	if (access(tmp, 0))
	{
		invalidcommand(args);
		free(tmp);
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
	
	args->outfile = open(argv[4], O_WRONLY);
	if (args->outfile == -1)
	{
		perror(MISS_OUTFILE);
		free(args);
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
