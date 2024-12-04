/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:59:23 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/04 19:40:52 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void define_pos(t_data_map *data_map, int i, int j)
{
	if (data_map->map[j][i] == 'N')
		data_map->pos = pi/2;
	else if (data_map->map[j][i] == 'S')
		data_map->pos = 3*pi/2;
	else if (data_map->map[j][i] == 'E')
		data_map->pos = 0;
	else if (data_map->map[j][i] == 'W')
		data_map->pos = pi;
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
			define_pos(data_map, i, j);
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
