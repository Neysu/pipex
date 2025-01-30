/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:53:55 by egibeaux          #+#    #+#             */
/*   Updated: 2025/01/30 22:24:12 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	closefd(t_pipe *args)
{
	close(args->pipefd[0]);
	close(args->pipefd[1]);
	free(args);
}

void	errorfd(char *file, t_pipe *args)
{
	closefd(args);
	perror(file);
	exit (1);
}

void	invalidcommand(t_pipe *args)
{
	msg("Invalid Command\n");
	(void)args;
	exit(1);
}
