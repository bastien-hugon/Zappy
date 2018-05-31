##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

NAME	= program

GFX_NAME	=	sockets.so

CC	= gcc

RM	= rm -f

GFX_SRCS = ./src_client_gfx/module.c

SRCS	= 

GFX_OBJS = $(GFX_SRCS:.c=.o)

OBJS	= $(SRCS:.c=.o)

CFLAGS = -W -Wall -Wextra

CFLAGS += -fpic --shared -I/usr/include/python3.6m -I./src_client_gfx/include

all: gfx

gfx: $(GFX_NAME)

$(GFX_NAME): $(GFX_OBJS)
	$(CC) -fpic --shared -I/usr/include/python3.6m -I./src_client_gfx/include $(GFX_OBJS) -o sockets.so
	cp src_client_gfx/hello.py .

clean:
	$(RM) $(OBJS) $(GFX_OBJS)

fclean: clean
	$(RM) $(NAME) $(GFX_NAME) hello.py

re: fclean all

.PHONY: all clean fclean re
