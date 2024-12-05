/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:29 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/05 11:40:38 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

# define pi 3.14159265358

/* structs */
typedef struct s_data_map
{
	int		fd;
	char	*line;
	bool	texture_color;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	int		*f_color;
	char	*ceiling_color;
	int		*c_color;
	char	**map;
	double	pos;
}			t_data_map;

/* parse_map_ter.c */
void	map_to_data(t_data_map *data_map);

/* parse_map_bis.c */
void	map_to_data(t_data_map *data_map);

/* parse_map.c */
void		check_map_char(t_data_map *data_map);
void		not_double_player(t_data_map *data_map);
void		map_is_well_spaced(t_data_map *data_map);
void		map_is_closed(t_data_map *data_map);
void		map_exist(char *str, t_data_map *data_map);

/* init_color.c */
void		init_color(char *str, t_data_map *data_map);

/* init_color_bis.c */
void f_to_hexa(t_data_map **data_map);
void c_to_hexa(t_data_map **data_map);

/* init_texture.c */
void		init_texture(char *str, t_data_map *data_map);

/* init_texture_bis.c */
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup_newline(const char *s);
void    check_texture_path(t_data_map *data_map);

/* parse.c */
void		check_color(t_data_map *data_map);
void		check_texture(t_data_map *data_map);
void		ft_open_map(char *str, t_data_map *data_map);
void		ft_read_map(char *str, t_data_map *data_map);

/* utils.c */
void		go_to_eof(char *str, t_data_map *data_map);
void		map_is_not_cub(char *str, t_data_map *data_map);
void		ft_error(char *str, t_data_map *data_map);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *s);

/* utils_bis.c */
int	ft_atoi(const char *nptr, t_data_map *data_map);

#endif
