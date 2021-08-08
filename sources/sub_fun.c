/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/08 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error(int ale)
{
	if (ale == 1)
		return (write(1, "Error\n", 7));
	return (-1);
}

void	init_struct(t_pipex *data)
{
	data->cmd1 = 0;
	data->cmd2 = 0;
	data->fd[0] = 0;
	data->fdin = 0;
	data->fdout = 0;
	data->fork_id = 0;
	data->in_f = 0;
	data->out_f = 0;
	data->pathcmd1 = 0;
	data->pathcmd2 = 0;
	data->path = 0;
}

static	int	ft_nomer_stroki(char const *stroka, char c)
{
	unsigned int	i;
	unsigned int	nomer;

	if (!stroka[0])
		return (0);
	i = 0;
	nomer = 0;
	while (stroka[i] && stroka[i] == c)
		i++;
	while (stroka[i])
	{
		if (stroka[i] == c)
		{
			nomer++;
			while (stroka[i] && stroka[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (stroka[i - 1] != c)
		nomer++;
	return (nomer);
}

static void	ft_sled_stroka(char **sledstr, unsigned int *sleddlina,
	char c)
{
	unsigned int	i;

	*sledstr += *sleddlina;
	*sleddlina = 0;
	i = 0;
	while (**sledstr && **sledstr == c)
		(*sledstr)++;
	while ((*sledstr)[i])
	{
		if ((*sledstr)[i] == c)
			return ;
		(*sleddlina)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	unsigned int	nomer;
	char			**otvet;
	unsigned int	sleddlina;
	char			*sledstr;
	unsigned int	i;

	if (!s)
		return (0);
	nomer = ft_nomer_stroki(s, c);
	otvet = malloc(sizeof(char *) * (nomer + 1));
	i = 0;
	sledstr = (char *)s;
	sleddlina = 0;
	if (!otvet)
		return (0);
	while (i < nomer)
	{
		ft_sled_stroka(&sledstr, &sleddlina, c);
		otvet[i] = malloc(sizeof(char) * (sleddlina + 1));
		ft_strlcpy(otvet[i], sledstr, sleddlina + 1);
		i++;
	}
	otvet[i] = 0;
	return (otvet);
}
