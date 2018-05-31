/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** module
*/

#include <Python.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int connection(int fd, struct sockaddr_in *s_in)
{
	if (connect(fd, (struct sockaddr *)s_in, sizeof(*s_in)) == -1) {
		close(fd);
		return (-1);
	}
	return (fd);
}

PyObject *create_socket(PyObject *self, PyObject *args)
{
	int fd;
	struct protoent *pe = getprotobyname("TCP");
	struct sockaddr_in s_in;
	const char *ip;
	const int port;

	(void)self;
	if (!PyArg_ParseTuple(args, "s|i", &ip, &port)){
		return (Py_BuildValue("i" , -1));
	}
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

static PyMethodDef SocketMethods[] = {
	{"create_socket", create_socket, METH_VARARGS, "Socket creation."},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef sockets =
{
	PyModuleDef_HEAD_INIT,
	"sockets",
	"",
	-1,
	SocketMethods,
	NULL,
	NULL,
	NULL,
	NULL
};

PyMODINIT_FUNC PyInit_sockets(void)
{
	return PyModule_Create(&sockets);
}