NAME = cub3d
HEADER = cub3d.h

SRC = ft_bzero.c \
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
	  cub3d.c \
	  raycast.c \
	  draw.c 

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf

OBJ = $(SRC:.c=.o)

all: ${NAME}


${NAME}: $(OBJ)
	# $(CC) $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $@
	$(CC) $(CFLAGS) $^ ../MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/yoel-bas/.brew/opt/glfw/lib/" -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re: fclean all