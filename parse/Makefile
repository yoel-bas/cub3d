# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 20:31:08 by melayoub          #+#    #+#              #
#    Updated: 2023/10/01 17:50:15 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cube
# NAME_B = cube_bonus
HEADER = cube.h
# HEADER_B = cube_bonus.h
# MINILIBX = -lmlx -framework OpenGL -framework AppKit -g

SRC = utils2.c utils_splt.c utils_map.c\
	parsing/path_parse.c parsing/map_perimeter.c parsing/map_components.c parsing/clr_parse.c \
	map_init_helper.c map_init.c main.c \
	gnl/get_next_line_utils.c gnl/get_next_line.c \
	

# B_SRC =

CC = cc #-fsanitize=address
FLAGS = -Wall -Wextra -Werror -g 
RM = rm -rf

all: $(NAME)

# bonus : $(NAME_B)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME) 
#  $(MINILIBX)

# $(NAME_B): $(B_SRC) $(HEADER_B)
#	$(CC) $(FLAGS) $(B_SRC) -o $(NAME_B) $(MINILIBX)

clean:
	$(RM) $(NAME) $(NAME_B)

fclean: clean
	$(RM) $(bonus)

re: fclean all