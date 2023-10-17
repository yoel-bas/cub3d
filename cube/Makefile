NAME = cub3D
HEADER = cub3d.h 

SRC =  ./init/map_init.c \
	./init/map_init_helper.c \
	./init/clrdir_filler.c \
	./init/map_filler.c \
	./utils/utils.c \
	./utils/utils_mem.c \
	./utils/utils_str.c \
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
	./raycast/player.c \
	./raycast/moves.c \
	./raycast/get_colors.c \
	cub3d.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror


OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: $(OBJ)
	$(CC) $(CFLAGS) $^ ../MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re: fclean all