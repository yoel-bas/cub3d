/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:58:43 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 00:50:51 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
#  define HEIGHT 1080
#  define WIDTH 1920
#  define TILE_SIZE 64
#  define SCALE 0.2
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include <libc.h>
# include <math.h>

typedef struct s_elem
{
	char	**file;
	char	**map;
}				t_elem;

typedef struct compas
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
}			t_cmp;

typedef struct colors
{
	char	*fl;
	char	*cl;
}			t_clr;

typedef struct r
{
	double	fov_angle;
	double	num_arays;
	int		face_up;
	int		face_down;
	int		face_right;
	int		face_left;
	double	wall_horzx;
	double	wall_horzy;
	double	wall_vertx;
	double	wall_verty;
}		t_ray;

typedef struct p
{
	float	x;
	float	x_r;
	float	y;
	float	y_r;
	float	radius;
	float	turn_direction;
	float	walk_direction;
	float	r_angle;
	float	speed;
	float	r_speed;
	float	flg;
	float	steps;
	int		middle;
}		t_player;

typedef struct element
{
	mlx_image_t			*image;
	mlx_image_t			*image2;
	float				coins;
	float				x_p;
	float				y_p;
	float				x_p1;
	float				y_p1;
	int					check_vert;
	char				**map;
	char				**map1;
	char				**map2;
	float				moves;
	mlx_t				*mlx;
	void				*mlx_window;
	void				*img_ptr;
	void				*img_ptrp;
	void				*img_ptrwin;
	void				*img_ptrw;
	void				*img_ptrc;
	void				*img_ptre;
	void				*img_ptre2;
	void				*img_ptrg;
	void				*img_ptrpl;
	float				back;
	void				*img;
	char				*addr;
	float				bits_per_pixel;
	float				line_length;
	float				endian;
	float				w_x;
	mlx_texture_t		*north_img;
	mlx_texture_t		*south_img;
	mlx_texture_t		*east_img;
	mlx_texture_t		*west_img;
	mlx_image_t			*m_north;
	mlx_image_t			*m_south;
	mlx_image_t			*m_east;
	mlx_image_t			*m_west;
	float				w_y;
	t_player			*player;
	t_ray				*ray;
	t_cmp				*cp;
	t_clr				*cl;
	t_elem				*lmt;
	char				**rgbs;
	double				ray_angle_image;
	int					dir_flag;
	int					done_flag;
	double				step;
	int					texturs_x;
	int					y_texture;
	unsigned int		color;
	int					mm;
	double				ray_distance;
	double				perpdistance;
	double				projection;
	double				wallstrip;
	int					wall_top;
	int					wall_bottom;
	double				x_step;
	double				y_step;
	double				x_inter;
	double				y_inter;
	double				check_x;
	double				check_y;
	double				to_checkx;
	double				to_checky;
}				t_cube;

void			ft_error(char *str);
char			*get_next_line(int fd);
int				ft_is_digit(int c);
int				ft_isalpha(int c);
int				is_white_space(char x);
int				is_whitesp_butnl(char c);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nitems, size_t size);
void			*ft_memset(void *str, int c, int n);
char			*ft_strchr(const char *str, int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(char *str);
char			*ft_strdup(char *src);
char			*ft_substr(char	*s, size_t	start, size_t len);
int				ft_strncmp(char *s1, char *s2, size_t n);
char			*ft_strjoin(char *str1, char *str2);
char			**ft_split(char *s, char c);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strcpy(char *src);
int				ft_atoi(const char *str);
char			*ft_strrchr(char *s, int c);
char			*ft_strtrim(char *s1, char *set);
void			check_inner_extranous(char **map);

void			player_pos_dir(char **file);
void			check_extension(char *path);
void			check_top(char **map);
void			check_bottom(char **map);
void			check_sides(char **map);
void			check_extranous_spaces(char **map);
void			check_extranous_revsp(char **map);
int				foreign_material(char **map);
void			ft_is_dir(char *line, t_cube *cnt);
void			ft_is_clr(char *line, t_cube *cnt);
void			ft_fill_map(t_cube *content, int *j);
void			player_pos_dir(char **map);
void			check_components(char **map);
int				fullfilled(t_cube *cnt);
double			distance(double x, double y, double x1, double y1);
void			cast(t_cube *main_game);
int				between(t_cube *main_game, int x, int y);
void			get_border(t_cube *main_game);
int				line_count(char **dbl, int *j);
void			ceiling_floor(t_cube *main_game);
void			clr_parse(char *str);
void			read_components(t_cube *content);
void			maper(t_cube	*content, char	*av);
void			check_dir(char **map, t_cube *content);
int				ft_count(char **spt);
void			ft_parser(t_cube *content);
void			texture(t_cube *main_game, mlx_image_t *sight);
void			ft_upload_texture_img(t_cube *content);
void			player_init(t_cube *main_game);
unsigned int	ft_pixel(unsigned int r, unsigned int g,
					unsigned int b, unsigned int a);
unsigned int	get_color(mlx_image_t *sight,
					unsigned int y_texture, unsigned int x_texture);
void			ceiling_floor(t_cube *main_game);
void			draw_map(t_cube *main_game);
void			player_init(t_cube *main_game);
void			player_update(t_cube *mg);
void			get_player_pos(t_cube *game);
void			player(t_cube *game);
void			player_update(t_cube *mg);
void			frame(void *main);
void			get_player_pos(t_cube *game);
void			player_init(t_cube *main_game);
void			reycast(t_cube *main_game, int fd);
void			draw_ground(t_cube *main_game, int x_p, int y_p);
void			draw_walls(t_cube *main_game, int x_p, int y_p);
void			cub(t_cube *main_game);
unsigned int	ceiling_color(t_cube *main_game, int upper_half);
void			floor_color(t_cube *main_game, int lower_half);
double			normalize(double angle);
int				is_wall(t_cube *main_game, double x1, double y1);
void			calcul_vertical(t_cube *main_game, double angle);
void			vertical_cast(t_cube *main_game, double angle);
void			calcul_horizontal(t_cube *main_game, double angle);
void			horizontal_cast(t_cube *main_game, double angle);
#endif
