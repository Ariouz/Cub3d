NAME= cub3d

GNL_SRCS= $(addprefix libs/gnl/, \
get_next_line.c \
get_next_line_utils.c)

SRCS_DIR= srcs/
SRCS= $(GNL_SRCS) $(addprefix $(SRCS_DIR), \
cub3d.c \
manager/listener_manager.c \
listener/exit_listener.c \
listener/key_press_listener.c \
listener/mouse_listener.c \
utils/initializer.c \
utils/draw_utils.c \
utils/image.c \
utils/math_utils.c \
utils/error_msg.c \
utils/free_utils.c \
parser/map_init.c \
parser/map_reader.c \
parser/map_reader_temp.c \
parser/get_asset.c \
parser/get_ceiling_color.c \
parser/get_floor_color.c \
parser/get_east_asset.c \
parser/get_north_asset.c \
parser/get_south_asset.c \
parser/get_west_asset.c \
parser/get_color.c \
parser/get_map_description.c \
parser/check_map.c \
parser/check_element.c \
parser/check_wall.c \
renderer/renderer.c \
renderer/raycaster.c \
renderer/minimap.c)

OBJS= $(SRCS:.c=.o)

LFT_DIR= libs/libft
LFT_A= $(LFT_DIR)/libft.a

MLX_DIR= libs/mlx

GNL_DIR= libs/gnl

LIBS= -Iincludes -L$(MLX_DIR) -I$(MLX_DIR) -lmlx -lXext -lX11 -lm -I$(GNL_DIR)

FLAGS= -g -Wall #-Werror -Wextra

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