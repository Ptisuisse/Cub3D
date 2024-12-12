/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:29 by dpoltura          #+#    #+#             */
/*   Updated: 2024/12/12 15:00:43 by dpoltura         ###   ########.fr       */
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

# define PI 3.14159265358979323846
# define FOV 60
# define HEIGHT 720
# define WIDTH 1280
# define TILE_SIZE 64
# define pi 3.14159265358

/* structs */
typedef struct s_data_map
{
	bool		minimap;
	int			fd;
	char		*line;
	bool		texture_color;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*floor_color;
	char		*f_color;
	char		*ceiling_color;
	char		*c_color;
	char		**map;
	double		pos;
	int			x;
	int			y;
	int			p_x;
	int			p_y;
}				t_data_map;

/*Player*/
typedef struct s_ply
{
	double		player_x;
	double		player_y;
	double		dir_angle;
	int			test;
	int		flag;
	double	ray_ngl;
	double	distance;
}				t_ply;

/*MLX*/
typedef struct s_mlx
{
	t_data_map	*map;
	t_ply		*ply;
	int			img_height;
	int			img_width;
	void		*ptr;
	void		*mlx;
	void		*img;
	void		*win;
	void		*img_player;
	void		*img_floor;
	void		*img_coll;
	void		*img_exit;
}				t_mlx;

/*raycasting.c*/
void			init_raycasting(t_mlx *mlx);
float get_h_inter(t_mlx *mlx, float angle);
float get_v_hinter(t_mlx *mlx, float angle);
float	nor_angle(float angle);
void	render_wall(t_mlx *mlx, int ray);
void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix);
int	get_color(t_mlx *mlx, int flag);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int inter_check(float angle, float *inter, float *step, int is_horizon);
/*mini_map.c*/
void			draw_fov_ray(t_mlx *mlx);
int				render_minimap(t_mlx *mlx);
void			ft_put_pixel(t_mlx *mlx, int x, int y, int color);
void			ft_put_pixel_player(t_mlx *mlx, double y, double x, int color);

/* parse_map_ter.c */
void	map_to_data(t_data_map *data_map);
/* parse_map_bis.c */

void			map_to_data(t_data_map *data_map);

/* parse_map.c */
void			check_map_char(t_data_map *data_map);
void			not_double_player(t_data_map *data_map);
void			map_is_well_spaced(t_data_map *data_map);
void			map_is_closed(t_data_map *data_map);
void			map_exist(char *str, t_data_map *data_map);

/* init_color.c */
void			init_color(char *str, t_data_map *data_map);

/* init_color_bis.c */
void f_to_hexa(t_data_map **data_map);
void c_to_hexa(t_data_map **data_map);

/* init_texture.c */
void			init_texture(char *str, t_data_map *data_map);

/* init_texture_bis.c */
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup_newline(const char *s);
void    check_texture_path(t_data_map *data_map);

/* parse.c */
void			check_color(t_data_map *data_map);
void			check_texture(t_data_map *data_map);
void			ft_open_map(char *str, t_data_map *data_map);
void			ft_read_map(char *str, t_data_map *data_map);

/* utils.c */
void			go_to_eof(char *str, t_data_map *data_map);
void			map_is_not_cub(char *str, t_data_map *data_map);
void			ft_error(char *str, t_data_map *data_map);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strdup(const char *s);

/*Mlx_init.c*/
int				ft_mlx_init(t_mlx *mlx);
void			size_of_map(t_data_map *map);

/* utils_bis.c */
int	ft_atoi(const char *nptr, t_data_map *data_map);

#endif
