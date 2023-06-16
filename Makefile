# - * - Makefile - * -

NAME = minishell
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
RM = rm -rf

SRC_MSH = main.c signals.c

SRCS = $(addprefix src/, $(SRC_MSH))
OBJS = $(patsubst src/%, $(OBJS_DIR)/%, $(SRCS:%.c=%.o))

GREEN	=	"\033[0;32m"
NC		=	"\033[0m"

OBJS_DIR	=	obj
LFT_DIR		=	libft

INC = -lreadline
LIBFT = $(LFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) $(INC) $(SRCS) $(LIBFT) -o $(NAME)
		@echo $(GREEN)"Compiled!"$(NC)

$(OBJS_DIR)/%.o: $(SRCS)
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -o $@ -c $<

clean:
		@$(RM) $(OBJS) $(OBJS_DIR)
		@make clean --no-print-directory -C $(LFT_DIR)

fclean: clean
		@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re