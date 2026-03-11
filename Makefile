NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = mlx
LIBFT_DIR = lib

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

INCLUDES = -I/opt/X11/include -Imlx -Iinclude
MLX_FLAGS = -Lmlx -lmlx -lXext -lX11

SRC = ./src/ft_check_map.c ./src/ft_init_utils.c ./src/init_game.c ./src/init_map.c ./src/main.c ./src/ft_moving.c ./src/ft_moving_player.c ./src/ft_check_fill_map.c ./src/check_utils.c ./src/ft_exit.c ./src/ft_map_hight.c ./src/ft_parse_map.c

all: ${NAME}

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then echo "ERROR: $(MLX_DIR) not found!"; exit 1; fi
	@if [ -f $(MLX_DIR)/configure ] && [ ! -f $(MLX_DIR)/Makefile ]; then \
		echo "Running configure in $(MLX_DIR)..."; \
		cd $(MLX_DIR) && ./configure; \
	fi
	@if [ ! -f $(MLX_DIR)/Makefile ]; then \
		echo "ERROR: No Makefile found in $(MLX_DIR) after running configure!"; \
		exit 1; \
	fi
	@make -C $(MLX_DIR)

$(LIBFT):
	@make re -C $(LIBFT_DIR)

${NAME}: $(MLX_LIB) $(LIBFT)
	${CC} ${SRC} ${CFLAGS} ${INCLUDES} ${LIBFT} ${MLX_LIB} ${MLX_FLAGS} -o ${NAME}

clean:
	@if [ -f $(MLX_DIR)/Makefile ]; then make clean -C $(MLX_DIR); fi
	@if [ -f $(LIBFT_DIR)/Makefile ]; then make clean -C $(LIBFT_DIR); fi

fclean: clean
	$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all