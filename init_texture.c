/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:14:54 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/05 11:58:23 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_ea_texture(char *str, int i, t_data_map *data_map)
{
	if (str && str[i] == 'E')
	{
		if (data_map->ea_texture)
			ft_error("Double in texture\n", data_map);
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		if (!ft_strncmp(&str[i], "./textures/texture_est.png", 26))
			data_map->ea_texture = ft_strdup_newline(&str[i]);
		else
			ft_error("Can't read east texture.\nTexture path format : ./textures/texture_est.png\n", data_map);
	}
}

static void	is_we_texture(char *str, int i, t_data_map *data_map)
{
	if (str && str[i] == 'W')
	{
		if (data_map->we_texture)
			ft_error("Double in texture\n", data_map);
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		if (!ft_strncmp(&str[i], "./textures/texture_ouest.png", 28))
			data_map->we_texture = ft_strdup_newline(&str[i]);
		else
			ft_error("Can't read west texture.\nTexture path format : ./textures/texture_ouest.png\n", data_map);
	}
}

static void	is_so_texture(char *str, int i, t_data_map *data_map)
{
	if (str && str[i] == 'S')
	{
		if (data_map->so_texture)
			ft_error("Double in texture\n", data_map);
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		if (!ft_strncmp(&str[i], "./textures/texture_sud.png", 26))
			data_map->so_texture = ft_strdup_newline(&str[i]);
		else
			ft_error("Can't read south texture.\nTexture path format : ./textures/texture_sud.png\n", data_map);
	}
}

static void	is_no_texture(char *str, int i, t_data_map *data_map)
{
	if (str && str[i] == 'N')
	{
		if (data_map->no_texture)
			ft_error("Double in texture\n", data_map);
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		if (!ft_strncmp(&str[i], "./textures/texture_nord.png", 27))
			data_map->no_texture = ft_strdup_newline(&str[i]);
		else
			ft_error("Can't read north texture.\nTexture path format : ./textures/texture_nord.png\n", data_map);
	}
}

void	init_texture(char *str, t_data_map *data_map)
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
		is_no_texture(data_map->line, i, data_map);
		is_so_texture(data_map->line, i, data_map);
		is_we_texture(data_map->line, i, data_map);
		is_ea_texture(data_map->line, i, data_map);
		free(data_map->line);
		data_map->line = get_next_line(data_map->fd);
		i = 0;
	}
	if (!data_map->no_texture || !data_map->so_texture || !data_map->we_texture
		|| !data_map->ea_texture)
		ft_error("Double in texture\n", data_map);
}
