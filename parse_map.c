/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:14:27 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/26 14:08:01 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	if_map_is_well_spaced(t_data_map *data_map, int i, int j)
{
	if (data_map->map[j][i] == '0')
	{
		if (data_map->map[j][i - 1] != 'N' && data_map->map[j][i - 1] != 'S'
			&& data_map->map[j][i - 1] != 'W' && data_map->map[j][i - 1] != 'E'
			&& data_map->map[j][i + 1] != 'N' && data_map->map[j][i + 1] != 'S'
			&& data_map->map[j][i + 1] != 'W' && data_map->map[j][i + 1] != 'E'
			&& data_map->map[j + 1] && data_map->map[j + 1][i] != 'N'
			&& data_map->map[j + 1][i] != 'S' && data_map->map[j + 1][i] != 'W'
			&& data_map->map[j + 1][i] != 'E' && j && data_map->map[j
			- 1][i] != 'N' && data_map->map[j - 1][i] != 'S' && data_map->map[j
			- 1][i] != 'W' && data_map->map[j - 1][i] != 'E'
			&& ((data_map->map[j][i + 1] != '0' && data_map->map[j][i
					+ 1] != '1') || (data_map->map[j + 1] && data_map->map[j
					+ 1][i] != '0' && data_map->map[j + 1][i] != '1') || (j
					&& data_map->map[j - 1][i] != '0' && data_map->map[j
					- 1][i] != '1')))
			ft_error("Invalid map\n", data_map);
	}
}

static void	while_map_is_well_spaced(t_data_map *data_map, int i, int j)
{
	while (data_map->map[j][i])
	{
		if_map_is_well_spaced(data_map, i, j);
		if (data_map->map[j][i] == 'N' || data_map->map[j][i] == 'S'
			|| data_map->map[j][i] == 'W' || data_map->map[j][i] == 'E')
		{
			if ((data_map->map[j][i - 1] != '0' && data_map->map[j][i
				- 1] != '1') || (data_map->map[j][i + 1] != '0'
				&& data_map->map[j][i + 1] != '1') || (data_map->map[j + 1]
				&& data_map->map[j + 1][i] != '0' && data_map->map[j
				+ 1][i] != '1') || (j && data_map->map[j - 1][i] != '0'
				&& data_map->map[j - 1][i] != '1'))
				ft_error("Invalid map\n", data_map);
		}
		i++;
	}
}

void	map_is_well_spaced(t_data_map *data_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data_map->map[j])
	{
		while_map_is_well_spaced(data_map, i, j);
		i = 0;
		j++;
	}
}

static void	while_map_exist(t_data_map *data_map, int i)
{
	while (data_map->line)
	{
		while (data_map->line && data_map->line[0] == '\n')
		{
			if (data_map->map)
				ft_error("Invalid map\n", data_map);
			free(data_map->line);
			data_map->line = get_next_line(data_map->fd);
		}
		while (data_map->line && data_map->line[i] == ' ')
			i++;
		if (data_map->line && data_map->line[i] != 'N'
			&& data_map->line[i] != 'S' && data_map->line[i] != 'W'
			&& data_map->line[i] != 'E' && data_map->line[i] != '1'
			&& data_map->line[i] != 'F' && data_map->line[i] != 'C'
			&& data_map->line[i] != '\n')
			ft_error("Invalid map\n", data_map);
		else if (data_map->line && data_map->line[i] == '1')
			map_to_data(data_map);
		else if (data_map->line && data_map->line[i] != '1' && data_map->map)
			ft_error("Invalid map\n", data_map);
		free(data_map->line);
		data_map->line = get_next_line(data_map->fd);
		i = 0;
	}
}

void	map_exist(char *str, t_data_map *data_map)
{
	int	i;

	i = 0;
	close(data_map->fd);
	data_map->fd = open(str, O_RDONLY);
	if (data_map->fd < 0)
		ft_error("Invalid map\n", data_map);
	free(data_map->line);
	data_map->line = get_next_line(data_map->fd);
	data_map->map = NULL;
	while_map_exist(data_map, i);
	map_to_data(data_map);
}
