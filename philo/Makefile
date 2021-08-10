NAME = philo

SRCS =	srcs/main.c \
		srcs/check_args.c \
		srcs/philo_monitor.c \
		srcs/philo_thread.c \
		srcs/init_free.c \
		srcs/utils.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
		@gcc $(CFLAGS) -o $(NAME) $^

%.o:	%.c
		@gcc $(CFLAGS) -c $< -o $@ -I./includes

clean:
		@$(RM) $(OBJS)

fclean:	clean
		@$(RM) $(NAME)

re:		fclean all

.PHONY: all bonus clean fclean re