NAME = minishell

SRCS = main.c \
		minishell_utils.c \
		handle_file.c \
		handle_err.c \
		free.c \
		signal.c \
		lexer.c \
		lexer_utils.c \
		expandor.c \
		expandor_utils.c \
		heredoc.c \
		heredoc_utils.c \
		parser.c \
		parser_utils.c \
		executor.c \
		executor_utils.c \
		buildin_env_initiate.c \
		buildin_env_getenv.c \
		buildin_exit.c \
		buildin.c \
		buildin_cd_util1.c \
		buildin_cd.c \
		buildin_echo.c \
		buildin_export.c \
		buildin_pwd.c \
		buildin_env_setenv.c \
		buildin_env_unset.c \

CC = cc

LINKS = -L ./libft -lft

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

RL_L = -lreadline -L ~/.brew/opt/readline/lib
RL_I = -I ~/.brew/opt/readline/include/readline

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft/
	$(CC) -o $@ $(OBJS) $(FLAGS) $(LINKS) $(RL_L) $(RL_I)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean fclean re

clean:
	rm -f *.o
	rm -f libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all