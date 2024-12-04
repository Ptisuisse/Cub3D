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
				map->player_x = (double)map->x;
				map->player_y = (double)map->y;
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

void ft_put_pixel_player(t_data_map *map, double y, double x, int color)
{
    int i;
    int j;
    int start_x;
    int start_y;

    // Center player position
    start_x = (int)((x) * 10);
    start_y = (int)((y) * 10);
    
    // Draw 10x10 player sprite
    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 10; i++)
        {
            mlx_pixel_put(map->mlx->ptr, map->mlx->win, 
                         start_x + i, start_y + j, color);
        }
    }
}

void draw_fov_ray(t_data_map *map)
{       // 60 degrés
    const int NUM_RAYS = 100;
    const double ANGLE_STEP = FOV / NUM_RAYS;
    double start_angle = map->dir_angle - FOV / 2;

    for (int ray = 0; ray < NUM_RAYS; ray++)
    {
        double ray_x = map->player_x + 0.5;
        double ray_y = map->player_y + 0.5;
        double angle = start_angle + (ray * ANGLE_STEP);
        
        while (map->map[(int)ray_y][(int)ray_x] != '1')
        {
            mlx_pixel_put(map->mlx->ptr, map->mlx->win, 
                         ray_x * 10, ray_y * 10, 0xFF0000);
            ray_x += cos(angle) * 0.01;
            ray_y += sin(angle) * 0.01;
        }
    }
}
void ft_put_pixel_rotated(t_data_map *map, int x, int y, int color, double angle)
{
    double center_x = x * 10 + 5;  // Centre du carré (x * 10 + half square)
    double center_y = y * 10 + 5;  // Centre du carré (y * 10 + half square)
    
    for (int j = -5; j < 5; j++)  // From -5 to 4 to center
    {
        for (int i = -5; i < 5; i++)  // From -5 to 4 to center
        {
            // Rotation autour du centre
            double rot_x = i * cos(angle) - j * sin(angle);
            double rot_y = i * sin(angle) + j * cos(angle);
            
            // Ajouter l'offset du centre
            int final_x = center_x + rot_x;
            int final_y = center_y + rot_y;
            
            mlx_pixel_put(map->mlx->ptr, map->mlx->win, final_x, final_y, color);
        }
    }
}
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

int	render_minimap(t_data_map *map)
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
			else
				ft_put_pixel(map, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	//ft_put_pixel_player(map, map->player_y, map->player_x, 0x00FF00);
	map->minimap = true;
	draw_fov_ray(map);
	return (1);
}


/*Directions*/

int	keyhook(int key, t_data_map	*map)
{
	double new_x;
    double new_y;

	if (key == 65307)
	{
		mlx_clear_window(map->mlx->ptr, map->mlx->win);
		exit(0);
	}
    if (key == 65362) // Flèche haut (avancer)
    {
        new_x = map->player_x + cos(map->dir_angle) * 0.5;
        new_y = map->player_y + sin(map->dir_angle) * 0.5;
        
        // Vérification collision
        if (map->map[(int)new_y][(int)new_x] != '1')
        {
            map->player_x = new_x;
            map->player_y = new_y;
        }
    }
	if (key == 65364)
	{
		new_x = map->player_x - cos(map->dir_angle) * 0.1;
		new_y = map->player_y - sin(map->dir_angle) * 0.1;
		
		// Vérification collision
		if (map->map[(int)new_y][(int)new_x] != '1')
		{
			map->player_x = new_x;
			map->player_y = new_y;
		}
	}
	if (key == 65361)
	{
		map->dir_angle -= 0.1;
		if (map->dir_angle < 0)
		{
			map->dir_angle += 2 * PI;
		}
	}
	if (key == 65363)
	{
		map->dir_angle += 0.1;
		if (map->dir_angle < 0)
		{
			map->dir_angle += 2 * PI;
		}
	}
    // Même logique pour reculer avec flèche bas (65364)
	mlx_clear_window(map->mlx->ptr, map->mlx->win);
	render_minimap(map);
	ft_put_pixel_rotated(map, map->player_x, map->player_y, 0x00FF00, map->dir_angle);
	draw_fov_ray(map); 
   	//mlx_clear_window(map->mlx->ptr, map->mlx->win);
    //render_minimap(map);
	// printf("key = %d\n", key);
	// if (key == 65307)
	// {
	// 	mlx_destroy_window(map->mlx->ptr, map->mlx->win);
	// 	exit(0);

	// }
	// if (key == 65362)
	// {
	// 	map->player_y -= 0.1;
	// }
	// render_minimap(map);
	return (0);
}

/*Initialisation de la mlx*/

int	ft_mlx_init(t_data_map *map)
{
	map->mlx->ptr = mlx_init();
	map->mlx->win = mlx_new_window(map->mlx->ptr, 1080, 720, "Cub3D");
	// render_minimap_test(map);
	mlx_hook(map->mlx->win, 2, 1L << 0, keyhook, map);
	mlx_loop(map->mlx->ptr);
	return (0);
}
