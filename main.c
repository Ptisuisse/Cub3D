/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:21 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/05 13:58:46 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_ply **ply)
{
	(*ply) = malloc(sizeof(t_ply));
	(*ply)->dir_angle = 3 * PI / 2;
	(*ply)->player_x = 0.0;
	(*ply)->player_y = 0.0;
	(*ply)->ray_ngl = PI;
	(*ply)->fov = (FOV * PI) / 180;
}

static void	init_data(t_data_map **data_map)
{
	(*data_map) = malloc(sizeof(t_data_map));
	if (!(*data_map))
		ft_error("Malloc error\n", (*data_map));
	(*data_map)->fd = 0;
	(*data_map)->x = 0;
	(*data_map)->y = 0;
	(*data_map)->p_x = 0;
	(*data_map)->p_y = 0;
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
	(*data_map)->minimap = false;
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
	t_ply		*ply;
	t_mlx		*mlx;
	t_data_map	*data_map;

	mlx = malloc(sizeof(t_mlx));
	data_map = NULL;
	ply = NULL;
	init_data(&data_map);
	init_player(&ply);
	check_argc(argc, data_map);
	check_map(argv, data_map);
	size_of_map(data_map);
	check_texture_path(data_map);
	mlx->map = data_map;
	mlx->ply = ply;
	ft_mlx_init(mlx);
	ft_error(NULL, data_map);
	return (0);
}
