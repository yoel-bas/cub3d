NAME = cub3d
HEADER = cub3d.h 

SRC =  ./init/map_init.c \
	./init/map_init_helper.c \
	./init/clrdir_filler.c \
	./init/map_filler.c \
	./utils/utils.c \
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
	./raycast/init_textures.c \
	./raycast/raycast.c \
	./raycast/drawer.c \
	./raycast/get_colors.c \
	cub3d.c \
	#  draw.c \
	./raycast/player.c \
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