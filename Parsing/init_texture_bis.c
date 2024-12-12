/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:11:18 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/05 11:45:11 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while ((s1 [i] != '\0' || s2 [i] != '\0')
		&& s1 [i] == s2 [i] && n - 1 > i)
		i++;
	return ((unsigned char)s1 [i] - s2 [i]);
}

char	*ft_strdup_newline(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void    check_texture_path(t_data_map *data_map)
{
    int fd;

    fd = open(data_map->no_texture, O_RDONLY);
    if (fd == -1)
        ft_error("NO texture path error\n", data_map);
    close(fd);
    fd = open(data_map->so_texture, O_RDONLY);
    if (fd == -1)
        ft_error("SO texture path error\n", data_map);
    close(fd);
    fd = open(data_map->we_texture, O_RDONLY);
    if (fd == -1)
        ft_error("WE texture path error\n", data_map);
    close(fd);
    fd = open(data_map->ea_texture, O_RDONLY);
    if (fd == -1)
        ft_error("EA texture path error\n", data_map);
    close(fd);
}
