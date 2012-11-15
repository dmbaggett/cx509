/* -*- mode: C++; fill-column: 100; -*-
 *
 * This extension module exports the cx509 type. The underlying implementation is provided by
 * sset.c.
 *
 * dmb - Feb 2012 - Copyright (C) 2012 Arcode Corporation
 */
#include <Python.h>
#include <stdio.h>
#include "structmember.h"

/* forward declarations */
static PyTypeObject cx509Type;

typedef struct {
    PyObject_HEAD

} cx509;

static PyObject *
cx509_new(PyTypeObject *type, PyObject *args, PyObject *kw)
{
    cx509 *self = (cx509 *) type->tp_alloc(type, 0);
    return (PyObject *) self;
}

static int
cx509_init(cx509 *self, PyObject *args, PyObject *kw)
{
    static char *kwlist[] = { "data", "format", NULL };
    PyObject *data = NULL;
    PyObject *format = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kw, "|OO", kwlist, &data, &format)) {
	return -1;
    }	
    else if (data) {
	if (PyObject_IsInstance(data, (PyObject *) &cx509Type) == 1) {
	    /* we're cloning another cx509 */
	}
	else if (PyString_Check(data)) {
	    /* we've been given a string; parse it */
	}
    }
    return 0;
}

static void
cx509_free(PyObject *self)
{
    Py_TYPE(self)->tp_free(self);
}

static PyMemberDef cx509_members[] = {
    {NULL}  /* Sentinel */
};

static PyMethodDef cx509_methods[] = {
#if 0
    {"__contains__", (PyCFunction) cx509_contains, METH_VARARGS, "Return True if the provided value is in the cx509." },
    {"__getitem__", (PyCFunction) cx509_getitem, METH_VARARGS, "Return the nth value in the set." },
    {"__eq__", (PyCFunction) cx509_eq, METH_VARARGS, "Return True if self and the provided sset are identical." },
    {"parse", (PyCFunction) cx509_parse, METH_VARARGS, "Parse the provided string; set the cx509 to match the string." },
    {"number_of_ranges", (PyCFunction) cx509_number_of_ranges, METH_NOARGS, "Return the length of this cx509 in range pairs." },
    {"min_and_max", (PyCFunction) cx509_min_and_max, METH_NOARGS, "Return a tuple (min, max) of values in the cx509." },
    {"has_star", (PyCFunction) cx509_has_star, METH_NOARGS, "Return True if the cx509 contains the INFINITY value; False otherwise." },
    {"clone", (PyCFunction) cx509_clone, METH_VARARGS|METH_KEYWORDS, "Make this cx509 a clone of the provided cx509. The new cx509 will have its own memory." },
    {"optimize", (PyCFunction) cx509_optimize, METH_VARARGS|METH_KEYWORDS, "Optimize ranges in cx509." },
    {"clear", (PyCFunction) cx509_clear, METH_NOARGS, "Clear the cx509." },
    {"invert", (PyCFunction) cx509_invert, METH_NOARGS, "Return a new cx509 with all the values that are not in self." },
    {"union", (PyCFunction) cx509_union, METH_VARARGS, "Return a new cx509 with elements from both self and t." },
    {"update", (PyCFunction) cx509_update, METH_VARARGS, "Update cx509 so it includes elements from both self and t." },
    {"as_tuple_list", (PyCFunction) cx509_as_tuple_list, METH_NOARGS, "Return ranges as a list of 2-item tuples." },
    {"set_from_list", (PyCFunction) cx509_set_from_list, METH_VARARGS|METH_KEYWORDS, "Set initial values from provided list of itegers (lo, hi, lo, hi ...)." },
#endif
    {NULL}  /* Sentinel */
};

static PyTypeObject cx509Type = {
    PyObject_HEAD_INIT(NULL)
    0,				/*ob_size*/
    "cx509.cx509",  		/*tp_name*/
    sizeof(cx509),  		/*tp_basicsize*/
    0,                         /*tp_itemsize*/
    cx509_free,     		/*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "cx509 objects",		/* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    cx509_methods,  		/* tp_methods */
    cx509_members,  		/* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)cx509_init,      /* tp_init */
    0,                        /* tp_alloc */
    cx509_new,     /* tp_new */
};


static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC
initcx509(void) 
{
    PyObject* m;

    if (PyType_Ready(&cx509Type) < 0)
        return;

    m = Py_InitModule3("cx509", module_methods, "X.509 certificate");
    if (m == NULL)
	return;

    Py_INCREF(&cx509Type);
    PyModule_AddObject(m, "cx509", (PyObject *) &cx509Type);
}
