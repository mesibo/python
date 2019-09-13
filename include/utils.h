// utils.h

#pragma once

#include <Python.h>
#include <mesibo.h>

uint8_t mesibo_py_get_param_ui8(PyObject* py_dict, const char* key);
uint16_t mesibo_py_get_param_ui16(PyObject* py_dict, const char* key);
int32_t mesibo_py_get_param_i32(PyObject* py_dict, const char* key);
uint32_t mesibo_py_get_param_ui32(PyObject* py_dict, const char* key);
uint64_t mesibo_py_get_param_ui64(PyObject* py_dict, const char* key);

double mesibo_py_get_param_double(PyObject* py_dict, const char* key);
int mesibo_py_get_param_int(PyObject* py_dict, const char* key);
char* mesibo_py_get_param_string(PyObject* py_dict, const char* key);
char* mesibo_py_get_string(PyObject* py_string);
void* mesibo_py_get_param_voidptr(PyObject* py_dict, const char* key);

void mesibo_py_get_param_messagedict(PyObject* py_dict, tMessageParams* p);
void mesibo_py_build_param_messagedict(PyObject* py_dict, tMessageParams* p);
void mesibo_py_get_param_bundledict(PyObject* py_dict, tMessageBundle* m);
void mesibo_py_build_param_bundledict(PyObject* py_dict, tMessageBundle* m);

void mesibo_py_log_param_message(tMessageParams* p);
void mesibo_py_log_param_bundle(tMessageBundle* m);

PyObject* mesibo_py_get_callableclass(PyObject* py_class);
