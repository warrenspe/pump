/*
 *  types.c: A file containing logic to discern what type of Python object is being serialized.
 *  Copyright (C) 2016 Warren Spencer warrenspencer27@gmail.com

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "headers/pump.h"
#include "longintrepr.h"


unsigned char getType(PyObject *obj) {
/* Function which determines what type a given python object is (see pump.h for type definitions).
 *
 * Inputs: obj - The python object to determine the type of.
 *
 * Outputs: A positive integer (in a char) on successful detection of the type of obj.
 *          0 if unable to determine the type of obj.
 */

    if (PyInt_CheckExact(obj)) {
        if (PyLong_AsLongLong(obj) < 0)
            return NEG_INT_TYPE;
        return INT_TYPE;

    } else if (PyLong_CheckExact(obj)) {
        if (((PyLongObject *) obj)->ob_size < 0)
            return NEG_LONG_TYPE;
        return LONG_TYPE;

    } else if (PyFloat_CheckExact(obj)) {
        return FLOAT_TYPE;

    } else if (PyString_Check(obj)) {
        return STRING_TYPE;

    } else if (PyUnicode_Check(obj)) {
        return UNICODE_TYPE;

    } else if (PyList_CheckExact(obj)) {
        return LIST_TYPE;

    } else if (PyTuple_CheckExact(obj)) {
        return TUPLE_TYPE;

    } else if (PyDict_CheckExact(obj)) {
        return DICT_TYPE;

    } else if (obj == Py_None) {
        return NONE_TYPE;

    } else if (PyAnySet_CheckExact(obj)) {
        if (PyFrozenSet_CheckExact(obj))
            return FROZEN_SET_TYPE;
        return SET_TYPE;
    }

    PyErr_Format(PyExc_TypeError, "Unknown object type \"%.400s\"", Py_TYPE(obj)->tp_name);
    return 0;
}
