// utils.h

/** Copyright (c) 2019 Mesibo
 * https://mesibo.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the terms and condition mentioned on https://mesibo.com
 * as well as following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions, the following disclaimer and links to documentation and source code
 * repository.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * Neither the name of Mesibo nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Documentation
 * https://mesibo.com/documentation/
 *
 * Source Code Repository
 * https://github.com/mesibo/python
 *
 */

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
