/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:05 by lvan-slu          #+#    #+#             */
/*   Updated: 2024/11/26 11:32:06 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Taille de la map*/
void	size_of_map(t_data_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[map->x])
	{
		map->y = 0;
		while (map->map[map->x][map->y])
			map->y++;
		if (map->y > j)
			j = map->y;
		map->x++;
		if (map->x > i)
			i = map->x;
	}
	map->y = j;
	map->x = i;
}

/*Pose un carre de 10px * 10px*/
void	ft_put_pixel(t_data_map *map, int x, int y, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = x * 10;
	start_y = y * 10;
	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			mlx_pixel_put(map->mlx->ptr, map->mlx->win, start_y + j, start_x
				+ i, color);
			i++;
		}
		j++;
	}
}

///*Gestion minimap murs et sols*/
int	render_minimap_test(t_data_map *map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				ft_put_pixel(map, i, j, 0x87CEEB);
			else if (map->map[i][j] == '0')
				ft_put_pixel(map, i, j, 0xFFFFFF);
			else if (map->map[i][j] == 'N')
			{
				map->player_x = i;
				map->player_y = j;
				ft_put_pixel(map, i, j, 0xF00000);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	clear_fov_ray(t_data_map *map)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (map->map[map->player_x - 1][map->player_y] == '1')
			mlx_pixel_put(map->mlx->ptr, map->mlx->win, map->player_y * 10 + 5,
				map->player_x * 10 - i, 0x87CEEB);
		else if (map->map[map->player_x - 1][map->player_y] == '0')
			mlx_pixel_put(map->mlx->ptr, map->mlx->win, map->player_y * 10 + 5,
				map->player_x * 10 - i, 0xFFFFFF);
		i++;
	}
}

void	draw_fov_ray(t_data_map *map)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		mlx_pixel_put(map->mlx->ptr, map->mlx->win, map->player_y * 10 + 5,
			map->player_x * 10 - i, 0xF0000);
		i++;
	}
}

int	keyhook(int key, void *data)
{
	t_data_map	*map;

	map = (t_data_map *)data;
	if (key == 65307)
		mlx_destroy_window(map->mlx->ptr, map->mlx->win);
	if (key == 65364)
	{
		clear_fov_ray(map);
		if (map->map[map->player_x + 1][map->player_y] != '1')
		{
			ft_put_pixel(map, map->player_x, map->player_y, 0xFFFFFF);
			ft_put_pixel(map, map->player_x + 1, map->player_y, 0xF00000);
			map->player_x += 1;
		}
		draw_fov_ray(map);
	}
	if (key == 65362)
	{
		if (map->map[map->player_x - 1][map->player_y] != '1')
		{
			draw_fov_ray(map);
			ft_put_pixel(map, map->player_x, map->player_y, 0xFFFFFF);
			ft_put_pixel(map, map->player_x - 1, map->player_y, 0xF00000);
			map->player_x -= 1;
		}
		draw_fov_ray(map);
	}
	return (0);
}

int	ft_mlx_init(t_data_map *map)
{
	map->mlx->ptr = mlx_init();
	map->mlx->win = mlx_new_window(map->mlx->ptr, 1080, 720, "Cub3D");
	render_minimap_test(map);
	mlx_hook(map->mlx->win, 2, 1L << 0, keyhook, map);
	mlx_loop(map->mlx->ptr);
	return (0);
}
