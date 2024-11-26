/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:07:58 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/26 14:11:17 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_to_eof(char *str, t_data_map *data_map)
{
	while (data_map->line)
	{
		free(data_map->line);
		data_map->line = get_next_line(data_map->fd);
	}
	close(data_map->fd);
	ft_open_map(str, data_map);
}

void	map_is_not_cub(char *str, t_data_map *data_map)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i
			- 4] != '.')
		ft_error("Map is not .cub\n", data_map);
}

void	ft_error(char *str, t_data_map *data_map)
{
	int	i;

	i = 0;
	if (!str)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	if (data_map->fd >= 0)
		close(data_map->fd);
	free(data_map->line);
	free(data_map->no_texture);
	free(data_map->so_texture);
	free(data_map->we_texture);
	free(data_map->ea_texture);
	free(data_map->floor_color);
	free(data_map->ceiling_color);
	i = 0;
	while (data_map->map && data_map->map[i])
	{
		free(data_map->map[i]);
		i++;
	}
	free(data_map);
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
