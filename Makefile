# - * - Makefile - * -

NAME = minishell
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

SRC_MSH	=	frees.c frees2.c main.c prompt.c signals.c signals2.c
SRC_BLT	=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRC_ERR =	errors.c errors2.c syntax_errors.c syntax_errors2.c
SRC_RUN =	exec_built_ins.c exec.c redirections.c heredoc.c run.c cmd_validator.c
SRC_PRS	=	parse_counter.c parse_split.c parse_str.c
SRC_RPL =	replacer_chr.c replacer_split.c replacer_split2.c replacer_utl.c replacer.c
SRC_STC	=	cmd_utils.c content.c init.c
SRC_UTL	=	array_utl.c list_utl.c quote_utl.c str_utl.c

OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRC_MSH:%.c=%.o)) $(addprefix $(OBJ_DIR)/built-ins/, $(SRC_BLT:%.c=%.o)) \
			$(addprefix $(OBJ_DIR)/error_handling/, $(SRC_ERR:%.c=%.o)) $(addprefix $(OBJ_DIR)/run/, $(SRC_RUN:%.c=%.o)) \
			$(addprefix $(OBJ_DIR)/parser/, $(SRC_PRS:%.c=%.o)) $(addprefix $(OBJ_DIR)/replacer/, $(SRC_RPL:%.c=%.o)) \
			$(addprefix $(OBJ_DIR)/structs/, $(SRC_STC:%.c=%.o)) $(addprefix $(OBJ_DIR)/utils/, $(SRC_UTL:%.c=%.o))

GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
NC		=	"\033[0m"

SRC_DIR	=	src
OBJ_DIR	=	obj
LFT_DIR	=	libft
OBJ_DIRS	=	$(OBJ_DIR)/built-ins/ $(OBJ_DIR)/error_handling/ $(OBJ_DIR)/run/ $(OBJ_DIR)/parser/ $(OBJ_DIR)/replacer/ \
				$(OBJ_DIR)/structs/ $(OBJ_DIR)/utils/

LIBFT	=	$(LFT_DIR)/libft.a
INC		=	-lreadline

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INC)
		@echo $(GREEN)"Compiled!"$(NC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

val: $(NAME)
	@valgrind --track-fds=yes --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.supp ./minishell

val_child: $(NAME)
	@valgrind --trace-children=yes --track-fds=yes --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.supp ./minishell

clean:
		@$(RM) $(OBJS) $(OBJ_DIR)
		@make clean --no-print-directory -C $(LFT_DIR)

fclean: clean
		@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re val
