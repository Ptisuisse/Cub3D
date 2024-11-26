/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:29 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/26 14:08:28 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

/*MLX*/

typedef struct mlx
{
	int		img_height;
	int		img_width;
	void	*ptr;
	void	*mlx;
	void	*img;
	void	*win;
	void	*img_player;
	void	*img_floor;
	void	*img_coll;
	void	*img_exit;
}			t_mlx;

/* structs */
typedef struct s_data_map
{
	bool	minimap;
	int		angle;
	int		fd;
	char	*line;
	bool	texture_color;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	char	*ceiling_color;
	char	**map;
	int		x;
	int		y;
	int		player_x;
	int		player_y;
	t_mlx	*mlx;
}			t_data_map;

/* parse_map_bis.c */

void		map_to_data(t_data_map *data_map);

/* parse_map.c */
void		check_map_char(t_data_map *data_map);
void		not_double_player(t_data_map *data_map);
void		map_is_well_spaced(t_data_map *data_map);
void		map_is_closed(t_data_map *data_map);
void		map_exist(char *str, t_data_map *data_map);

/* init_color.c */
void		init_color(char *str, t_data_map *data_map);

/* init_texture.c */
void		init_texture(char *str, t_data_map *data_map);

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

/*Mlx_init.c*/
int			ft_mlx_init(t_data_map *map);
void		size_of_map(t_data_map *map);

#endif
