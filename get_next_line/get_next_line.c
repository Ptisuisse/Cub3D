/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:53:33 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/17 12:57:12 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_buftostr(str, fd);
	if (!str)
		return (NULL);
	line = ft_getline(str);
	str = ft_clear(str);
	return (line);
}

char	*ft_buftostr(char *str, int fd)
{
	int		chrd;
	char	*buf;

	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	chrd = 1;
	if (!str)
		str = ft_calloc(sizeof(char), 1);
	while (chrd != 0 && !ft_strchr(buf, '\n'))
	{
		chrd = read(fd, buf, BUFFER_SIZE);
		if (chrd == -1)
		{
			free(str);
			free(buf);
			return (NULL);
		}
		buf[chrd] = '\0';
		str = ft_strjoin_gnl(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_getline(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = str[i];
	return (line);
}

char	*ft_clear(char *str)
{
	int		i;
	int		j;
	char	*nstr;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	nstr = ft_calloc(sizeof(char), ft_strlen(str) - i + 1);
	if (!nstr)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		nstr[j++] = str[i++];
	free (str);
	return (nstr);
}
