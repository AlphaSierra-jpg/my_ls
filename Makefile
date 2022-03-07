CC = gcc
NAME = my_ls
SRC = main.c \
	  my_ls.c \
	  my_function.c \
	  my_ls_l.c \
	  my_ls_diffl.c

OBJ = $(SRC:%.c=%.o)
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -L. -lmy 
$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
all:		$(NAME)

clean:		
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all