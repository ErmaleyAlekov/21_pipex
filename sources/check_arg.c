/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/08 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	parse_cmd(t_pipex **data, char *argv, int cmd)
{
	if (cmd == 1)
	{
		(*data)->cmd1 = ft_split(argv, ' ');
	}
	else
		(*data)->cmd2 = ft_split(argv, ' ');
	if (ft_strncmp(argv, "/", 1) == 0
		|| ft_strncmp(argv, "./", 2) == 0
		|| ft_strncmp(argv, "../", 3) == 0)
	{
		if (cmd == 1)
			(*data)->flag1 = 1;
		else
			(*data)->flag2 = 1;
	}
	return (1);
}

static	int	parse_path(t_pipex **data, char **envp)
{
	char	*path;
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
	{
		env = ft_split(envp[i], '=');
		if (!ft_strncmp("PATH", env[0], 5))
		{
			path = env[1];
			if (path == 0 && ((*data)->flag1 == 0 || (*data)->flag2 == 0))
				return (-1);
			(*data)->path = ft_split(path, ':');
			free(env);
			return (1);
		}
		i++;
		free(env);
	}
	return (-1);
}

int	parse_data(t_pipex **data, char **argv, char **envp)
{
	(*data)->in_f = argv[1];
	(*data)->out_f = argv[4];
	if (!parse_cmd(data, argv[2], 1) || !parse_cmd(data, argv[3], 2))
		return (-1);
	if (!parse_path(data, envp))
		return (-1);
	return (0);
}

static	int	check_path(t_pipex **data, char **path, char *cmd)
{
	int		i;
	char	*ale;

	i = 0;
	while ((*data)->path[i])
	{
		ale = ft_strjoin((*data)->path[i], "/");
		ale = ft_strjoin(ale, cmd);
		if (open(ale, O_RDONLY) != -1)
		{
			*path = ale;
			cmd = ale;
			return (1);
		}
		free(ale);
		i++;
	}
	return (0);
}

int	check_data(t_pipex *data)
{
	data->fdin = open(data->in_f, O_RDWR);
	if (data->fdin < 0)
		return (error(1));
	data->fdout = open(data->out_f, O_RDWR | O_TRUNC | O_CREAT);
	if (data->fdout < 0)
		return (error(1));
	if (data->flag1 == 0)
	{
		if (!check_path(&data, &data->pathcmd1, data->cmd1[0]))
			return (error(1));
	}
	else
		data->pathcmd1 = data->cmd1[0];
	if (data->flag2 == 0)
	{
		if (!check_path(&data, &data->pathcmd2, data->cmd2[0]))
			return (error(1));
	}
	else
		data->pathcmd2 = data->cmd2[0];
	return (0);
}
