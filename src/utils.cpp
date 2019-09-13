// utils.cpp

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

#define MESIBO_INT32_MAX  0x7fffffff
#define MESIBO_INT32_MIN  0x80000001
#define MESIBO_UINT8_MAX  0xff
#define MESIBO_UINT16_MAX 0xffff
#define MESIBO_UINT32_MAX 0xffffffff
#define MESIBO_UINT64_MAX 0xffffffffffffffff


#include "utils.h"
#include <Python.h>
#include <inttypes.h>
#include "globals.h"

uint8_t mesibo_py_get_param_ui8(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    unsigned long temp_item =
        PyLong_AsUnsignedLong(PyDict_GetItem(py_dict, py_key));
    if (temp_item > MESIBO_UINT8_MAX) {
      PyErr_Format(PyExc_OverflowError, "Invalid unsigned 8-bit integer: %s",
                   key);
      return -1;
    }

    return temp_item;
  }

  return 0;
}

uint16_t mesibo_py_get_param_ui16(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    unsigned long temp_item =
        PyLong_AsUnsignedLong(PyDict_GetItem(py_dict, py_key));
    if (temp_item > MESIBO_UINT16_MAX) {
      PyErr_Format(PyExc_OverflowError, "Invalid unsigned 16-bit integer: %s",
                   key);
      return -1;
    }

    return temp_item;
  }
  return 0;
}

uint32_t mesibo_py_get_param_ui32(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    unsigned long temp_item =
        PyLong_AsUnsignedLong(PyDict_GetItem(py_dict, py_key));
    if (temp_item > MESIBO_UINT32_MAX) {
      PyErr_Format(PyExc_OverflowError, "Invalid unsigned 32-bit integer: %s",
                   key);
      return -1;
    }

    return temp_item;
  }
  return 0;
}

int32_t mesibo_py_get_param_i32(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    unsigned long temp_item = PyLong_AsLong(PyDict_GetItem(py_dict, py_key));
    return temp_item;
  }
  return 0;
}

uint64_t mesibo_py_get_param_ui64(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    unsigned long long temp_item =
        PyLong_AsUnsignedLongLong(PyDict_GetItem(py_dict, py_key));
    return temp_item;
  }
  return 0;
}

double mesibo_py_get_param_double(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    double temp_item = PyFloat_AsDouble(PyDict_GetItem(py_dict, py_key));
    return temp_item;
  }
  return 0;
}

int mesibo_py_get_param_int(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);

  if (PyDict_Contains(py_dict, py_key) == 1) {
    long temp_item = PyLong_AsLong(PyDict_GetItem(py_dict, py_key));
    // Overflow check handled by pyobject
    return temp_item;
  }
  return 0;
}

char* mesibo_py_get_string(PyObject* py_string) {
  char* c_string;
#if PY_MAJOR_VERSION >= 3
  c_string =
      PyBytes_AS_STRING(PyUnicode_AsEncodedString(py_string, "utf-8", "~E~"));

#else
  c_string = PyString_AsString(py_string);

#endif
  return c_string;
}

char* mesibo_py_get_param_string(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);
  char* c_string = (char*)"";

  if (PyDict_Contains(py_dict, py_key) == 1) {
    return mesibo_py_get_string(PyDict_GetItem(py_dict, py_key));
  }

  return c_string;
}

void* mesibo_py_get_param_voidptr(PyObject* py_dict, const char* key) {
  PyObject* py_key = Py_BuildValue("s", key);
  PyObject* temp_item;

  if (PyDict_Contains(py_dict, py_key) == 1) {
    temp_item = PyDict_GetItem(py_dict, py_key);
    return PyLong_AsVoidPtr(temp_item);
  }

  return NULL;
}

void mesibo_py_get_param_messagedict(PyObject* py_dict, tMessageParams* p) {
 
  p->id            = mesibo_py_get_param_ui64(py_dict, ID);
  p->refid         = mesibo_py_get_param_ui64(py_dict, REFID);
  p->uid           = mesibo_py_get_param_ui32(py_dict, UID);
  p->groupid       = mesibo_py_get_param_ui32(py_dict, GROUPID);
  p->expiry        = mesibo_py_get_param_i32(py_dict, EXPIRY);
  p->flag          = mesibo_py_get_param_ui32(py_dict, FLAG);
  p->when          = mesibo_py_get_param_ui64(py_dict, WHEN);
  p->retaints      = mesibo_py_get_param_ui64(py_dict, RETAINTS);
  p->uflags        = mesibo_py_get_param_ui32(py_dict, UFLAGS);
  p->status        = mesibo_py_get_param_ui16(py_dict, STATUS);
  p->channel       = mesibo_py_get_param_ui16(py_dict, CHANNEL);
  p->type          = mesibo_py_get_param_ui16(py_dict, TYPE);
  p->origin        = mesibo_py_get_param_ui8(py_dict, ORIGIN);
  p->saved         = mesibo_py_get_param_ui8(py_dict, SAVED);
  p->thumbnail     = mesibo_py_get_param_string(py_dict, THUMBNAIL);
  p->tnlen         = mesibo_py_get_param_int(py_dict, TNLEN);
  p->filepath      = mesibo_py_get_param_string(py_dict, FILEPATH);
  p->read_session  = mesibo_py_get_param_voidptr(py_dict, READ_SESSION);

}

void mesibo_py_build_param_messagedict(PyObject* py_dict, tMessageParams* p) {
  PyDict_SetItem(py_dict, Py_BuildValue("s", ID),
                 PyLong_FromUnsignedLongLong(p->id));

  PyDict_SetItem(py_dict, Py_BuildValue("s", REFID),
                 PyLong_FromUnsignedLongLong(p->refid));

  PyDict_SetItem(py_dict, Py_BuildValue("s", UID),
                 PyLong_FromUnsignedLong(p->uid));

  PyDict_SetItem(py_dict, Py_BuildValue("s", GROUPID),
                 PyLong_FromUnsignedLong(p->groupid));

  PyDict_SetItem(py_dict, Py_BuildValue("s", EXPIRY),
                 PyLong_FromLong(p->expiry));

  PyDict_SetItem(py_dict, Py_BuildValue("s", FLAG),
                 PyLong_FromUnsignedLong(p->flag));

  PyDict_SetItem(py_dict, Py_BuildValue("s", WHEN),
                 PyLong_FromUnsignedLongLong(p->when));

  PyDict_SetItem(py_dict, Py_BuildValue("s", RETAINTS),
                 PyLong_FromUnsignedLongLong(p->retaints));

  PyDict_SetItem(py_dict, Py_BuildValue("s", UFLAGS),
                 PyLong_FromUnsignedLong(p->uflags));

  PyDict_SetItem(py_dict, Py_BuildValue("s", STATUS),
                 PyLong_FromUnsignedLong(p->status));

  PyDict_SetItem(py_dict, Py_BuildValue("s", CHANNEL),
                 PyLong_FromUnsignedLong(p->channel));

  PyDict_SetItem(py_dict, Py_BuildValue("s", TYPE),
                 PyLong_FromUnsignedLong(p->type));

  PyDict_SetItem(py_dict, Py_BuildValue("s", ORIGIN),
                 PyLong_FromUnsignedLong(p->origin));

  PyDict_SetItem(py_dict, Py_BuildValue("s", SAVED),
                 PyLong_FromUnsignedLong(p->saved));

  PyDict_SetItem(py_dict, Py_BuildValue("s", THUMBNAIL),
                 Py_BuildValue("s", (p->thumbnail) ? (p->thumbnail) : ""));

  PyDict_SetItem(py_dict, Py_BuildValue("s", TNLEN), PyLong_FromLong(p->tnlen));

  PyDict_SetItem(py_dict, Py_BuildValue("s", FILEPATH),
                 Py_BuildValue("s", (p->filepath) ? (p->filepath) : ""));

  PyDict_SetItem(py_dict, Py_BuildValue("s", READ_SESSION),
                 (p->read_session) ? PyLong_FromUnsignedLongLong(
                                         *((uint64_t*)p->read_session))
                                   : Py_BuildValue("i", 0));
}

void mesibo_py_build_param_bundledict(PyObject* py_dict, tMessageBundle* m) {
  PyDict_SetItem(py_dict, Py_BuildValue("s", MSGLEN),
                 PyLong_FromUnsignedLong(m->msglen));

  PyDict_SetItem(py_dict, Py_BuildValue("s", MESSAGE),
                 Py_BuildValue("s", m->message));

  PyDict_SetItem(py_dict, Py_BuildValue("s", TITLE),
                 Py_BuildValue("s", m->title));

  PyDict_SetItem(py_dict, Py_BuildValue("s", FILESIZE),
                 PyLong_FromUnsignedLong(m->filesize));

  PyDict_SetItem(py_dict, Py_BuildValue("s", FILETYPE),
                 PyLong_FromUnsignedLong(m->filetype));

  PyDict_SetItem(py_dict, Py_BuildValue("s", FILEURL),
                 Py_BuildValue("s", m->fileurl));

  PyDict_SetItem(py_dict, Py_BuildValue("s", FILEPATH),
                 Py_BuildValue("s", m->filepath));

  PyDict_SetItem(py_dict, Py_BuildValue("s", LAUNCHURL),
                 Py_BuildValue("s", m->launchurl));


  PyDict_SetItem(py_dict, Py_BuildValue("s", TNSLEN),
                 PyLong_FromUnsignedLong(m->tnslen));


  PyDict_SetItem(py_dict, Py_BuildValue("s", TNLEN),
                 PyLong_FromUnsignedLong(m->tnlen));

  PyDict_SetItem(py_dict, Py_BuildValue("s", HAS_LOCATION),
                 PyLong_FromLong(m->has_location));

  PyDict_SetItem(py_dict, Py_BuildValue("s", LAT),
                 PyLong_FromUnsignedLong(m->lat));

  PyDict_SetItem(py_dict, Py_BuildValue("s", LON),
                 PyLong_FromUnsignedLong(m->lon));

  PyDict_SetItem(py_dict, Py_BuildValue("s", LAT_D),
                 PyLong_FromDouble(m->lat_d));

  PyDict_SetItem(py_dict, Py_BuildValue("s", LON_D),
                 PyLong_FromDouble(m->lon_d));

  PyDict_SetItem(py_dict, Py_BuildValue("s", LOCATION),
                 PyLong_FromUnsignedLongLong(m->location));

  PyDict_SetItem(py_dict, Py_BuildValue("s", RRID),
                 PyLong_FromUnsignedLongLong(m->rrid));

  PyDict_SetItem(py_dict, Py_BuildValue("s", ACTIVITY),
                 PyLong_FromLong(m->activity));

  PyDict_SetItem(py_dict, Py_BuildValue("s", HAS_ACTIVITY),
                 PyLong_FromLong(m->has_activity));
}

void mesibo_py_get_param_bundledict(PyObject* py_dict, tMessageBundle* m) {

  m->data            = mesibo_py_get_param_string(py_dict,DATA);
  m->datalen         = mesibo_py_get_param_ui32(py_dict,DATALEN);
  m->msglen          = mesibo_py_get_param_ui32(py_dict,MSGLEN);
  m->message         = mesibo_py_get_param_string(py_dict,MESSAGE);
  m->title           = mesibo_py_get_param_string(py_dict,TITLE); 
  m->filesize        = mesibo_py_get_param_ui32(py_dict,FILESIZE);
  m->filetype        = mesibo_py_get_param_ui16(py_dict,FILETYPE);
  m->fileurl         = mesibo_py_get_param_string(py_dict,FILEURL);
  m->filepath        = mesibo_py_get_param_string(py_dict,FILEPATH);
  m->launchurl       = mesibo_py_get_param_string(py_dict,LAUNCHURL);
  m->thumbnail_send  = mesibo_py_get_param_string(py_dict,THUMBNAIL_SEND);
  m->tnslen          = mesibo_py_get_param_ui16(py_dict,TNSLEN);
  m->thumbnail       = mesibo_py_get_param_string(py_dict,THUMBNAIL);
  m->tnlen           = mesibo_py_get_param_ui16(py_dict,TNLEN);
  m->has_location    = mesibo_py_get_param_int(py_dict,HAS_LOCATION);
  m->lat             = mesibo_py_get_param_ui32(py_dict,LAT);
  m->lon             = mesibo_py_get_param_ui32(py_dict,LON);
  m->lat_d           = mesibo_py_get_param_double(py_dict,LAT_D);
  m->lon_d           = mesibo_py_get_param_double(py_dict,LON_D);
  m->location        = mesibo_py_get_param_ui64(py_dict,LOCATION);
  m->rrid            = mesibo_py_get_param_ui64(py_dict,RRID);
  m->activity        = mesibo_py_get_param_int(py_dict,ACTIVITY);
  m->has_activity    = mesibo_py_get_param_int(py_dict,HAS_ACTIVITY);

}

void mesibo_py_log_param_message(tMessageParams* p) {
  DEBUG("%" PRIu64 " " ID "        \n", p->id);
  DEBUG("%" PRIu64 " " REFID "     \n", p->refid);
  DEBUG("%" PRIu32 " " UID "       \n", p->uid);
  DEBUG("%" PRIu32 " " GROUPID "   \n", p->groupid);
  DEBUG("%" PRId32 " " EXPIRY "    \n", p->expiry);
  DEBUG("%" PRIu32 " " FLAG "      \n", p->flag);
  DEBUG("%" PRIu64 " " WHEN "      \n", p->when);
  DEBUG("%" PRIu64 " " RETAINTS "  \n", p->retaints);
  DEBUG("%" PRIu32 " " UFLAGS "    \n", p->uflags);
  DEBUG("%" PRIu16 " " STATUS "    \n", p->status);
  DEBUG("%" PRIu16 " " CHANNEL "   \n", p->channel);
  DEBUG("%" PRIu16 " " TYPE "      \n", p->type);
  DEBUG("%" PRIu8 "  " ORIGIN "    \n", p->origin);
  DEBUG("%" PRIu8 "  " SAVED "     \n", p->saved);
  DEBUG("%s " THUMBNAIL "          \n", p->thumbnail);
  DEBUG("%d " TNLEN "              \n", p->tnlen);
  DEBUG("%s " FILEPATH "           \n", p->filepath);
  DEBUG("%p " READ_SESSION "       \n\n", p->read_session);
}

void mesibo_py_log_param_bundle(tMessageBundle* m) {
  DEBUG("%" PRIu32 " " MSGLEN "    \n", m->msglen);
  DEBUG("%s " MESSAGE "            \n", m->message);
  DEBUG("%s title                  \n", m->title);
  DEBUG("%" PRIu32 " " FILESIZE "  \n", m->filesize);
  DEBUG("%" PRIu16 " " FILETYPE "  \n", m->filetype);
  DEBUG("%s " FILEURL "            \n", m->fileurl);
  DEBUG("%s " FILEPATH "           \n", m->filepath);
  DEBUG("%s " LAUNCHURL "          \n", m->launchurl);
  DEBUG("%" PRIu16 " " TNSLEN "    \n", m->tnslen);
  DEBUG("%" PRIu16 " " TNLEN "     \n", m->tnlen);
  DEBUG("%d " HAS_LOCATION "       \n", m->has_location);
  DEBUG("%" PRIu32 " " LAT "  %" PRIu32 " " LON " \n", m->lat, m->lon);
  DEBUG("%f lat  %f lon \n", m->lat_d, m->lon_d);
  DEBUG("%" PRIu64 " " LOCATION "  \n", m->location);
  DEBUG("%" PRIu64 " " RRID "      \n", m->rrid);
  DEBUG("%d " ACTIVITY " %d " HAS_ACTIVITY "\n", m->activity, m->has_activity);
}

PyObject* mesibo_py_get_callableclass(PyObject* py_class) {
  if (PyCallable_Check(py_class)) {
    PyObject* callable = PyObject_CallObject(py_class, NULL);
    return callable;
  }

  else {
    PyErr_Format(PyExc_RuntimeError, "%s call failed",
                 mesibo_py_get_string(PyObject_Repr(py_class)));
    return NULL;
  }
}
