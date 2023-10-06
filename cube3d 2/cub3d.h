#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
#  define TILE_SIZE 32
# endif


#include "../MLX42/include/MLX42/MLX42.h"
#include <libc.h>
#include <math.h>
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
}		t_ray;
typedef struct p
{
	double	x;
	double	x_r;
	double 	y;
	double	y_r;
	double radius;
	double turn_direction;
	double walk_direction;
	double r_angle;
	double speed;
	double r_speed;
	double flg;
	double steps;
}		t_player;
typedef struct element
{
	mlx_image_t *image;
	mlx_image_t *image2;
	int		coins;
	int		x_p;
	int		y_p;
	int		x_p1;
	int		y_p1;
	char	**map;
	char	**map1;
	char	**map2;
	int		moves;
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
	int		back;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int w_x;
	int w_y;
	t_player *player;
	t_ray *ray;
}			t_way;
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
int	ft_isalpha(int c);
void	*ft_memset(void *str, int c, int n);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char *s, char c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	ft_wrong(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void reycast(t_way *main_game, int fd);
void	draw_ground(t_way *main_game, int x_p, int y_p);
void	draw_walls(t_way *main_game, int x_p, int y_p);
void	cub(t_way *main_game, int fd);
#endif 