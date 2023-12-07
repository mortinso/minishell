# - * - Makefile - * -

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

SRC_MSH	=	frees.c frees2.c main.c prompt.c signals.c signals2.c
SRC_BLT	=	$(addprefix built-ins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
SRC_ERR =	$(addprefix error_handling/, errors.c errors2.c syntax_errors.c syntax_errors2.c)
SRC_RUN =	$(addprefix run/, exec_built_ins.c exec.c redirections.c heredoc.c heredoc_utils.c run.c cmd_validator.c)
SRC_PRS	=	$(addprefix parser/, parse_counter.c parse_split.c parse_str.c)
SRC_RPL =	$(addprefix replacer/, replacer_utl.c rep.c)
SRC_STC	=	$(addprefix structs/, cmd_utils.c content.c init.c)
SRC_UTL	=	$(addprefix utils/, array_utl.c list_utl.c quote_utl.c str_utl.c str_utl2.c)

SRCS	=	$(addprefix $(SRC_DIR)/, $(SRC_MSH) $(SRC_BLT) $(SRC_ERR) $(SRC_RUN) $(SRC_PRS) $(SRC_RPL) $(SRC_STC) $(SRC_UTL))

OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
NC		=	"\033[0m"

SRC_DIR	=	src
OBJ_DIR	=	obj
LFT_DIR	=	libft

LIBFT	=	$(LFT_DIR)/libft.a
INC		=	-lreadline

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INC)
	@echo $(GREEN)"Compiled!"$(NC)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@$(CC) $(CFLAGS) -c $< -o $@

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
