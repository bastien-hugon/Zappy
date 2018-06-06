/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** module
*/

#include "module.h"

int connection(int fd, struct sockaddr_in *s_in)
{
	if (connect(fd, (struct sockaddr *)s_in, sizeof(*s_in)) == -1) {
		close(fd);
		return (-1);
	}
	return (fd);
}

PyObject *get_fd_activity(PyObject *self, PyObject *args)
{
	int fd;
	FILE *file_d;
	char command[1025] = {0};
	fd_set fds;

	(void)self;
	if (!PyArg_ParseTuple(args, "i", &fd))
		return (Py_BuildValue("i" , -1));
	file_d = fdopen(fd, "r");
	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	if (select(2, &fds, NULL, NULL, NULL) == -1) {
		printf("Problem with select\n");
		return(Py_BuildValue("s" , NULL));
	}
	if (FD_ISSET(fd, &fds))
		fgets(command, 1025, file_d);
	return(Py_BuildValue("s" , command));
}

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

PyMODINIT_FUNC PyInit_sockets(void)
{
	return PyModule_Create(&sockets);
}