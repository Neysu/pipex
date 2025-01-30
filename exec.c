/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:28 by elliot            #+#    #+#             */
/*   Updated: 2025/01/30 21:02:45 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

char	*findcmd(t_pipe *args, char **envp)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	**path;
	
	i = 0;
	ret = NULL;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strsep(path[i], args->cmd[0], '/');
		if (!access(tmp, X_OK))
			ret = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	ft_free(path);
	return (ret);
}

void	openfile(t_pipe *args, char **argv, bool file)
{
	if (file)
	{
		args->infile = open(argv[1], O_RDONLY);
		if (args->infile == -1)
		{
			closefd(args);
			perror(MISS_INFILE);
			exit (1);
		}
		dup2(args->infile, 0);
		close(args->infile);
	}
	else
	{
		args->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (args->outfile == -1)
		{
			closefd(args);
			perror(MISS_OUTFILE);
			exit (1);
		}
		dup2(args->outfile, 1);
		close(args->outfile);
	}
}

void	cmd1(t_pipe *args, char **argv, char **envp)
{
	char 	*tmp;
	
	openfile(args, argv, true);
	args->cmd = ft_split(argv[2], ' ');
	tmp = findcmd(args, envp);
	if (!tmp)
	{
		closefd(args);
		invalidcommand(args);
		exit(1);
	}
	if (dup2(args->pipefd[1], 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	closefd(args);
	if (execve(tmp, args->cmd, envp))
	{
		perror("execve1");
		exit(1);
	}
	ft_free(args->cmd);
	exit(1);
}

void	cmd2(t_pipe *args, char **argv, char **envp)
{
	char 	*tmp;
	
	openfile(args, argv, false);
	args->cmd = ft_split(argv[3], ' ');
	tmp = findcmd(args, envp);
	if (!tmp)
	{
		closefd(args);
		invalidcommand(args);
		exit(1);
	}
	if (dup2(args->pipefd[0], 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	closefd(args);
	if (execve(tmp, args->cmd, envp))
	{
		perror("execve2");
		exit(1);
	}
	ft_free(args->cmd);
	exit(1);
}
