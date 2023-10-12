NAME = cub3d
HEADER = cub3d.h

SRC = ft_bzero.c \
	  ft_calloc.c \
	  ft_memset.c \
	  map_init.c \
	  ft_strchr.c\
	  map_init_helper.c \
	  utils_map.c \
	  utils_splt.c \
	  utils.c \
	  utils2.c \
	  map_components.c \
	  map_perimeter.c\
	  path_parse.c\
	  clr_parse.c\
	  get_next_line.c \
	  ft_strjoin.c \
	  cub3d.c \
	  raycast.c \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_memset.c \
	  ft_split.c \
	  ft_strchr.c \
	  ft_strcmp.c \
	  ft_strdup.c \
	  ft_strlen.c \
	  ft_substr.c \
	  ft_wrong.c \
	  get_next_line.c \
	  ft_strjoin.c \
	  draw.c 

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

OBJ = $(SRC:.c=.o)

all: ${NAME}


${NAME}: $(OBJ)
	# $(CC) $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit  -o $@
	$(CC) $(CFLAGS) $^ ../MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re: fclean all