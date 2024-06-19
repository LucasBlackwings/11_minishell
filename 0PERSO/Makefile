NAME = minishell
CC = cc
CFLAGS = -lreadline -Wall -Wextra -Werror -g3 -std=c99 -pedantic -fsanitize=leak -fsanitize=address -fsanitize=undefined
OFLAGS = -Wall -Wextra -Werror -g3 -std=c99 -pedantic -fsanitize=leak -fsanitize=address -fsanitize=undefined

SOURCES =	main.c \
			build_prompt.c \
			split_minishell.c \

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
