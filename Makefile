NAME	:=	fdf

CC	:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
GDB	:=	-g3
export GDB

FILES		:=	main.c

SRC_PATH	:=	src
SRC			:=	$(addprefix $(SRC_PATH)/,$(FILES))

OBJ_PATH	:=	build
OBJ			:=	$(addprefix $(OBJ_PATH)/,$(FILES:.c=.o))

INC_PATH	:=	inc
CINC		:=	-I. -Iinc

MLX_PATH	:=	minilibx-linux
MLX			:=	mlx

FT_PATH		:=	libft
FT			:=	ft

CLIB := -L$(FT_PATH) -l$(FT) -L$(MLX_PATH) -l$(MLX) -lXext -lX11

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(MLX_PATH)/lib$(MLX).a $(FT_PATH)/lib$(FT).a
	$(CC) $(CFLAGS) $(GDB) $(CINC) $(OBJ) -o $@ $(CLIB)

$(MLX_PATH)/lib$(MLX).a:
	make -C $(MLX_PATH)

$(FT_PATH)/lib$(FT).a:
	make -C $(FT_PATH)

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(GDB) $(CINC) -c $< -o $@

$(OBJPATH):
	mkdir -p $@

.PHONY: clean fclean re norm
clean:
	rm -f $(OBJ)

fclean: clean
	make clean -C $(MLX_PATH)
	make fclean -C $(FT_PATH)
	rm -f $(NAME)

re: fclean all

norm:
	make norm -C $(FT_PATH)
	norminette -R CheckForbiddenSourceHeader $(SRC)
	norminette -R CheckDefine $(INCPATH)
