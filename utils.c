/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:53:55 by egibeaux          #+#    #+#             */
/*   Updated: 2025/01/28 23:12:23 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	closefd(t_pipe *args)
{
	close(args->pipefd[0]);
	close(args->pipefd[1]);
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
	free(args);
	exit(1);
}
