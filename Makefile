##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

NAME	= program

GFX_NAME	=	client_gfx

CC	= gcc

RM	= rm -f

GFX_SRCS = ./src_client_gfx/module.c

SRCS	= 

GFX_OBJS = $(GFX_SRCS:.c=.o)

OBJS	= $(SRCS:.c=.o)

CFLAGS = $(python3-config --includes)
CFLAGS += -W -Wall -Wextra -fpic --shared

gfx: $(GFX_NAME)

$(GFX_NAME): $(GFX_OBJS)
	$(CC) -fPIC --shared $(GFX_OBJS) -o sockets.abi3.so

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
