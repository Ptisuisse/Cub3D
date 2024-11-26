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
	while (map->map[map->y])
	{
		map->x = 0;
		while (map->map[map->y][map->x])
		{
			if (map->map[map->y][map->x] == 'N')
			{
				map->player_x = map->x;
				map->player_y = map->y;
			}
			map->x++;
		}
		if (map->x > j)
			j = map->x;
		map->y++;
		if (map->y > i)
			i = map->y;
	}
	map->x = j;
	map->y = i;
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
			mlx_pixel_put(map->mlx->ptr, map->mlx->win, start_y + i, start_x
				+ j, color);
			i++;
		}
		j++;
	}
}
void	draw_fov_ray(t_data_map *map);

///*Gestion minimap murs et sols*/
int	render_minimap_test(t_data_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				ft_put_pixel(map, y, x, 0x87CEEB);
			else if (map->map[y][x] == '0')
				ft_put_pixel(map, y, x, 0xFFFFFF);
			else if (map->map[y][x] == 'N')
			{
				map->player_x = x;
				map->player_y = y;
				//---------------> changer emplacement init joueur
				ft_put_pixel(map, y, x, 0xF00000);
			}
			x++;
		}
		y++;
	}
	map->minimap = true;
	draw_fov_ray(map);
	return (1);
}

/*creation / suppression du rayon*/
void	clear_fov_ray(t_data_map *map)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (map->map[map->player_y - 1][map->player_x] == '1')
			mlx_pixel_put(map->mlx->ptr, map->mlx->win, map->player_x * 10 + 5,
				map->player_y * 10 - i, 0x87CEEB);
		else if (map->map[map->player_y - 1][map->player_x] == '0')
			mlx_pixel_put(map->mlx->ptr, map->mlx->win, map->player_x * 10 + 5,
				map->player_y * 10 - i, 0xFFFFFF);
		i++;
	}
}

void	draw_fov_ray(t_data_map *map)
{
	int	j;
	int	i;
	int	save_x;
	int	save_y;

	j = 0;
	save_y = map->player_y;
	save_x = map->player_x;
	i = 0;
	while (map->map[save_y - 1][save_x] == '0')
	{
		save_y--;
		i++;
	}
	i *= 10;
	while (j < i)
	{
		mlx_pixel_put(map->mlx->ptr, map->mlx->win, map->player_x * 10 + 5,
			map->player_y * 10 + 0.6 - j, 0xF00000);
		j++;
	}
}

int	keyhook(int key, void *data)
{
	t_data_map	*map;

	map = (t_data_map *)data;
	if (key == 65307)
		mlx_destroy_window(map->mlx->ptr, map->mlx->win);
	if (key == 109)
	{
		if (map->minimap == false)
			render_minimap_test(map);
		else
		{
			mlx_clear_window(map->mlx->ptr, map->mlx->win);
			map->minimap = false;
		}
	}
	if (map->minimap == true)
	{
		if (key == 65364)
		{
			if (map->map[map->player_y + 1][map->player_x] != '1')
			{
				map->map[map->player_y][map->player_x] = '0';
				ft_put_pixel(map, map->player_y, map->player_x, 0xFFFFFF);
				ft_put_pixel(map, map->player_y + 1, map->player_x, 0xF00000);
				map->player_y += 1;
				map->map[map->player_y][map->player_x] = 'N';
			}
			draw_fov_ray(map);
		}
		if (key == 65362)
		{
			if (map->map[map->player_y - 1][map->player_x] != '1')
			{
				map->map[map->player_y][map->player_x] = '0';
				ft_put_pixel(map, map->player_y, map->player_x, 0xFFFFFF);
				ft_put_pixel(map, map->player_y - 1, map->player_x, 0xF00000);
				map->player_y -= 1;
				map->map[map->player_y][map->player_x] = 'N';
			}
			draw_fov_ray(map);
		}
		if (key == 65361) // gauche
		{
			map->map[map->player_y][map->player_x] = '0';
			ft_put_pixel(map, map->player_y, map->player_x, 0xFFFFFF);
			ft_put_pixel(map, map->player_y, map->player_x - 1, 0xF00000);
			map->player_x -= 1;
			draw_fov_ray(map);
			map->map[map->player_y][map->player_x] = 'N';
		}
		if (key == 65363) // droite
		{
			map->map[map->player_y][map->player_x] = '0';
			ft_put_pixel(map, map->player_y, map->player_x, 0xFFFFFF);
			ft_put_pixel(map, map->player_y, map->player_x + 1, 0xF00000);
			map->player_x += 1;
			draw_fov_ray(map);
			map->map[map->player_y][map->player_x] = 'N';
		}
	}
	return (0);
}

int	ft_mlx_init(t_data_map *map)
{
	map->mlx->ptr = mlx_init();
	map->mlx->win = mlx_new_window(map->mlx->ptr, 1080, 720, "Cub3D");
	// render_minimap_test(map);
	mlx_hook(map->mlx->win, 2, 1L << 0, keyhook, map);
	mlx_loop(map->mlx->ptr);
	return (0);
}
