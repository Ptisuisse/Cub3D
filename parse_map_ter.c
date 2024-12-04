/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_ter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:32:12 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/04 19:34:02 by dpoltura         ###   ########.fr       */
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
