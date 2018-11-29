NAME		= 42sh

LIB			= libft.a
LIB_DIR		= libft
LIB_PATH	= $(LIB_DIR)/$(LIB)

TERMCAP		= -ltermcap
READLINE	= ft_readline/libft_readline.a

CC			= gcc
FLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
INCLUDES	= -I ./libft/includes -I ./includes
COMPILE		= $(CC) $(FLAGS) $(INCLUDES)

SRCS		= $(addprefix srcs/, main.c errors.c init_shell.c\
	$(addprefix builtins/, b_cd.c b_echo.c b_env.c b_setenv.c b_unsetenv.c builtin.c\
				b_exit.c b_export.c b_unset.c)\
	$(addprefix exec/, assignments.c exec_cmd.c exec_tree.c exec_semi_and_or.c expand_str.c strip_quotes.c\
				expand.c path.c redirects.c back_ticks.c hash_path.c)\
	$(addprefix parser/, parse_tokens.c preliminary_parse.c tree2.c \
				expand_token.c expand_tokens.c utils.c \
				stack.c print_infos.c init_structs.c redirections.c)\
	$(addprefix tokenizer/, )\
	$(addprefix local_var/, local_var.c local_var_comp.c)\
)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB) $(READLINE)
	$(COMPILE) $(OBJS) $(LIB_PATH) $(TERMCAP) $(READLINE) -o $(NAME)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIB):
	make -C $(LIB_DIR)

$(READLINE):
	make -C ft_readline

clean:
	make clean -C $(LIB_DIR)
	make clean -C ft_readline
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIB_DIR)
	make fclean -C ft_readline
	rm -rf $(NAME)

re: fclean all
