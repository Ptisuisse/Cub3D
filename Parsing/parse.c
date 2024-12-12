/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:48:09 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/26 14:12:33 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_color(t_data_map *data_map)
{
	int	i;
	int	color_nb;

	i = 0;
	color_nb = 0;
	while (color_nb < 2)
	{
		while (data_map->line[0] == '\n')
		{
			free(data_map->line);
			data_map->line = get_next_line(data_map->fd);
		}
		while (data_map->line[i] == ' ')
			i++;
		if ((data_map->line[i] != 'F' && data_map->line[i] != 'C')
			|| (data_map->line[i] == 'F' && data_map->line[i + 1] != ' ')
			|| (data_map->line[i] == 'C' && data_map->line[i + 1] != ' '))
			ft_error("Can't read color\n", data_map);
		else
		{
			free(data_map->line);
			data_map->line = get_next_line(data_map->fd);
			color_nb++;
		}
	}
}

static void	if_check_texture(t_data_map *data_map, int i)
{
	if ((data_map->line[i] != 'N' && data_map->line[i] != 'S'
			&& data_map->line[i] != 'W' && data_map->line[i] != 'E')
		|| (data_map->line[i] == 'N' && data_map->line[i + 1] != 'O'
			&& data_map->line[i + 1] != ' ') || (data_map->line[i] == 'S'
			&& data_map->line[i + 1] != 'O' && data_map->line[i + 1] != ' ')
		|| (data_map->line[i] == 'W' && data_map->line[i + 1] != 'E'
			&& data_map->line[i + 1] != ' ') || (data_map->line[i] == 'E'
			&& data_map->line[i + 1] != 'A' && data_map->line[i + 1] != ' ')
		|| (data_map->line[i] == 'N' && data_map->line[i + 1] == 'O'
			&& data_map->line[i + 2] != ' ') || (data_map->line[i] == 'S'
			&& data_map->line[i + 1] == 'O' && data_map->line[i + 2] != ' ')
		|| (data_map->line[i] == 'W' && data_map->line[i + 1] == 'E'
			&& data_map->line[i + 2] != ' ') || (data_map->line[i] == 'E'
			&& data_map->line[i + 1] == 'A' && data_map->line[i + 2] != ' '))
		ft_error("Can't read texture\n", data_map);
}

void	check_texture(t_data_map *data_map)
{
	int	i;
	int	texture_nb;

	i = 0;
	texture_nb = 0;
	while (texture_nb < 4)
	{
		while (data_map->line[0] == '\n')
		{
			free(data_map->line);
			data_map->line = get_next_line(data_map->fd);
		}
		while (data_map->line[i] == ' ')
			i++;
		if_check_texture(data_map, i);
		free(data_map->line);
		data_map->line = get_next_line(data_map->fd);
		i = 0;
		texture_nb++;
	}
}

void	ft_open_map(char *str, t_data_map *data_map)
{
	data_map->fd = open(str, O_RDONLY);
	if (data_map->fd < 0)
	{
		close(data_map->fd);
		ft_error("Can't open map\n", data_map);
	}
	free(data_map->line);
	data_map->line = get_next_line(data_map->fd);
}

void	ft_read_map(char *str, t_data_map *data_map)
{
	int	i;

	ft_open_map(str, data_map);
	i = 0;
	while (data_map->line[0] == '\n')
	{
		free(data_map->line);
		data_map->line = get_next_line(data_map->fd);
	}
	while (data_map->line[i] == ' ')
		i++;
	if (data_map->line[i] != 'N' && data_map->line[i] != 'S'
		&& data_map->line[i] != 'W' && data_map->line[i] != 'E'
		&& data_map->line[i] != 'F' && data_map->line[i] != 'C')
		ft_error("Can't read map\n", data_map);
	if (data_map->line[i] == 'F' || data_map->line[i] == 'C')
		data_map->texture_color = true;
	else
		data_map->texture_color = false;
}
