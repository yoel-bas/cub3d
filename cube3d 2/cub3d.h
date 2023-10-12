#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
#  define TILE_SIZE 64
#  define SCALE 0.2
# endif


#include "../MLX42/include/MLX42/MLX42.h"
#include <libc.h>
#include <math.h>

typedef struct s_elem
{
	char	**file;
	char 	**map;
	// char	*path;
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
	// char 	**fl;
	// char 	**cl;
}			t_clr;


typedef struct r
{
	double FOV_ANGLE;
	double num_arays;
	int face_up;
	int face_down;
	int face_right;
	int face_left;
	double wall_horzx;
	double wall_horzy;
	double wall_vertx;
	double wall_verty;
}		t_ray;
typedef struct p
{
	float	x;
	float	x_r;
	float 	y;
	float	y_r;
	float radius;
	float turn_direction;
	float walk_direction;
	float r_angle;
	float speed;
	float r_speed;
	float flg;
	float steps;
}		t_player;
typedef struct element
{
	mlx_image_t *image;
	mlx_image_t *image2;
	mlx_image_t *m_north;
	float		coins;
	float		x_p;
	float		y_p;
	float		x_p1;
	float		y_p1;
	int		check_vert;
	char	**map;
	char	**map1;
	char	**map2;
	float		moves;
	mlx_t* mlx;
	void	*mlx_window;
	void	*img_ptr;
	void	*img_ptrp;
	void	*img_ptrwin;
	void	*img_ptrw;
	void	*img_ptrc;
	void	*img_ptre;
	void	*img_ptre2;
	void	*img_ptrg;
	void	*img_ptrpl;
	float		back;
	void	*img;
	char	*addr;
	float		bits_per_pixel;
	float		line_length;
	float		endian;
	float w_x;
	mlx_texture_t *north_img;
	mlx_texture_t *west_img;
	mlx_texture_t *south_img;
	mlx_texture_t *east_img;
	float w_y;
	t_player *player;
	t_ray *ray;
	t_cmp	*cp;
	t_clr	*cl;
	t_elem	*lmt;
	char 	**rgbs;
	int		iter;
}			t_cube;

char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
int	ft_isalpha(int c);
void	*ft_memset(void *str, int c, int n);
char	*ft_strchr(const char *str, int c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	ft_wrong(void);

void reycast(t_cube *main_game, int fd);
void	draw_ground(t_cube *main_game, int x_p, int y_p);
void	draw_walls(t_cube *main_game, int x_p, int y_p);
void	cub(t_cube *main_game);
int		found_newline(char *stash);
char	*update_it(char *s);
char	*get_next_line(int fd);
char	*get_linee(char *src);

void	ft_error(char *str);
size_t	 ft_strlen(char *str);
char	*ft_strdup(char *src);
char	*ft_substr(char	*s, size_t	start, size_t len);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char  *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char 	*ft_strcpy(char *src);
int		ft_atoi(const char *str);

void	player_pos_dir(char **file);
void	check_extension(char *path);
void	check_top_bottom(char **map);
void	check_sides(char **map);
void	check_extranous_spaces(char **map);
int	foreign_material(char **map);
void	player_pos_dir(char **map);
void	check_components(char **map);
int 	fullfilled(t_cube *cnt);
int		line_count(char  **dbl, int *j);
int		is_white_space(char x);
void	clr_parse(char *str);
// void    clr_parse(char *str, t_cube *content, int flag);
void	read_components(t_cube *content);
void	maper(t_cube	*content, char	*av);
#endif 