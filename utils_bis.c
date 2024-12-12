/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:13:53 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/04 17:57:53 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(const char *nptr, t_data_map *data_map)
{
	static int	i = 0;
    int j;
	int	k;

    j = 0;
	k = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		k = k * 10;
		k += nptr[i] - '0';
		i++;
        j++;
	}
    if (j == 0 || k > 255)
    {
        ft_error("Can't read color\n", data_map);
    }
    i++;
    if (!nptr[i])
        i = 0;
    return (k);
}
