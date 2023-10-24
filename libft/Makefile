NAME = libft.a

LIBFT = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c 

GNL =	get_next_line.c \
		get_next_line_utils.c

PRINTF = ft_printf.c \
		ft_printf_utils.c


BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

all: $(NAME)

$(NAME):
	cc -c -Wall -Wextra -Werror $(LIBFT)
	cc -c -Wall -Wextra -Werror $(BONUS)
	cc -c -Wall -Wextra -Werror $(GNL)
	ar -crs $(NAME) $(LIBFT:.c=.o)
	ar -crs $(NAME) $(BONUS:.c=.o)
	ar -crs $(NAME) $(GNL:.c=.o)
	cc -c -Wall -Wextra -Werror -I libft $(PRINTF)
	ar -crs $(NAME) $(PRINTF:.c=.o)


clean:
	rm -f $(LIBFT:.c=.o) $(BONUS:.c=.o) $(GNL:.c=.o) $(PRINTF:.c=.o)

fclean: clean
	rm -f $(NAME) 

bonus:
	cc -c -Wall -Wextra -Werror $(BONUS)
	ar -urs $(NAME) $(BONUS:.c=.o)

re: fclean all