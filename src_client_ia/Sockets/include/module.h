/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** module
*/

#ifndef MODULE_H_
	#define MODULE_H_

#include <Python.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

PyObject *create_socket(PyObject *self, PyObject *args);
PyObject *get_fd_activity(PyObject *self, PyObject *args);
PyObject *send_command(PyObject *self, PyObject *args);


static PyMethodDef SocketMethods[] = {
	{"create_socket", create_socket, METH_VARARGS, "Socket creation."},
	{"get_fd_activity", get_fd_activity, METH_VARARGS, "FD selection."},
	{"send_command", send_command, METH_VARARGS, "Send command to serv."},
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
#endif /* !MODULE_H_ */
