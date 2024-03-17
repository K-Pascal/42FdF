FILES		:=	main.c				\
				parser.c			\
				parser_utils.c		\
				utils.c				\
				draw_line.c			\
				draw_line_utils.c	\
				transformations.c	\
				projections.c		\
				events.c			\
				events_utils.c		\
				render.c			\
				matrix.c			\

SRC_PATH	:=	src
SRC			:=	$(addprefix $(SRC_PATH)/,$(FILES))

OBJ_PATH	:=	build
OBJ			:=	$(addprefix $(OBJ_PATH)/,$(FILES:.c=.o))
DEPS		:= $(OBJ:.o=.d)

INC_PATH	:=	inc
CINC		:=	-I. -Iinclude

MLX_PATH	:=	minilibx-linux
MLX			:=	mlx

FT_PATH		:=	libft
FT			:=	ft

NAME	:=	fdf

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
GDB		:=	-g3
export GDB
CLIB	:=	-L$(FT_PATH) -L$(MLX_PATH) -l$(FT) -l$(MLX) -lXext -lX11 -lm

.PHONY: all
all: $(NAME)

$(NAME): $(MLX_PATH)/lib$(MLX).a $(FT_PATH)/lib$(FT).a $(OBJ)
	$(CC) $(CFLAGS) $(GDB) $(CINC) $(OBJ) -o $@ $(CLIB)

$(MLX_PATH)/lib$(MLX).a:
	make -C $(MLX_PATH)

$(FT_PATH)/lib$(FT).a:
	make -C $(FT_PATH)

-include $(DEPS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(GDB) $(CINC) -MMD -MP -c $< -o $@

$(OBJ_PATH):
	mkdir -p $@

.PHONY: clean fclean cleanlib re norm
clean:
	rm -f $(OBJ)
	rm -f $(DEPS)

fclean: clean
	make fclean -C $(FT_PATH)
	rm -f $(NAME)

cleanlib:
	make clean -C $(MLX_PATH)

re: fclean all

norm:
	make norm -C $(FT_PATH)
	norminette -R CheckForbiddenSourceHeader $(SRC)
	norminette -R CheckDefine $(INCPATH)
