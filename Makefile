RED		:=	\e[31m
GREEN	:=	\e[32m
ORANGE	:=	\e[33m
BLUE	:=	\e[34m
PURPLE	:=	\e[35m
CYAN	:=	\e[36m

BOLD	:=	\e[1m
DIM		:=	\e[2m
BOM		:=	\e[22m
ITA		:=	\e[3m
NOITA	:=	\e[23m

GOTO_B	:=	\e[1A\e[K

DEFAULT	:=	\e(B\e[m

FILES		:=	draw_line.c			\
				draw_line_utils.c	\
				events.c			\
				events_utils.c		\
				matrix.c			\
				parser.c			\
				parser_utils.c		\
				projections.c		\
				render.c			\
				render_utils.c		\
				transformations.c	\
				utils.c				\

FILES_BONUS	:=	frame_bonus.c		\
				frame_utils_bonus.c	\

SRC_PATH	:=	src
SRC			:=	$(addprefix $(SRC_PATH)/,$(FILES))
SRC_BONUS	:= $(SRC) $(addprefix $(SRC_PATH)/,$(FILES_BONUS))

OBJ_PATH	:=	build
OBJ			:=	$(addprefix $(OBJ_PATH)/,$(FILES:.c=.o))
OBJ_BONUS	:=	$(OBJ) $(addprefix $(OBJ_PATH)/,$(FILES_BONUS:.c=.o))
DEPS		:=	$(OBJ_BONUS:.o=.d)

INC_PATH	:=	include
CINC		:=	-I. -I$(INC_PATH)

MLX_PATH	:=	minilibx-linux
MLX			:=	mlx

FT_PATH		:=	libft
FT			:=	ft

NAME		:=	fdf
NAME_BONUS	:=	$(NAME)_bonus

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
GDB		:=	-g3
export GDB
CLIB	:=	-L$(FT_PATH) -L$(MLX_PATH) -l$(FT) -l$(MLX) -lXext -lX11 -lm

.PHONY: all bonus
all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) $(OBJ_PATH)/main.o $(MLX_PATH)/lib$(MLX).a $(FT_PATH)/lib$(FT).a
	@echo "$(ORANGE)$(ITA)Linking$(NOITA) into $(BOLD)$@$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(GDB) $(CINC) $(OBJ) $(OBJ_PATH)/main.o -o $@ $(CLIB) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)linked$(NOITA) into $(BOLD)$@$(DEFAULT)"

$(NAME_BONUS): $(OBJ_BONUS) $(OBJ_PATH)/main_bonus.o $(MLX_PATH)/lib$(MLX).a $(FT_PATH)/lib$(FT).a
	@echo "$(ORANGE)$(ITA)Linking$(NOITA) into $(BOLD)$@$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(GDB) $(CINC) $(OBJ_BONUS) $(OBJ_PATH)/main_bonus.o -o $@ $(CLIB) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)linked$(NOITA) into $(BOLD)$@$(DEFAULT)"

$(MLX_PATH)/lib$(MLX).a:
	@echo "$(ORANGE)$(ITA)Creating$(NOITA) $(BOLD)$@$(DEFAULT)..."
	@make --silent -C $(MLX_PATH) > /dev/null \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)created$(NOITA) $(BOLD)$@$(DEFAULT)"

$(FT_PATH)/lib$(FT).a:
	@echo "$(ORANGE)$(ITA)Creating$(NOITA) $(BOLD)$@$(DEFAULT)..."
	@make --silent -C $(FT_PATH) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)created$(NOITA) $(BOLD)$@$(DEFAULT)"

-include $(DEPS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@echo "$(ORANGE)$(ITA)Compiling$(NOITA) $(BOLD)$<$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(GDB) $(CINC) -MMD -MP -c $< -o $@ \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)compiled$(NOITA) $(BOLD)$<$(DEFAULT)"

$(OBJ_PATH):
	@mkdir -p $@ && echo "$(DIM)Directory $(ITA)$@/$(NOITA) created$(DEFAULT)"

.PHONY: clean fclean cleanlib re norm
clean:
	@( rm -r $(OBJ_PATH) 2> /dev/null \
		&& echo "$(RED)$(ITA)Removed$(NOITA) object files and their directory$(DEFAULT)" ) \
		|| :

fclean: clean
	@( rm $(NAME) 2> /dev/null \
		&& echo "$(RED)$(ITA)Removed$(NOITA) executable $(NAME)$(DEFAULT)" ) \
		|| :

cleanlib:
	@echo "Cleaning the library..."
	@make --silent fclean -C $(FT_PATH) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)cleaned$(NOITA) the library$(DEFAULT)"

re: fclean all

norm:
	@echo "$(CYAN)libft :$(DEFAULT)"
	@make --silent norm -C $(FT_PATH)
	@echo "$(CYAN)fdf :$(DEFAULT)"
	@norminette -R CheckForbiddenSourceHeader $(SRC_BONUS) $(SRC_PATH)/main.c $(SRC_PATH)/main_bonus.c
	@norminette -R CheckDefine $(INC_PATH)
