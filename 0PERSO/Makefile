NAME = minishell
CC = cc
CFLAGS = -lreadline -Wall -Wextra -Werror -g3 -std=c99 -pedantic -fsanitize=leak -fsanitize=address -fsanitize=undefined
OFLAGS = -Wall -Wextra -Werror -g3 -std=c99 -pedantic -fsanitize=leak -fsanitize=address -fsanitize=undefined
# make re && make clean && clear && ./minishell

SOURCES =	main.c \
			./parser/parser_control.c \
			./parser/parser_core.c \
			./parser/parser_inbuilts_syntax.c \
			./parser/parser_megasplit.c \
			./parser/parser_utils.c \
			./prompt/build_prompt.c \
			./utils/utils_libft_utils.c \
			./utils/utils_minishell_utils.c \
			./utils/utils_minisplit.c \
			./utils/utils_printf_error.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(OFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean:
	rm -f $(NAME) $(OBJECTS)

re: fclean all

.PHONY: all clean fclean re
