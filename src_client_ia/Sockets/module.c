/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** module
*/

/**
* @brief C module use by python to connect him by C networks functions
*
* @file module.c
* @author your name
* @date 2018-06-04
*/

#include "module.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int epollfd = 0;

/**
* @brief Set connexion between client and server
*
* @return int -> Filedescriptor
*/
int connection(int fd, struct sockaddr_in *s_in)
{
	if (connect(fd, (struct sockaddr *)s_in, sizeof(*s_in)) == -1) {
		close(fd);
		return (-1);
	}
	return (fd);
}

/**
* @brief check for a '\n' in the recieved message
*
* @param command [In], the command line
* @return int if '\n then 0 else -1
*/
int check_carriage_return(char *command)
{
	if (strlen(command) > 4000 || command[strlen(command) - 1] == '\n')
		return (0);
	else
		return (-1);
}

/**
* @brief Check if there is activity on server file descriptor
*
* @return string -> command or NULL if no activities
*/
PyObject *get_fd_activity(PyObject *self, PyObject *args)
{
	int fd;
	char command[16384] = {0};
	// fd_set fds;
	int nb_fds = 0;
	struct epoll_event events[1024];

	(void)self;
	if (!PyArg_ParseTuple(args, "i", &fd))
		return (Py_BuildValue("i" , -1));
	printf("Before epoll_wait\n");
	nb_fds = epoll_wait(epollfd, events, 1024, 0);
	for (int n = 0; n < nb_fds; ++n) {
		while (check_carriage_return(command) != 0)
			read(events[n].data.fd, command, 16384);
	}
	// FD_ZERO(&fds);
	// FD_SET(fd, &fds);
	// if (select(fd+1, &fds, NULL, NULL, NULL) == -1) {
	// 	printf("Problem with select\n");
	// 	return (Py_BuildValue("s" , NULL));
	// }
	// if (FD_ISSET(fd, &fds)) {
	// 	while (check_carriage_return(command) != 0)
	// 		read(fd, command, 16384);
	// }
	return (Py_BuildValue("s" , command));
}

/**
* @brief Send command to server
*
* @return int -> 0 for true and 1 for false
*/
PyObject *send_command(PyObject *self, PyObject *args)
{
	char *to_send;
	int fd;

	(void)self;
	if (!PyArg_ParseTuple(args, "s|iepollfd", &to_send, &fd))
		return (Py_BuildValue("i" , -1));
	printf("COMMAND : %s\n", to_send);
	if (dprintf(fd, "%s\n", to_send) <= 0)
		printf("Message not sent\n");
	else
		printf("Message sucess\n");
	return (Py_BuildValue("i", 0));
}

int init_epoll(int fd)
{
	struct epoll_event ev;

	epollfd = epoll_create1(0);
	if (epollfd == -1) {
		fprintf(stderr, "error: epoll_create1\n");
		exit(84);
	}
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		fprintf(stderr, "error: epoll_ctl\n");
		exit(84);
	}
	return (epollfd);
}

/**
* @brief Init connexion between graphic client and server
*
* @return int -> Filedescriptor
*/
PyObject *create_socket(PyObject *self, PyObject *args)
{
	int fd;
	int epollfd;
	int serverfd;
	struct protoent *pe = getprotobyname("TCP");
	struct sockaddr_in s_in;
	const char *ip;
	const int port;
	struct epoll_event ev;

	(void)self;
	if (!PyArg_ParseTuple(args, "s|i", &ip, &port))
		return (Py_BuildValue("i|i" , -1, -1));
	printf("%s %d\n", ip, port);
	if (!pe)
		return (Py_BuildValue("i|i" , -1, -1));
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return (Py_BuildValue("i|i" , -1, -1));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip);
	epollfd = init_epoll(fd);
	serverfd = connection(fd, &s_in);
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, serverfd, &ev);
	return (Py_BuildValue("i", serverfd));
}

/**
* @brief Init py functions
*
* @return PyMODINIT_FUNC
*/
PyMODINIT_FUNC PyInit_sockets(void)
{
	return (PyModule_Create(&sockets));
}
