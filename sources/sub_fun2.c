/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_fun2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/08 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rezult;
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	rezult = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (!rezult)
		return (0);
	while (*s1)
		rezult[i++] = *s1++;
	while (*s2)
		rezult[i++] = *s2++;
	rezult[i] = '\0';
	return (rezult);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	if (!dst || !src)
		return (0);
	a = 0;
	while (src[a])
		a++;
	if (dstsize == 0)
		return (a);
	a = 0;
	while (src[a] && a < dstsize - 1)
	{
		dst[a] = src[a];
		a++;
	}
	dst[a] = 0;
	a = 0;
	while (src[a])
		a++;
	return (a);
}

unsigned int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
