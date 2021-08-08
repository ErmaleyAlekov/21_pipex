/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/08 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct pipex
{
	char	*in_f;
	char	*out_f;
	char	**cmd1;
	char	**cmd2;
	int		fd[2];
	int		fdin;
	int		fdout;
	char	*bits;
	char	*pathcmd1;
	char	*pathcmd2;
	int		fork_id;
	int		flag1;
	int		flag2;
	char	**path;
}	t_pipex;

int				error(int ale);
void			init_struct(t_pipex *data);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				parse_data(t_pipex **data, char **argv, char **envp);
int				check_data(t_pipex *data);
int				ft_strlcpy(char *dst, const char *src, size_t dstsize);
unsigned int	ft_strlen(char const *str);

#endif
