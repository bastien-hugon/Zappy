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
* @brief Check if there is activity on server file descriptor
*
* @return string -> command or NULL if no activities
*/
PyObject *get_fd_activity(PyObject *self, PyObject *args)
{
	int fd;
	FILE *file_d;
	int nb_read;
	char command[4096] = {0};
	fd_set fds;

	(void)self;
	if (!PyArg_ParseTuple(args, "i", &fd))
		return (Py_BuildValue("i" , -1));
	file_d = fdopen(fd, "r");
	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	if (select(fd+1, &fds, NULL, NULL, NULL) == -1) {
		printf("Problem with select\n");
		return (Py_BuildValue("s" , NULL));
	}
	if (FD_ISSET(fd, &fds)) {
		nb_read = read(fd, command, 4096);
	}
	printf("nb_read = %d\n", nb_read);
	command[nb_read] = '\0';
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
	if (!PyArg_ParseTuple(args, "s|i", &to_send, &fd))
		return (Py_BuildValue("i" , -1));
	printf("COMMAND : %s\n", to_send);
	dprintf(fd, "%s\n", to_send);
	// printf("WRITE RETURN: %ld\n", write(fd, to_send, strlen(to_send)));
	return (Py_BuildValue("i", 0));
}

/**
* @brief Init connexion between graphic client and server
*
* @return int -> Filedescriptor
*/
PyObject *create_socket(PyObject *self, PyObject *args)
{
	int fd;
	struct protoent *pe = getprotobyname("TCP");
	struct sockaddr_in s_in;
	const char *ip;
	const int port;

	(void)self;
	if (!PyArg_ParseTuple(args, "s|i", &ip, &port))
		return (Py_BuildValue("i" , -1));
	if (!pe)
		return (Py_BuildValue("i" , -1));
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return (Py_BuildValue("i" , -1));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip);
	return (Py_BuildValue("i", connection(fd, &s_in)));
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