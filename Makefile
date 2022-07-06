SRCS = src/main.c src/time.c src/utils.c src/threads.c src/access.c src/thread_utils.c src/loops.c src/check_input.c
NAME = philo
CFLAGS = -Werror -Wextra -Wall -pthread -fsanitize=thread

$(NAME): $(SRCS)
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	cd src && rm -f $(wildcard *.o)

fclean: clean
	rm -f $(NAME)

re: fclean all