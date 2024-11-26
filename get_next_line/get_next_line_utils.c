/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:57:39 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/17 12:57:53 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	total;

	total = nmemb * size;
	if (!total)
		return (malloc(1));
	if (nmemb > INT_MAX || size > INT_MAX)
		return (NULL);
	if (!nmemb || !size)
		return (NULL);
	res = (char *)malloc(total);
	if (!res)
		return (NULL);
	ft_memset(res, 0, total);
	return ((void *)res);
}

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return ((char *)s1);
	if (!s1)
		return ((char *)s2);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (c > 256)
		c -= 256;
	while (s[i] != '\0')
		i++;
	while (s[j] != c)
	{
		j++;
		if (s[j] == '\0' && s[j] != c)
			return (NULL);
	}
	return ((char *)s + j);
}
