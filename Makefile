NAME= cub3d

SRCS_DIR= srcs/
SRCS= $(addprefix $(SRCS_DIR), \
cub3d.c) \
$(addprefix $(SRCS_DIR)manager/, \
listener_manager.c) \
$(addprefix $(SRCS_DIR)listener/, \
exit_listener.c)

OBJS= $(SRCS:.c=.o)

LFT_DIR= libs/libft
LFT_A= $(LFT_DIR)/libft.a

MLX_DIR= libs/mlx

LIBS= -Iincludes -L$(MLX_DIR) -I$(MLX_DIR) -lmlx -lXext -lX11 -lm

FLAGS= -Wall -Werror -Wextra

$(NAME): $(LFT_A) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LFT_A) $(LIBS) -o $(NAME)

%.o: %.c
	gcc -c $< -o $@ $(FLAGS) $(LIBS)

$(LFT_A):
	make -C $(LFT_DIR) bonus

install:
	cd $(MLX_DIR)/ && ./configure && cd ../../

clean:
	make -C $(LFT_DIR) clean BONUS=1
	rm $(OBJS)

fclean: clean
	make -C $(LFT_DIR) fclean BONUS=1
	rm -rf $(NAME)

re: fclean $(NAME)

all: $(NAME)

.PHONY: all re clean fclean install