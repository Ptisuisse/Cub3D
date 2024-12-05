/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:21 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/05 11:34:26 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data(t_data_map **data_map)
{
	(*data_map) = malloc(sizeof(t_data_map));
	if (!(*data_map))
		ft_error("Malloc error\n", (*data_map));
	(*data_map)->fd = 0;
	(*data_map)->line = NULL;
	(*data_map)->texture_color = false;
	(*data_map)->no_texture = NULL;
	(*data_map)->so_texture = NULL;
	(*data_map)->we_texture = NULL;
	(*data_map)->ea_texture = NULL;
	(*data_map)->floor_color = NULL;
	(*data_map)->f_color = NULL;
	(*data_map)->ceiling_color = NULL;
	(*data_map)->c_color = NULL;
	(*data_map)->map = NULL;
	(*data_map)->pos = 0;
}

static void	check_texture_color(t_data_map *data_map)
{
	if (!data_map->texture_color)
	{
		check_texture(data_map);
		check_color(data_map);
	}
	if (data_map->texture_color)
	{
		check_color(data_map);
		check_texture(data_map);
	}
}

static void	check_argc(int argc, t_data_map *data_map)
{
	if (argc < 2)
		ft_error("Too few arguments\n", data_map);
	if (argc > 2)
		ft_error("Too many arguments\n", data_map);
}

static void	check_map(char **argv, t_data_map *data_map)
{
	map_is_not_cub(argv[1], data_map);
	ft_open_map(argv[1], data_map);
	ft_read_map(argv[1], data_map);
	check_texture_color(data_map);
	init_texture(argv[1], data_map);
	init_color(argv[1], data_map);
	map_exist(argv[1], data_map);
	map_is_closed(data_map);
	map_is_well_spaced(data_map);
	check_map_char(data_map);
	not_double_player(data_map);
}

int	main(int argc, char **argv)
{
	t_data_map	*data_map;

	data_map = NULL;
	init_data(&data_map);
	check_argc(argc, data_map);
	check_map(argv, data_map);
	check_texture_path(data_map);
	ft_error(NULL, data_map);
	return (0);
}
