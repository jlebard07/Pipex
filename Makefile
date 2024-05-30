NAME = pipex
SRC = pipex.c utils.c
CC = cc 
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRC:.c=.o)
CLEAN = rm -rf
FCLEAN = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a .
	$(CC) $(CFLAGS) $(OBJS) libft.a -o $(NAME)	

all: $(NAME)

clean:
	$(CLEAN) libft/*.o 
	$(CLEAN) *.o
	$(CLEAN) libft.a
	$(CLEAN) libft/libft.a

fclean: clean
	$(FCLEAN) $(NAME)

re: fclean all

.PHONY: all clean fclean re