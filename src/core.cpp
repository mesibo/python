// api.cpp

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

#include "core.h"
#include <Python.h>
#include <mesibo.h>
#include "globals.h"
#include "notify.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

PyObject *PyNotifyClass;

void mesibo_py_init() {
  DEBUG("===>mesibo_init called\n");

  CNotify *n = new CNotify();
  m_api = query_mesibo("/tmp");
  n->set_api(m_api);
  m_api->set_notify(0, n, 1);
}

PyObject *mesibo_py_start(PyObject *self) {
  DEBUG("===>mesibo_start called\n");
  m_api->start();
  return Py_BuildValue("i", 1);
}

PyObject *mesibo_py_stop(PyObject *self) {
  DEBUG("===>mesibo_stop called\n");
  m_api->stop();
  return Py_BuildValue("i", 1);
}

PyObject *mesibo_py_reconnect_now(PyObject *self, PyObject *type_arg) {
  int type;
  if (!PyArg_ParseTuple(type_arg, "i", &type)) {
    PyErr_Format(PyExc_TypeError, "reconnect failed,Invalid arguments");
    return NULL;
  }

  DEBUG("===>mesibo_reconnect_now type:%d \n", type);
  m_api->reconnect_now(type);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_debug(PyObject *self, PyObject *debug_args) {
  DEBUG("===>mesibo_set_debug called \n");
  int loglevel;
  unsigned long debugflags;

  if (!PyArg_ParseTuple(debug_args, "ik", &loglevel, &debugflags)) {
    PyErr_Format(PyExc_TypeError, "set_debug failed,Invalid arguments ");
    return NULL;
  }

  DEBUG("loglevel: %d debugflags: %" PRIu32 "\n", loglevel,
        (uint32_t)debugflags);
  m_api->set_debug(loglevel, (uint32_t)debugflags);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_uniqid(PyObject *self, PyObject *uniqid_obj) {
  DEBUG("===>mesibo_set_uniqid called \n");
  unsigned long uniqid = 0;

  if (!PyArg_ParseTuple(uniqid_obj, "k", &uniqid)) {
    PyErr_Format(PyExc_TypeError, "set_uniqid failed,Invalid arguments");
    return NULL;
  }

  DEBUG("uniqid %ld \n", uniqid);
  DEBUG("uniqid %" PRIu32 " \n", (uint32_t)uniqid);

  m_api->set_uniqid((uint32_t)uniqid);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_device(PyObject *self, PyObject *app_id) {
  DEBUG("===>mesibo_set_device called\n");
  unsigned char type = 1;
  const char *deviceid = "MyDeviceId";
  const char *package;
  const char *version = "1.0.0";

  if (!PyArg_ParseTuple(app_id, "s", &package)) {
    PyErr_Format(PyExc_TypeError, "set_device failed,Invalid arguments");
    return NULL;
  }

  DEBUG(" type %d, deviceid %s, package %s, version %s \n\n", type, deviceid,
        package, version);

  int return_val = m_api->set_device((uint8_t)type, deviceid, package, version);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_cpu(PyObject *self, PyObject *cpu_args) {
  DEBUG("===>mesibo_set_cpu called \n");
  unsigned long long features;
  int family, count;

  if (!PyArg_ParseTuple(cpu_args, "iKi", &family, &features, &count)) {
    PyErr_Format(PyExc_TypeError, "set_cpu failed,Invalid arguments");
    return NULL;
  }

  DEBUG("family %d features %" PRIu64 " count %d \n", family,
        (uint64_t)features, count);
  m_api->set_cpu(family, (uint64_t)features, count);

  return Py_BuildValue("i", 0);
}

PyObject *mesibo_py_set_accesstoken(PyObject *self, PyObject *PyAppToken) {
  DEBUG("===>mesibo_set_accesstoken called\n");

  const char *cookie;
  if (!PyArg_ParseTuple(PyAppToken, "s", &cookie)) {
    PyErr_Format(PyExc_TypeError, "set_accesstoken failed,Invalid arguments");
    return NULL;
  }

  DEBUG("cookie %s \n", cookie);
  int return_val = m_api->set_credentials(cookie);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_notify(PyObject *self, PyObject *notify_class_ref) {
  DEBUG("===>mesibo_set_notify called \n");
  
  if (!PyArg_ParseTuple(notify_class_ref, "O", &PyNotifyClass)) {
    PyErr_Format(PyExc_TypeError, "set_notify failed,Invalid arguments");
    return NULL;
  }

  if (!PyCallable_Check(PyNotifyClass)) {
    PyErr_Format(PyExc_TypeError, "%s not callable",
                 mesibo_py_get_string(PyObject_Repr(PyNotifyClass)));
    return NULL;
  }

  PyNotifyClass = mesibo_py_get_callableclass(PyNotifyClass);
  if (!PyNotifyClass) {
    PyErr_Format(PyExc_TypeError, "%s not callable",
                 mesibo_py_get_string(PyObject_Repr(PyNotifyClass)));
    Py_DECREF(PyNotifyClass);
    return NULL;
  }

  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_appstore(PyObject *self, PyObject *appstore_args) {
  DEBUG("===>mesibo_set_appstore called \n");

  int storeid;
  const char *store;
  if (!PyArg_ParseTuple(appstore_args, "is", &storeid, &store)) {
    PyErr_Format(PyExc_RuntimeError, "set_appstore failed,Invalid arguments");
    return NULL;
  }

  DEBUG("storeid: %d ,store: %s\n", storeid, store);
  m_api->set_appstore(storeid, store);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_bufferlen(PyObject *self, PyObject *buffer_args) {
  DEBUG("===>mesibo_set_bufferlen called \n");
  int len, empty;

  if (!PyArg_ParseTuple(buffer_args, "ii", &len, &empty)) {
    PyErr_Format(PyExc_TypeError, "set_bufferlen failed,Invalid arguments");
    return NULL;
  }

  DEBUG("len %d ,empty %d \n", len, empty);
  int return_val = m_api->set_bufferlen(len, empty);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_network(PyObject *self, PyObject *network_args) {
  DEBUG("===>mesibo_set_network called");

  unsigned char type = 0;
  unsigned long ipaddr = 0;
  unsigned long gwaddr = 0;
  unsigned short lastport = 0;
  if (!PyArg_ParseTuple(network_args, "bkkH", &type, &ipaddr, &gwaddr,
                        &lastport)) {
    PyErr_Format(PyExc_TypeError, "set_network failed,Invalid arguments");
    return NULL;
  }

  DEBUG("type %" PRIu8 " ,ipaddr %" PRIu32 " ,gwaddr %" PRIu32
        " ,lastport %" PRIu16 "",
        (uint8_t)type, (uint32_t)ipaddr, (uint32_t)gwaddr, (uint16_t)lastport);
  int return_val = m_api->set_network((uint8_t)type, (uint32_t)ipaddr,
                                      (uint32_t)gwaddr, (uint16_t)lastport);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_send_message(PyObject *self, PyObject *message_args) {
  DEBUG("===>mesibo_send_message called \n\n");

  PyObject *p_dict_obj;
  const char *to;
  const char *data = "";
  int len = 0;

  unsigned long long msg_id ;
  PyObject *data_obj;
  char * string_data;

  /* the O! parses for a Python object (DictObj) checked
 to be of type PyDict_Type --dictionary*/

  if (!PyArg_ParseTuple(message_args, "O!KO", &PyDict_Type, &p_dict_obj, &msg_id, 
                        &data_obj)) {
    PyErr_Format(PyExc_TypeError, "send_message failed,Invalid arguments");
    Py_DECREF(p_dict_obj);
    return NULL;
  }

  //Overloaded functions for bytes,string and integer
  #if PY_MAJOR_VERSION >= 3 //For Python3
  if(PyBytes_Check(data_obj)){
      data = PyBytes_AsString(data_obj);
      DEBUG("%s Bytes data \n", data);
      len = PyBytes_Size(data_obj) + 1;
    }

  else if(PyLong_Check(data_obj)){
      sprintf(string_data, "%llu", PyLong_AsUnsignedLongLong(data_obj));
      data = (const char * )string_data;
      len = strlen(data);
    }

  else {
      data = mesibo_py_get_string(data_obj);
      len = strlen(data);

    }

  

  #else     //For Python 2
  if(PyLong_Check(data_obj)){
      sprintf(string_data, "%llu", PyLong_AsUnsignedLongLong(data_obj));
      data = (const char * )string_data;
    }
  else if(PyString_Check(data_obj))
      data = mesibo_py_get_string(data_obj);
  
  len = strlen(data);
  #endif


  tMessageParams p = {};
  mesibo_py_get_param_messagedict(p_dict_obj, &p);
  p.id = (uint64_t)msg_id;
  mesibo_py_log_param_message(&p);
  
  to = mesibo_py_get_param_string(p_dict_obj, PEER);

  DEBUG("\n\n %s  to \n", to);
  DEBUG("%s data \n", data);
  DEBUG("%d len \n", len);

  int return_val = 0;
  m_api->message(&p, to, data, len);

  Py_DECREF(p_dict_obj);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_message_send(PyObject *self) {
  DEBUG("===> message_send called \n");
  int return_val = 0;
  return_val = m_api->message_send();
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_cancel(PyObject *self, PyObject *cancel_args) {
  DEBUG("===>mesibo_cancel called\n");
  int type;
  unsigned long id;

  if (!PyArg_ParseTuple(cancel_args, "ik", &type, &id)) {
    PyErr_Format(PyExc_TypeError, "cancel failed,Invalid arguments");
    return NULL;
  }

  DEBUG("type %d id %" PRIu32 " ", type, (uint32_t)id);
  int return_val = m_api->cancel(type, (uint32_t)id);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_random32(PyObject *self) {
  uint32_t random_val = m_api->random32();

  return PyLong_FromUnsignedLong(random_val);
}

PyObject *mesibo_py_timestamp(PyObject *self) {
  uint64_t time_val = m_api->timestamp();
  DEBUG("TS %" PRIu64 " \n", time_val);

  return PyLong_FromUnsignedLongLong(time_val);
}

PyObject *mesibo_py_set_secure(PyObject *self, PyObject *secure_obj) {
  DEBUG("===>mesibo_set_secure called \n");
  int secure;

  if (!PyArg_ParseTuple(secure_obj, "i", &secure)) {
    PyErr_Format(PyExc_RuntimeError, "set_secure failed,Invalid arguments");
    return NULL;
  }

  DEBUG("secure:%d \n", secure);
  m_api->set_secure(secure);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_server(PyObject *self, PyObject *server_obj) {
  DEBUG("===>mesibo_set_server called \n");
  const char *server;
  if (!PyArg_ParseTuple(server_obj, "s", &server)) {
    PyErr_Format(PyExc_TypeError, "set_server failed,Invalid arguments");
    return NULL;
  }
  DEBUG("server: %s", server);
  int return_val = -1;
  return_val = m_api->set_server(server);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_database(PyObject *self, PyObject *PyDbName) {
  DEBUG("===>mesibo_set_database called\n");
  const char *db_path;
  if (!PyArg_ParseTuple(PyDbName, "s", &db_path)) {
    PyErr_Format(PyExc_TypeError, "set_database failed,Invalid arguments");
    return NULL;
  }

  DEBUG("dbfile  %s \n", db_path);
  int return_val = m_api->set_database(db_path);
  if (0 != return_val) PyErr_Format(PyExc_RuntimeError, "database failed");

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_reset_database(PyObject *self, PyObject *tables_obj) {
  DEBUG("===>mesibo_reset_database called \n");
  unsigned long tables;

  if (!PyArg_ParseTuple(tables_obj, "k", &tables)) {
    PyErr_Format(PyExc_TypeError, "reset_database failed,Invalid arguments");
    return NULL;
  }

  DEBUG("tables: %" PRIu32 " \n", (uint32_t)tables);
  int return_val = m_api->reset_database((uint32_t)tables);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_readsession(PyObject *self, PyObject *session_args) {
  DEBUG("===>mesibo_set_readsession called\n");

  void *data;
  unsigned long flag;
  const char *from;
  unsigned long groupid;
  const char *searchquery;

  PyObject *data_obj;

  if (!PyArg_ParseTuple(session_args, "Oksks", &data_obj, &flag, &from,
                        &groupid, &searchquery)) {
    PyErr_Format(PyExc_TypeError, "set_reading_session failed,Invalid arguments");
    Py_DECREF(data_obj);
    return NULL;
  }

  if (PyLong_AsUnsignedLongLong(data_obj) != 0) {
    data = PyLong_AsVoidPtr(data_obj);
  } else
    data = NULL;

  DEBUG("data %p ,flag %" PRIu32 ",from %s ,groupid %" PRIu32
        ",searchquery %s \n",
        data, (uint32_t)flag, from, (uint32_t)groupid, searchquery);

  void *return_val;
  return_val = m_api->set_readsession(data, (uint32_t)flag, from,
                                      (uint32_t)groupid, searchquery);

  return PyLong_FromVoidPtr(return_val);
}

PyObject *mesibo_py_read(PyObject *self, PyObject *session_args) {
  DEBUG("===>mesibo_read called \n");
  void *rs;
  int count;
  PyObject *rs_obj;

  if (!PyArg_ParseTuple(session_args, "Oi", &rs_obj, &count)) {
    PyErr_Format(PyExc_TypeError, "read failed,Invalid arguments");
    Py_DECREF(rs_obj);
    return NULL;
  }

  rs = PyLong_AsVoidPtr(rs_obj);
  if (PyErr_Occurred() && rs == NULL) {
    PyErr_Format(PyExc_RuntimeError, "Invalid PyLong pointer value");
    return NULL;
  }

  DEBUG("read rs: %p,count: %d \n", rs, count);

  int return_val;
  return_val = m_api->read(rs, count);
  DEBUG("%d read returned \n", return_val);

  Py_DECREF(rs_obj);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_delete_messages(PyObject *self, PyObject *msg_args) {
  DEBUG("===>mesibo_delete_messages called \n");
  uint64_t *ids;
  int count;
  int del_type;

  PyObject *idlist_obj;

  if (!PyArg_ParseTuple(msg_args, "O!ii", &PyList_Type, &idlist_obj, &count,
                        &del_type)) {
    PyErr_Format(PyExc_TypeError, "delete_messages failed,Invalid arguments");
    return NULL;
  }

  DEBUG("count: %d del_type:%d \n", count, del_type);
  DEBUG("%zd listsize \n", PyList_Size(idlist_obj));
  ids = (uint64_t *)malloc(sizeof(uint64_t) * PyList_Size(idlist_obj));

  for (int i = 0; i < count; i++) {
    ids[i] = PyLong_AsUnsignedLongLong(PyList_GetItem(idlist_obj, i));
    DEBUG("id: %" PRIu64 "", ids[i]);
  }

  int return_val = m_api->delete_messages(ids, count, del_type);

  free(ids);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_delete_message(PyObject *self, PyObject *msg_args) {
  DEBUG("===>mesibo_delete_message called \n");
  unsigned long long id;
  const char *from;
  unsigned long groupid;
  unsigned long long ts;

  if (!PyArg_ParseTuple(msg_args, "KskK", &id, &from, &groupid, &ts)) {
    PyErr_Format(PyExc_TypeError, "delete_message failed,Invalid arguments");
    return NULL;
  }

  DEBUG("mid: %" PRIu64 ", from:%s, groupid: %" PRIu32 ", ts: %" PRIu64 " \n",
        (uint64_t)id, from, (uint16_t)groupid, (uint64_t)ts);
  int return_val = m_api->delete_messages((uint64_t)id, from, (uint32_t)groupid,
                                          (uint64_t)ts);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_delete_policy(PyObject *self, PyObject *policy_args) {
  DEBUG("===>mesibo_delete_policy called \n");
  int max_interval = 0;
  int delete_type = 0;

  if (!PyArg_ParseTuple(policy_args, "ii", &max_interval, &delete_type)) {
    PyErr_Format(PyExc_TypeError, "delete_policy failed,Invalid arguments");
    return NULL;
  }

  DEBUG("max_interval: %d ,delete_type: %d", max_interval, delete_type);
  int return_val = 0;
  return_val = m_api->delete_policy(max_interval, delete_type);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_key(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo_set_key called \n");
  const char *key;
  const char *value;

  if (!PyArg_ParseTuple(args, "ss", &key, &value)) {
    PyErr_Format(PyExc_TypeError, "set_key failed,Invalid arguments");
    return NULL;
  }

  DEBUG("key: %s , value %s \n", key, value);
  int return_val = m_api->set_key(key, value);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_delete_key(PyObject *self, PyObject *key_arg) {
  DEBUG("===>mesibo_delete_key called \n");
  const char *key;
  if (!PyArg_ParseTuple(key_arg, "s", &key)) {
    PyErr_Format(PyExc_TypeError, "delete_key failed,Invalid arguments");
    return NULL;
  }

  DEBUG("key: %s \n", key);
  int return_val = m_api->delete_key(key);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_read_key(PyObject *self, PyObject *key_arg) {
  DEBUG("===>mesibo_read_key called \n");
  const char *key;

  if (!PyArg_ParseTuple(key_arg, "s", &key)) {
    PyErr_Format(PyExc_TypeError, "read_key failed,Invalid arguments");
    return NULL;
  }

  char **value = (char **)malloc(sizeof(char *));
  m_api->read_key(key, value);

  PyObject *value_py_str = Py_BuildValue("s", value[0]);
  free(value);
  return value_py_str;
}

PyObject *mesibo_py_free_keyvaluebuffer(PyObject *self, PyObject *value_obj) {
  DEBUG("===>mesibo_free_keyvaluebuffer called \n");
  char *value;
  if (!PyArg_ParseTuple(value_obj, "s", &value)) {
    PyErr_Format(PyExc_TypeError,
                 "free_keyvaluebuffer failed,Invalid arguments");
    return NULL;
  }

  DEBUG("value: %s \n", value);
  m_api->free_keyvaluebuffer(value);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_count_key(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo_count_key called \n");
  const char *key = "";
  const char *value = "";

  if (!PyArg_ParseTuple(args, "s", &key, &value)) {
    PyErr_Format(PyExc_TypeError, "count_key failed,Invalid arguments");
    return NULL;
  }

  DEBUG("key: %s ,value: %s", key, value);
  int return_val = m_api->count_key(key, value);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_read_contact(PyObject *self, PyObject *contact_args) {
  DEBUG("===>mesibo_read_contact called");

  const char *address = "";
  unsigned long groupid;
  const char *orderby = "";
  int count = 0;

  if (!PyArg_ParseTuple(contact_args, "sksi", &address, &groupid, orderby,
                        count)) {
    PyErr_Format(PyExc_TypeError, "read_contact failed,Invalid arguments");
    return NULL;
  }

  DEBUG("address: %s ,groupid: %" PRIu32 ", orderby: %s , count: %d \n",
        address, (uint32_t)groupid, orderby, count);
  int return_val =
      m_api->read_contact(address, (uint32_t)groupid, orderby, count);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_delete_contact(PyObject *self, PyObject *contact_args) {
  DEBUG("===>mesibo_delete_contact called \n");
  const char *address = "";
  unsigned long groupid;

  if (!PyArg_ParseTuple(contact_args, "sk", &address, &groupid)) {
    PyErr_Format(PyExc_TypeError, "delete_contact failed,Invalid arguments");
    Py_DECREF(address);
    return NULL;
  }

  DEBUG("address: %s ,groupid: %" PRIu32 " \n", address, (uint32_t)groupid);
  int return_val = m_api->delete_contact(address, (uint32_t)groupid);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_get_loginstatus(PyObject *self) {
  int return_val = m_api->get_loginstatus();
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_get_mapimage_url(PyObject *self, PyObject *mapimage_args) {
  DEBUG("===>mesibo_get_mapimage_url called \n");
  float lat, lon;
  int width, zoom;
  char *url;

  if (!PyArg_ParseTuple(mapimage_args, "ffiis", &lat, &lon, &width, &zoom,
                        &url)) {
    PyErr_Format(PyExc_TypeError, "get_mapimage_url failed,Invalid arguments");
    return NULL;
  }

  DEBUG("lat: %f, lon:%f, width:%d, zoom:%d ,url:%s \n", lat, lon, width, zoom,
        url);
  int return_val = m_api->get_mapimage_url(lat, lon, width, zoom, url);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_phone_fqn(PyObject *self, PyObject *fqn_args) {
  DEBUG("===>mesibo_phone_fqn called \n");
  const char *phone;
  int country_code;
  int mcc;
  char *fqn;

  if (!PyArg_ParseTuple(fqn_args, "siis", &phone, &country_code, &mcc, &fqn)) {
    PyErr_Format(PyExc_TypeError, "phone_fqn failed, Invalid arguments");
    return NULL;
  }

  DEBUG("phone: %s ,country_code: %d, mcc: %d,fqn:%s", phone, country_code, mcc,
        fqn);
  m_api->phone_fqn(phone, country_code, mcc, fqn);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_phone_strip(PyObject *self, PyObject *strip_args) {
  DEBUG("mesibo_phone_strip called \n");
  const char *phone;
  int strip_prefix;
  char *fqn;

  if (!PyArg_ParseTuple(strip_args, "sis", &phone, &strip_prefix, &fqn)) {
    PyErr_Format(PyExc_TypeError, "phone_strip failed, Invalid arguments");
    return NULL;
  }

  DEBUG("phone: %s, strip_prefix: %d,fqn:%s \n", phone, strip_prefix, fqn);
  m_api->phone_strip(phone, strip_prefix, fqn);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_send_readreceipt(PyObject *self, PyObject *receipt_args) {
  DEBUG("mesibo_send_readreceipt called \n");
  int type = 0;
  const char *to = "";
  unsigned long groupid = 0;
  unsigned long long readid = 0;

  if (!PyArg_ParseTuple(receipt_args, "iskK", &type, &to, &groupid, &readid)) {
    PyErr_Format(PyExc_TypeError, "send_readreceipt failed,Invalid arguments");
    return NULL;
  }

  DEBUG("type: %d, to: %s, groupid: %" PRIu32 ",readid: %" PRIu64 "", type, to,
        (uint32_t)groupid, (uint64_t)readid);
  int return_val =
      m_api->send_readreceipt(type, to, (uint32_t)groupid, (uint64_t)readid);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_send_activity(PyObject *self, PyObject *activity_args) {
  DEBUG("mesibo_send_activity called \n");
  tMessageParams p = {};
  const char *to = "";
  unsigned long activity = 0;
  unsigned long interval = 0;

  PyObject *p_dict_obj;

  if (!PyArg_ParseTuple(activity_args, "O!skk", &PyDict_Type, &p_dict_obj, &to,
                        &activity, &interval)) {
    PyErr_Format(PyExc_TypeError, "send_activity failed,Invalid arguments");
    Py_DECREF(p_dict_obj);
    return NULL;
  }

  mesibo_py_get_param_messagedict(p_dict_obj, &p);
  mesibo_py_log_param_message(&p);

  DEBUG("%" PRIu32 " \n", (uint32_t)activity);
  DEBUG("%" PRIu32 " len \n", (uint32_t)interval);

  int return_val = m_api->send_activity(&p, to, activity, interval);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_send_messagebundle(PyObject *self, PyObject *bundle_args) {
  DEBUG("===>mesibo_send_messagebundle called \n");
  tMessageParams p = {};
  const char *to;
  tMessageBundle m = {};

  PyObject *p_dict_obj;
  PyObject *m_dict_obj;

  if (!PyArg_ParseTuple(bundle_args, "O!sO!", &PyDict_Type, &p_dict_obj, &to,
                        &PyDict_Type, &m_dict_obj)) {
    PyErr_Format(PyExc_TypeError, "send_file failed,Invalid arguments");
    Py_DECREF(p_dict_obj);
    Py_DECREF(m_dict_obj);
    return NULL;
  }

  mesibo_py_get_param_messagedict(p_dict_obj, &p);
  mesibo_py_log_param_message(&p);

  DEBUG("%s  to \n", to);

  mesibo_py_get_param_bundledict(m_dict_obj, &m);
  mesibo_py_log_param_bundle(&m);

  int return_val = m_api->send_messagebundle(&p, to, &m);

  Py_DECREF(p_dict_obj);
  Py_DECREF(m_dict_obj);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_forward_message(PyObject *self, PyObject *message_args) {
  DEBUG("===>mesibo_forward_message called \n");
  tMessageParams p = {};
  const char *to;
  unsigned long long id;

  PyObject *p_dict_obj;

  if (!PyArg_ParseTuple(message_args, "O!sK", &PyDict_Type, &p_dict_obj, &to,
                        &id)) {
    PyErr_Format(PyExc_TypeError, "forward_message failed,Invalid arguments");
    Py_DECREF(p_dict_obj);
    return NULL;
  }

  mesibo_py_get_param_messagedict(p_dict_obj, &p);
  mesibo_py_log_param_message(&p);

  int return_val = m_api->forward_message(&p, to, id);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_update_message(PyObject *self, PyObject *message_args) {
  DEBUG("===>mesibo_update_message called \n ");
  uint64_t id;
  int flag;
  int status;
  const char *thumbnail;
  int tnlen;
  const char *filepath;

  if (!PyArg_ParseTuple(message_args, "Kiisis", &id, &flag, &status, &thumbnail,
                        &tnlen, &filepath)) {
    PyErr_Format(PyExc_TypeError, "update_message failed,Invalid arguments");
    return NULL;
  }

  DEBUG("id: %" PRIu64
        ",flag:%d,status:%d,thumbnail:%s,tnlen:%d,filepath:%s \n",
        id, flag, status, thumbnail, tnlen, filepath);

  int return_val =
      m_api->update_message(id, flag, status, thumbnail, tnlen, filepath);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_send_pending(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo_send_pending called \n");
  unsigned long id;
  int flag;

  if (!PyArg_ParseTuple(args, "ki", &id, &flag)) {
    PyErr_Format(PyExc_TypeError, "send_pending failed,Invalid arguments");
    return NULL;
  }

  DEBUG("id: %" PRIu32 ",flag: %d \n", (uint32_t)id, flag);
  int return_val = m_api->send_pending((uint32_t)id, flag);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_resend_message(PyObject *self, PyObject *id_arg) {
  DEBUG("mesibo_resend_message called \n");
  unsigned long id = 0;

  if (!PyArg_ParseTuple(id_arg, "k", &id)) {
    PyErr_Format(PyExc_TypeError, "resend_message failed, Invalid arguments");
    return NULL;
  }

  DEBUG("id: %" PRIu32 "\n", (uint32_t)id);
  int return_val = m_api->resend_message((uint32_t)id);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_call(PyObject *self, PyObject *args) {
  DEBUG("==>mesibo call \n");
  const char *destination;
  int type = 0;

  if (!PyArg_ParseTuple(args, "si", &destination, &type)) {
    PyErr_Format(PyExc_TypeError, "call failed,Invalid arguments");
    return NULL;
  }

  DEBUG("destination: %s\n", destination);
  int return_val = m_api->call(destination, type);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_answer(PyObject *self, PyObject *video_arg) {
  DEBUG("==>mesibo answer called \n ");
  int video = 0;

  if (!PyArg_ParseTuple(video_arg, "i", &video)) {
    PyErr_Format(PyExc_TypeError, "answer failed,Invalid arguments");
  }

  DEBUG("video:%d \n", video);
  int return_val = m_api->answer(video);

  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_hangup(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo hangup called \n");

  unsigned long callid;
  int status;

  if (!PyArg_ParseTuple(args, "ki", &callid, &status)) {
    PyErr_Format(PyExc_TypeError, "hangup failed,Invalid arguments");
    return NULL;
  }

  DEBUG("callid: %" PRIu32 ",status: %d \n", (uint32_t)callid, status);
  int return_val = m_api->hangup((uint32_t)callid, status);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_mute(PyObject *self, PyObject *args) {
  DEBUG("===>mute called \n");
  int audio;
  int video;
  int enable;

  if (!PyArg_ParseTuple(args, "iii", &audio, &video, &enable)) {
    PyErr_Format(PyExc_TypeError, "mute failed,Invalid arguments");
    return NULL;
  }

  DEBUG("audio:%d,video:%d,enable:%d \n", audio, video, enable);
  int return_val = m_api->mute(audio, video, enable);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_hold(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo hold called  \n");
  int enable;
  if (!PyArg_ParseTuple(args, "i", &enable)) {
    PyErr_Format(PyExc_TypeError, "hold failed,Invalid arguments");
    return NULL;
  }

  DEBUG("enable: %d", enable);
  int return_val = m_api->hold(enable);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_pstn(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo set_pstn called \n");
  const char *server;
  int port;

  if (!PyArg_ParseTuple(args, "si", &server, &port)) {
    PyErr_Format(PyExc_TypeError, "set_pstn failed,Invalid arguments");
    return NULL;
  }

  DEBUG("server: %s, port:%d \n", server, port);
  int return_val = m_api->set_pstn(server, port);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_set_callprocessing(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo set_callprocessing called \n");
  int call_reject_status;
  int current_call_status;

  if (!PyArg_ParseTuple(args, "ii", &call_reject_status,
                        &current_call_status)) {
    PyErr_Format(PyExc_TypeError, "set_callprocessing failed,Invalid arguments");
    return NULL;
  }

  DEBUG("call_reject_status:%d ,current_call_status:%d \n", call_reject_status,
        current_call_status);
  m_api->set_callprocessing(call_reject_status, current_call_status);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_set_answer_mode(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo_set_answermode called \n");
  int lateconnect;

  if (!PyArg_ParseTuple(args, "i", &lateconnect)) {
    PyErr_Format(PyExc_TypeError, "set_answer_mode failed,Invalid arguments");
    return NULL;
  }

  DEBUG("lateconnect:%d \n", lateconnect);
  m_api->set_answer_mode(lateconnect);
  Py_RETURN_NONE;
}

PyObject *mesibo_py_mute_status(PyObject *self) {
  return Py_BuildValue("i", m_api->mute_status());
}

PyObject *mesibo_py_set_callfactory(PyObject *self, PyObject *args) {
  DEBUG("===>set_callfactory called \n");
  int type;
  void *factory;
  PyObject *factory_obj;
  if (!PyArg_ParseTuple(args, "iO", &type, &factory_obj)) {
    PyErr_Format(PyExc_TypeError, "set_callfactory failed,Invalid arguments");
    return NULL;
  }

  factory = PyLong_AsVoidPtr(factory_obj);

  DEBUG("type: %d,factory: %p \n", type, factory);
  m_api->set_callfactory(type, factory);

  Py_RETURN_NONE;
}

PyObject *mesibo_py_callstatus_from_proxyrtc(PyObject *self, PyObject *args) {
  DEBUG("===>mesibo_callstatus_from_proxyrtc called \n");
  int status;
  const char *sdp;
  int sdplen;

  if (!PyArg_ParseTuple(args, "isi", &status, &sdp, &sdplen)) {
    PyErr_Format(PyExc_TypeError, "call_status failed,Invalid arguments");
    return NULL;
  }

  DEBUG("status:%d,sdp:%s,sdplen:%d \n", status, sdp, sdplen);
  int return_val = m_api->callstatus_from_proxyrtc(status, sdp, sdplen);
  return Py_BuildValue("i", return_val);
}

PyObject *mesibo_py_get_uid(PyObject *self) {
  return PyLong_FromUnsignedLong(m_api->get_uid());
}

