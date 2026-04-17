# NAME = cub3D

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

# MLX_DIR = mlx
# LIBFT_DIR = libft

# LIBFT = $(LIBFT_DIR)/libft.a
# MLX_LIB = $(MLX_DIR)/libmlx.a

# INCLUDES = -I/opt/X11/include -Imlx -Iinclude
# MLX_FLAGS = -Lmlx -lmlx -lXext -lX11

# # SRC = ./srcs/main.c ./srcs/moving.c ./srcs/init_game.c ./srcs/init_map.c
# SRC = ./srcs/main.c ./srcs/init_map.c ./srcs/init_game.c ./srcs/parsing1.c ./srcs/moving.c

# # ./srcs/main.c

# all: ${NAME} cub


# cub:
# 	@printf '#!/bin/bash\nMAP=$$(find maps/ -name "$$1" 2>/dev/null | head -1)\nif [ -z "$$MAP" ]; then\n    echo "Error: '\''$$1'\'' not found in maps/"\n    exit 1\nfi\n./cub3D "$$MAP"\n' > cub
# 	@chmod +x cub
# 	@echo "Script ./cub créé"
	
# $(MLX_LIB):
# 	@if [ ! -d $(MLX_DIR) ]; then echo "ERROR: $(MLX_DIR) not found!"; exit 1; fi
# 	@if [ -f $(MLX_DIR)/configure ] && [ ! -f $(MLX_DIR)/Makefile ]; then \
# 		echo "Running configure in $(MLX_DIR)..."; \
# 		cd $(MLX_DIR) && ./configure; \
# 	fi
# 	@if [ ! -f $(MLX_DIR)/Makefile ]; then \
# 		echo "ERROR: No Makefile found in $(MLX_DIR) after running configure!"; \
# 		exit 1; \
# 	fi
# 	@make -C $(MLX_DIR)

# $(LIBFT):
# 	@make re -C $(LIBFT_DIR)

# ${NAME}: $(MLX_LIB) $(LIBFT)
# 	${CC} ${SRC} ${CFLAGS} ${INCLUDES} ${LIBFT} ${MLX_LIB} ${MLX_FLAGS} -o ${NAME}

# clean:
# 	@if [ -f $(MLX_DIR)/Makefile ]; then make clean -C $(MLX_DIR); fi
# 	@if [ -f $(LIBFT_DIR)/Makefile ]; then make clean -C $(LIBFT_DIR); fi

# fclean: clean
# 	$(RM) $(NAME)
# 	@$(RM) $(LIBFT)
# 	$(RM) cub

# re: fclean all
NAME = cub3D
BIN_DIR = bin
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = mlx
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
INCLUDES = -I/opt/X11/include -Imlx -Iinclude
MLX_FLAGS = -Lmlx -lmlx -lXext -lX11
SRC = ./srcs/main.c ./srcs/init_game.c ./srcs/parsing1.c ./srcs/moving.c ./srcs/parsingIdent.c

all: ${BIN_DIR}/${NAME} cub

${BIN_DIR}:
	@mkdir -p ${BIN_DIR}

cub:
	@printf '#!/bin/bash\nMAP=$$(find maps/ -name "$$1" 2>/dev/null | head -1)\nif [ -z "$$MAP" ]; then\n    echo "Error: '\''$$1'\'' not found in maps/"\n    exit 1\nfi\n./bin/cub3D "$$MAP"\n' > cub
	@chmod +x cub
	@echo "Script ./cub créé"

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

${BIN_DIR}/${NAME}: ${BIN_DIR} $(MLX_LIB) $(LIBFT)
	${CC} ${SRC} ${CFLAGS} ${INCLUDES} ${LIBFT} ${MLX_LIB} ${MLX_FLAGS} -o ${BIN_DIR}/${NAME}

clean:
	@if [ -f $(MLX_DIR)/Makefile ]; then make clean -C $(MLX_DIR); fi
	@if [ -f $(LIBFT_DIR)/Makefile ]; then make clean -C $(LIBFT_DIR); fi

fclean: clean
	$(RM) -r $(BIN_DIR)
	@$(RM) $(LIBFT)
	$(RM) cub
	$(RM) vgcore.*

re: fclean all