##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

SOCKET_NAME	=	sockets.so

CC	= 	gcc

RM	= 	rm -f

SOCKET_SRCS	=	Sockets/module.c	\
			Sockets/module2.c

SOCKET_OBJS	=	$(SOCKET_SRCS:.c=.o)

CFLAGS	=	-W -Wall -Wextra

CFLAGS	+=	-fpic --shared -I/usr/include/python3.6m -I./Sockets/include

all: socket

socket: $(SOCKET_NAME)

$(SOCKET_NAME): $(SOCKET_OBJS)
	$(CC) -fpic --shared -I/usr/include/python3.6m $(SOCKET_OBJS) -o $(SOCKET_NAME)

clean:
	$(RM) $(OBJS) $(SOCKET_OBJS)

fclean: clean
	$(RM) $(NAME) $(SOCKET_NAME)

re: fclean all

.PHONY: all clean fclean re
