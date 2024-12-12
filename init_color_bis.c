/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:35:12 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/05 11:48:17 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    f_to_hexa(t_data_map **data_map)
{
	char	base_hexa[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	char	*hexa_nbr;
	int     i;
	int     j;

	hexa_nbr = malloc(sizeof(char) * 8);
	if (!hexa_nbr)
		ft_error("Malloc error", (*data_map));
	i = 0;
	j = 1;
	hexa_nbr[0] = '#';
	while ((*data_map)->f_color[i] != -1)
	{
		hexa_nbr[j] = base_hexa[(*data_map)->f_color[i] / 16];
		hexa_nbr[j + 1] = base_hexa[(*data_map)->f_color[i] % 16];
		i++;
		j += 2;
	}
	hexa_nbr[j] = '\0';
	free((*data_map)->floor_color);
	(*data_map)->floor_color = ft_strdup(hexa_nbr);
	free(hexa_nbr);
}

void c_to_hexa(t_data_map **data_map)
{
	char	base_hexa[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	char	*hexa_nbr;
	int	i;
	int	j;

	hexa_nbr = malloc(sizeof(char) * 8);
	if (!hexa_nbr)
		ft_error("Malloc error", (*data_map));
	i = 0;
	j = 1;
	hexa_nbr[0] = '#';
	while ((*data_map)->c_color[i] != -1)
	{
		hexa_nbr[j] = base_hexa[(*data_map)->c_color[i] / 16];
		hexa_nbr[j + 1] = base_hexa[(*data_map)->c_color[i] % 16];
		i++;
		j += 2;
	}
	hexa_nbr[j] = '\0';
	free((*data_map)->ceiling_color);
	(*data_map)->ceiling_color = ft_strdup(hexa_nbr);
	free(hexa_nbr);
}
