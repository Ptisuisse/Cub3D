/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:25 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/04 19:35:03 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	is_c_color(char *str, int i, t_data_map *data_map)
{
	if (str && str[i] == 'C')
	{
		if (data_map->ceiling_color)
			ft_error("Double in color\n", data_map);
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			data_map->ceiling_color = ft_strdup(&str[i]);
		else
			ft_error("Can't read color\n", data_map);
	}
}

static void	is_f_color(char *str, int i, t_data_map *data_map)
{
	if (str && str[i] == 'F')
	{
		if (data_map->floor_color)
			ft_error("Double in color\n", data_map);
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			data_map->floor_color = ft_strdup(&str[i]);
		else
			ft_error("Can't read color\n", data_map);
	}
}

static void	parse_colors(t_data_map **data_map)
{
	(*data_map)->f_color = malloc(sizeof(int) * 4);
	if (!(*data_map)->f_color)
		ft_error("Malloc error\n", (*data_map));
	(*data_map)->f_color[0] = ft_atoi((*data_map)->floor_color, (*data_map));
	(*data_map)->f_color[1] = ft_atoi((*data_map)->floor_color, (*data_map));
	(*data_map)->f_color[2] = ft_atoi((*data_map)->floor_color, (*data_map));
	(*data_map)->f_color[3] = -1;
	(*data_map)->c_color = malloc(sizeof(int) * 4);
	if (!(*data_map)->c_color)
		ft_error("Malloc error\n", (*data_map));
	(*data_map)->c_color[0] = ft_atoi((*data_map)->ceiling_color, (*data_map));
	(*data_map)->c_color[1] = ft_atoi((*data_map)->ceiling_color, (*data_map));
	(*data_map)->c_color[2] = ft_atoi((*data_map)->ceiling_color, (*data_map));
	(*data_map)->c_color[3] = -1;
}

void	init_color(char *str, t_data_map *data_map)
{
	int	i;

	i = 0;
	go_to_eof(str, data_map);
	while (data_map->line)
	{
		while (data_map->line && data_map->line[0] == '\n')
		{
			free(data_map->line);
			data_map->line = get_next_line(data_map->fd);
		}
		while (data_map->line && data_map->line[i] == ' ')
			i++;
		is_f_color(data_map->line, i, data_map);
		is_c_color(data_map->line, i, data_map);
		free(data_map->line);
		data_map->line = get_next_line(data_map->fd);
		i = 0;
	}
	if (!data_map->floor_color || !data_map->ceiling_color)
		ft_error("Double in color\n", data_map);
	parse_colors(&data_map);
	f_to_hexa(&data_map);
	c_to_hexa(&data_map);
}
