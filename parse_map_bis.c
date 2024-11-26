/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:59:23 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/26 14:08:08 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_to_data(t_data_map *data_map)
{
	static int	j = 0;

	if (!data_map->map)
	{
		data_map->map = malloc(sizeof(char *) * 100);
		if (!data_map->map)
			return ;
	}
	if (!data_map->line)
	{
		data_map->map[j] = NULL;
		return ;
	}
	data_map->map[j] = ft_strdup(data_map->line);
	j++;
}

void	check_map_char(t_data_map *data_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data_map->map[j])
	{
		while (data_map->map[j][i])
		{
			if (data_map->map[j][i] != '0' && data_map->map[j][i] != '1'
				&& data_map->map[j][i] != 'N' && data_map->map[j][i] != 'S'
				&& data_map->map[j][i] != 'W' && data_map->map[j][i] != 'E'
				&& data_map->map[j][i] != ' ' && data_map->map[j][i] != '\n')
				ft_error("Invalid map\n", data_map);
			i++;
		}
		i = 0;
		j++;
	}
}

void	not_double_player(t_data_map *data_map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	j = 0;
	player = 0;
	while (data_map->map[j])
	{
		while (data_map->map[j][i])
		{
			if (data_map->map[j][i] == 'N' || data_map->map[j][i] == 'S'
				|| data_map->map[j][i] == 'W' || data_map->map[j][i] == 'E')
				player++;
			i++;
		}
		i = 0;
		j++;
	}
	if (player != 1)
		ft_error("Not one player\n", data_map);
}

static void	while_map_is_closed(t_data_map *data_map, int i, int j)
{
	while (data_map->map[j])
	{
		if (!j || !data_map->map[j + 1])
		{
			while (data_map->map[j][i])
			{
				if (data_map->map[j][i] != '1' && data_map->map[j][i] != ' '
					&& data_map->map[j][i] != '\n')
					ft_error("Invalid map\n", data_map);
				i++;
			}
		}
		else
		{
			while (data_map->map[j][i])
				i++;
			if (data_map->map[j][i - 2] != '1')
				ft_error("Invalid map\n", data_map);
		}
		i = 0;
		j++;
	}
}

void	map_is_closed(t_data_map *data_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while_map_is_closed(data_map, i, j);
}
