# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 15:29:04 by sbenes            #+#    #+#              #
#    Updated: 2023/08/26 13:56:21 by sbenes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#color and formatting definitions:
BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
NC =	\033[0m


#name
NAME = 		miniRT

# compiler
CC =		cc
CFLAGS =	-Wall -Wextra -Werror -g

#Minilibx
MLX_PATH =	mlx/
MLX_NAME =	libmlx.a
MLX =		$(MLX_PATH)$(MLX_NAME)

#libft
LIBFT_PATH =	libft/
LIBFT_NAME =	libft.a
LIBFT =			$(LIBFT_PATH)$(LIBFT_NAME)

#Includes
INC =	-I ./include/\
		-I ./libft/\
		-I ./mlx/

#sources
SRC_PATH =	src/
SRC = 	main.c error.c utils.c parser.c \
	init_objects.c init_objects_utils.c init_object_utils2.c init_object_utils3.c init_scene.c init_scene_utils.c init_scene_utils2.c init.c\
	events.c exit.c render.c vector_operations.c vector_operations_utils.c hit_sphere.c ray.c ray_utils.c hit_plane.c\
	hit_cylinder.c hit_cylinder_utils.c light.c light_utils.c shadow.c shadow_utils.c
	
SRCS =	$(addprefix $(SRC_PATH), $(SRC))

#objects
OBJ_PATH =	obj/
OBJ =		$(SRC:.c=.o)
OBJS =		$(addprefix $(OBJ_PATH), $(OBJ))


all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(MLX):
	@echo "$(BOLD)$(GREEN)[ 🙈 Making MiniLibX... ]$(NC)"
	@make -sC $(MLX_PATH)

$(LIBFT):
	@echo "$(BOLD)$(GREEN)[ 🙉 Making libft... ]$(NC)"
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJS)
	@echo "$(BOLD)$(GREEN)[ 🙊 Compiling shit together... ]$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm
	@echo "$(BOLD)$(GREEN)[ 🪄 Program ready! ]$(NC)"

bonus: all

clean:
	@echo "$(BOLD)$(RED)[ 🔥 Purging object files ]$(NC)"
	@rm -Rf $(OBJ_PATH)
	@make clean -sC $(MLX_PATH)
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@echo "$(BOLD)$(RED)[ 🔥 Removing program ]$(NC)"
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean


 
