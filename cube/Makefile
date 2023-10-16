NAME = cub3d
HEADER = cub3d.h 

SRC =  map_init.c \
	map_init_helper.c \
	./utils/utils_map.c \
	./utils/utils2.c \
	./utils/ft_split.c \
	./gnl/get_next_line.c \
	./gnl/get_next_line_utils.c \
	./parsing/path_parse.c \
	./parsing/map_perimeter.c \
	./parsing/map_peri_extra.c \
	./parsing/map_components.c \
	./parsing/clr_parse.c\
	cub3d.c \
	raycast.c \
	#  draw.c \
	ft_wrong.c \
	  ft_strcmp.c \
	  ft_strchr.c \
	  ft_memset.c \
	  utils_splt.c \
	  ft_strjoin.c \
	  ft_strlen.c \
	  ft_substr.c \
	  ft_calloc.c \
	  ft_bzero.c \
	  ft_strdup.c \
	  ft_strjoin.c \
	  

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