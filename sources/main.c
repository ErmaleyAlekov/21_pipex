/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/08 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	exec_cmd(t_pipex *data, char **envp, int ale)
{
	if (ale == 1)
	{
		dup2(data->fd[1], 1);
		dup2(data->fdin, 0);
		if (execve(data->pathcmd1, data->cmd1, envp) == -1)
			return (error(1));
	}
	if (ale == 2)
	{
		close(data->fdin);
		close(data->fd[1]);
		dup2(data->fd[0], 0);
		dup2(data->fdout, 1);
		close(data->fdout);
		close(data->fd[0]);
		if (execve(data->pathcmd2, data->cmd2, envp) == -1)
			return (error(1));
	}
	return (1);
}

static	int	exec_pipe(t_pipex *data, char **envp)
{
	data->fork_id = fork();
	if (data->fork_id == 0)
	{
		exec_cmd(data, envp, 1);
		exit(0);
	}
	else if (data->fork_id == -1)
		return (error(1));
	else
	{
		waitpid(data->fork_id, 0, 0);
		exec_cmd(data, envp, 2);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;

	if (argc != 5)
		return (-1);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (-1);
	init_struct(data);
	if (parse_data(&data, argv, envp) == -1)
		return (error(1));
	if (check_data(data) == -1)
		return (error(1));
	if (pipe(data->fd) != 0)
		return (error(1));
	if (exec_pipe(data, envp) == -1)
		return (error(1));
	free(data);
	return (0);
}
