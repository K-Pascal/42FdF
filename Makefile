RED		:=	\e[31m
GREEN	:=	\e[32m
ORANGE	:=	\e[33m
BLUE	:=	\e[34m
PURPLE	:=	\e[35m
CYAN	:=	\e[36m

BOLD	:=	\e[1m
DIM		:=	\e[2m
BOM		:=	\e[22m
ITA	:=	\e[3m
NOITA	:=	\e[23m

GOTO_B	:=	\e[1A\e[K

DEFAULT	:=	\e(B\e[m

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

$(NAME): $(OBJ) $(MLX_PATH)/lib$(MLX).a $(FT_PATH)/lib$(FT).a
	@echo "$(ORANGE)$(ITA)Linking$(NOITA) into $(BOLD)$@$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(GDB) $(CINC) $(OBJ) -o $@ $(CLIB) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)linked$(NOITA) into $(BOLD)$@$(DEFAULT)"

$(MLX_PATH)/lib$(MLX).a:
	@echo "$(ORANGE)$(ITA)Creating$(NOITA) $(BOLD)$@$(DEFAULT)"
	@make --silent -C $(MLX_PATH) > /dev/null \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)created$(NOITA) $(BOLD)$@$(DEFAULT)"

$(FT_PATH)/lib$(FT).a:
	@echo "$(ORANGE)$(ITA)Creating$(NOITA) $(BOLD)$@$(DEFAULT)"
	@make --silent -C $(FT_PATH) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)created$(NOITA) $(BOLD)$@$(DEFAULT)"


-include $(DEPS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile | $(OBJ_PATH)
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
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@norminette -R CheckDefine $(INCPATH)
