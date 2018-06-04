##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

CC	= gcc

RM	= rm -f

DOC_NAME	= my_irc.html

NAME_SERVER	= "server"

NAME_CLIENT	= "client"

NAME_UT	= units

SRCS_UT_IRC =

SRCS_UT_SERV	=	./tests/server/arguments/test_argument_handling.c \
			./tests/server/list/test_list_create.c \
			./tests/server/list/test_list_next_prev.c \
			./tests/server/mocking/mock_malloc.c \
			./src_server/argument_handling/argument_handling.c \
			./src_server/list/list.c

SRCS_UT_CLIENT  =

SERV_SRCS	=	./src_server/argument_handling/argument_handling.c \
			./src_server/main.c

SERV_OBJS  = $(SERV_SRCS:.c=.o)

CLIENT_SRCS  = 

CLIENT_OBJS  = $(CLIENT_SRCS:.c=.o)

CFLAGS = -I ./src_server/include/

CFLAGS += -W -Wall -Wextra

TUFLAGS = -lcriterion -lgcov --coverage -DSTESTS -I ./tests/server/include

all: server

server: $(NAME_SERVER)

$(NAME_SERVER): $(SERV_OBJS)
	$(CC) $(SERV_OBJS) -o $(NAME_SERVER) $(CFLAGS) $(LDFLAGS)

client: $(NAME_CLIENT)

$(NAME_CLIENT): $(CLIENT_OBJS) $(IRC_OBJS)
	$(CC) $(IRC_OBJS) $(CLIENT_OBJS) -o $(NAME_CLIENT) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(SERV_OBJS) $(CLIENT_OBJS) $(IRC_OBJS)
	$(RM) *.g*

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	$(RM) $(NAME_UT)

tests_run: $(NAME_UT)

$(NAME_UT):
	gcc -o $(NAME_UT) $(SRCS_UT_IRC) $(SRCS_UT_CLIENT) $(SRCS_UT_SERV) $(CFLAGS) $(TUFLAGS)
	./units
	gcov *.gcda

doc: $(DOC_NAME)

$(DOC_NAME):
	doxygen

re: fclean all

.PHONY: server client tests_run doc all clean fclean re