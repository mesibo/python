// bind.cpp

#include <Python.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "core.h"
#include "docs.cpp"
#include "globals.h"
#include "structmember.h"

typedef struct {
  PyObject_HEAD 
  bool is_initialized;
  
} Mesibo;


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


static void Mesibo_dealloc(Mesibo *self) {
  Py_TYPE(self)->tp_free((PyObject *)self);
}


static PyObject *Mesibo_new(PyTypeObject *type, PyObject *args,
                            PyObject *kwds) {

  static Mesibo *self = NULL; /* static to create a Singleton */
  

  if(self) {

    Py_INCREF(self);
    return (PyObject *)self;
  }

  pthread_mutex_lock(&lock);
  
  if(self) {
    pthread_mutex_unlock(&lock);
    Py_INCREF(self);
    return (PyObject *)self; 
  }
  
  self = (Mesibo *)type->tp_alloc(type, 0);
  mesibo_py_init();
  self->is_initialized = true;
  Py_INCREF(self);

  pthread_mutex_unlock(&lock); 

  return (PyObject *)self;
}

static int Mesibo_init(Mesibo *self, PyObject *args, PyObject *kwds) {
  /*Custom Initialisation */

  return 0;
}

static PyMemberDef Mesibo_members[] = {
    {NULL} /* Sentinel */
};

static PyMethodDef Mesibo_methods[] = {

    {"answer", (PyCFunction)mesibo_py_answer, METH_VARARGS, answer__doc__},

    {"call", (PyCFunction)mesibo_py_call, METH_VARARGS, call__doc__},

    {"call_status", (PyCFunction)mesibo_py_callstatus_from_proxyrtc,
     METH_VARARGS, callStatus__doc__},

    {"cancel", (PyCFunction)mesibo_py_cancel, METH_VARARGS, cancel__doc__},

    {"count_key", (PyCFunction)mesibo_py_count_key, METH_VARARGS,
     countKey__doc__},

    {"delete_contact", (PyCFunction)mesibo_py_delete_contact, METH_VARARGS,
     deleteContact__doc__},

    {"delete_key", (PyCFunction)mesibo_py_delete_key, METH_VARARGS,
     deleteKey__doc__},

    {"delete_message", (PyCFunction)mesibo_py_delete_message, METH_VARARGS,
     deleteMessage__doc__},

    {"delete_messages", (PyCFunction)mesibo_py_delete_messages, METH_VARARGS,
     deleteMessages__doc__},

    {"delete_policy", (PyCFunction)mesibo_py_delete_policy, METH_VARARGS,
     deletePolicy__doc__},

    {"forward_message", (PyCFunction)mesibo_py_forward_message, METH_VARARGS,
     forwardMessage__doc__},

    {"free_keyvaluebuffer", (PyCFunction)mesibo_py_free_keyvaluebuffer,
     METH_VARARGS, freeKeyValueBuffer__doc__},

    {"hangup", (PyCFunction)mesibo_py_hangup, METH_VARARGS, hangup__doc__},
    {"hold", (PyCFunction)mesibo_py_hold, METH_VARARGS, hold__doc__},

    {"get_loginstatus", (PyCFunction)mesibo_py_get_loginstatus, METH_NOARGS,
     getLoginStatus__doc__},

    {"get_mapimage_url", (PyCFunction)mesibo_py_get_mapimage_url, METH_VARARGS,
     getMapimageUrl__doc__},

    {"get_uid", (PyCFunction)mesibo_py_get_uid, METH_NOARGS, getUid__doc__},

    {"message_send", (PyCFunction)mesibo_py_message_send, METH_NOARGS,
     messageSend__doc__},

    {"mute", (PyCFunction)mesibo_py_mute, METH_VARARGS, mute__doc__},

    {"get_mute_status", (PyCFunction)mesibo_py_mute_status, METH_NOARGS,
     muteStatus__doc__},

    {"phone_fqn", (PyCFunction)mesibo_py_phone_fqn, METH_VARARGS,
     phoneFqn__doc__},

    {"phone_strip", (PyCFunction)mesibo_py_phone_strip, METH_VARARGS,
     phoneStrip__doc__},

    {"random", (PyCFunction)mesibo_py_random32, METH_NOARGS, random__doc__},

    {"read", (PyCFunction)mesibo_py_read, METH_VARARGS, read__doc__},

    {"read_contact", (PyCFunction)mesibo_py_read_contact, METH_VARARGS,
     readContact__doc__},

    {"read_key", (PyCFunction)mesibo_py_read_key, METH_VARARGS, readKey__doc__},

    {"reconnect", (PyCFunction)mesibo_py_reconnect_now, METH_VARARGS,
     reconnect__doc__},

    {"resend", (PyCFunction)mesibo_py_resend_message, METH_VARARGS,
     resend__doc__},

    {"reset_database", (PyCFunction)mesibo_py_reset_database, METH_VARARGS,
     resetDatabase__doc__},

    {"send_activity", (PyCFunction)mesibo_py_send_activity, METH_VARARGS,
     sendActivity__doc__},

    {"send_message", (PyCFunction)mesibo_py_send_message, METH_VARARGS,
     sendMessage__doc__},

    {"send_file", (PyCFunction)mesibo_py_send_messagebundle, METH_VARARGS,
     sendFile__doc__},

    {"send_pending", (PyCFunction)mesibo_py_send_pending, METH_VARARGS,
     sendPending__doc__},

    {"send_readreceipt", (PyCFunction)mesibo_py_send_readreceipt, METH_VARARGS,
     sendReadReceipt__doc__},

    {"set_answer_mode", (PyCFunction)mesibo_py_set_answer_mode, METH_VARARGS,
     setAnswerMode__doc__},

    {"set_appstore", (PyCFunction)mesibo_py_set_appstore, METH_VARARGS,
     setAppstore__doc__},

    {"set_bufferlen", (PyCFunction)mesibo_py_set_bufferlen, METH_VARARGS,
     setBufferLen__doc__},

    {"set_callfactory", (PyCFunction)mesibo_py_set_callfactory, METH_VARARGS,
     setCallFactory__doc__},

    {"set_callprocessing", (PyCFunction)mesibo_py_set_callprocessing,
     METH_VARARGS, setCallProcessing__doc__},

    {"set_cpu", (PyCFunction)mesibo_py_set_cpu, METH_VARARGS, setCpu__doc__},

    {"set_accesstoken", (PyCFunction)mesibo_py_set_accesstoken,
     METH_VARARGS | METH_KEYWORDS, setAccessToken__doc__},

    {"set_database", (PyCFunction)mesibo_py_set_database, METH_VARARGS,
     setDatabase__doc__},

    {"set_debug", (PyCFunction)mesibo_py_set_debug, METH_VARARGS,
     setDebug__doc__},

    {"set_device", (PyCFunction)mesibo_py_set_device, METH_VARARGS,
     setDevice__doc__},

    {"set_key", (PyCFunction)mesibo_py_set_key, METH_VARARGS, setKey__doc__},

    {"set_network", (PyCFunction)mesibo_py_set_network, METH_VARARGS,
     setNetwork__doc__},

    {"set_notify", (PyCFunction)mesibo_py_set_notify, METH_VARARGS,
     setNotify__doc__},

    {"set_pstn", (PyCFunction)mesibo_py_set_pstn, METH_VARARGS, setPstn__doc__},
    {"set_readingsession", (PyCFunction)mesibo_py_set_readsession, METH_VARARGS,
     setReadingSession__doc__},

    {"set_secureconnection", (PyCFunction)mesibo_py_set_secure, METH_VARARGS,
     setSecureConnection__doc__},

    {"set_server", (PyCFunction)mesibo_py_set_server, METH_VARARGS,
     setServer__doc__},

    {"set_uniqid", (PyCFunction)mesibo_py_set_uniqid, METH_VARARGS,
     setUniqid__doc__},

    {"start", (PyCFunction)mesibo_py_start, METH_NOARGS, start__doc__},

    {"stop", (PyCFunction)mesibo_py_stop, METH_NOARGS, stop__doc__},

    {"timestamp", (PyCFunction)mesibo_py_timestamp, METH_NOARGS,
     timestamp__doc__},

    {"update_message", (PyCFunction)mesibo_py_update_message, METH_VARARGS,
     updateMessage__doc__},

    {"wait", (PyCFunction)mesibo_py_wait, METH_NOARGS, wait__doc__},

    {NULL, NULL, 0, NULL}

};

static PyMethodDef mesibo_methods[] = {
    {NULL} /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3
/* module initialization */
/* Python version 3 */

static PyTypeObject mesibo_MesiboType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "mesibo.Mesibo",
    .tp_basicsize = sizeof(Mesibo),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)Mesibo_dealloc,
    .tp_print = 0,
    .tp_getattr = 0,
    .tp_setattr = 0,
    .tp_as_async = 0,
    .tp_repr = 0,
    .tp_as_number = 0,
    .tp_as_sequence = 0,
    .tp_as_mapping = 0,

    .tp_hash = 0,
    .tp_call = 0,
    .tp_str = 0,
    .tp_getattro = 0,
    .tp_setattro = 0,

    .tp_as_buffer = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc =
        "Mesibo Class with Python bindings for mesibo C/C++ api.Documentation: "
        "https://mesibo.com/documentation/",

    .tp_traverse = 0,
    .tp_clear = 0,
    .tp_richcompare = 0,
    .tp_weaklistoffset = 0,

    .tp_iter = 0,
    .tp_iternext = 0,

    .tp_methods = Mesibo_methods,
    .tp_members = Mesibo_members,
    .tp_getset = 0,
    .tp_base = 0,
    .tp_dict = 0,
    .tp_descr_get = 0,
    .tp_descr_set = 0,
    .tp_dictoffset = 0,
    .tp_init = (initproc)Mesibo_init,
    .tp_alloc = 0,
    .tp_new = (newfunc)Mesibo_new,

};

static struct PyModuleDef mesibo = {PyModuleDef_HEAD_INIT, "mesibo",
                                    "Python bindings for mesibo C/C++ API ", -1,
                                    mesibo_methods};

PyMODINIT_FUNC PyInit_mesibo(void) {
  PyObject *m;

  if (PyType_Ready(&mesibo_MesiboType) < 0) return NULL;

  m = PyModule_Create(&mesibo);
  if (m == NULL) return NULL;

  Py_INCREF(&mesibo_MesiboType);
  PyModule_AddObject(m, "Mesibo", (PyObject *)&mesibo_MesiboType);
  return m;
}

#else
/* module initialization */
/* Python version 2 */

static PyTypeObject mesibo_MesiboType = {
    PyObject_HEAD_INIT(NULL) 0,               /*ob_size*/
    "mesibo.Mesibo",                          /*tp_name*/
    sizeof(Mesibo),                           /*tp_basicsize*/
    0,                                        /*tp_itemsize*/
    (destructor)Mesibo_dealloc,               /*tp_dealloc*/
    0,                                        /*tp_print*/
    0,                                        /*tp_getattr*/
    0,                                        /*tp_setattr*/
    0,                                        /*tp_compare*/
    0,                                        /*tp_repr*/
    0,                                        /*tp_as_number*/
    0,                                        /*tp_as_sequence*/
    0,                                        /*tp_as_mapping*/
    0,                                        /*tp_hash */
    0,                                        /*tp_call*/
    0,                                        /*tp_str*/
    0,                                        /*tp_getattro*/
    0,                                        /*tp_setattro*/
    0,                                        /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Mesibo Class with Python bindings for mesibo C/C++ api.Documentation: "
    "https://mesibo.com/documentation/",      /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    Mesibo_methods,                           /* tp_methods */
    Mesibo_members,                           /* tp_members */
    0,                                        /* tp_getset */
    0,                                        /* tp_base */
    0,                                        /* tp_dict */
    0,                                        /* tp_descr_get */
    0,                                        /* tp_descr_set */
    0,                                        /* tp_dictoffset */
    (initproc)Mesibo_init,                    /* tp_init */
    0,                                        /* tp_alloc */
    Mesibo_new,                               /* tp_new */

};

PyMODINIT_FUNC initmesibo(void) {
  PyObject *m;

  if (PyType_Ready(&mesibo_MesiboType) < 0) return;

  m = Py_InitModule3("mesibo", mesibo_methods,
                     "Python bindings for mesibo C/C++ API ");

  Py_INCREF(&mesibo_MesiboType);
  PyModule_AddObject(m, "Mesibo", (PyObject *)&mesibo_MesiboType);
}

#endif
