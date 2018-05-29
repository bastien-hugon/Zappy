##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

NAME	= program

CC	= 

RM	= rm -f

SRCS	= 

OBJS	= $(SRCS:=.o)

CFLAGS = -I 
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
