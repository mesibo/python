// notify.cpp

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


#define MESIBO_LISTENER_ON_MESSAGE "on_message"
#define MESIBO_LISTENER_ON_MESSAGE_BUNDLE "on_file"
#define MESIBO_LISTENER_ON_MESSAGE_STATUS "on_messagestatus"
#define MESIBO_LISTENER_ON_STATUS "on_status"
#define MESIBO_LISTENER_ON_ERROR "on_error"
#define MESIBO_LISTENER_ON_ACTIVITY "on_activity"
#define MESIBO_LISTENER_ON_CALL "on_call"
#define MESIBO_LISTENER_ON_KEY "on_key"
#define MESIBO_LISTENER_ON_CONTACT "on_contact"
#define MESIBO_LISTENER_ON_RTC "on_rtc"
#define MESIBO_LISTENER_ON_SERVER "on_server"

#include "notify.h"
#include <Python.h>
#include <assert.h>
#include <mesibo.h>
#include "globals.h"
#include "utils.h"

void CNotify::set_api(IMesibo *api) { m_api = api; }

int CNotify::on_message(tMessageParams *p, const char *from, const char *data,
                        uint32_t len) {
  int printlen = len;
  if (printlen > 64) printlen = 64;
  DEBUG(
      "===> test app message received: uid %u status %d channel %d type "
      "%u id "
      "%" PRIx64 " refid %lu groupid %u, when %" PRIu64
      " from %s, flag: %x len %d: %.*s\n",
      p->uid, p->status, p->channel, p->type, p->id, p->refid, p->groupid,
      p->when, from, p->flag, len, printlen, data);

  DEBUG("==> with message parameters\n");

  mesibo_py_log_param_message(p);
  PyObject *tMessageParams_dict_obj = PyDict_New();
  mesibo_py_build_param_messagedict(tMessageParams_dict_obj, p);

  PyObject *data_bytes_obj;
#if PY_MAJOR_VERSION >= 3
  data_bytes_obj = Py_BuildValue("y", data);
#else
  data_bytes_obj = Py_BuildValue("s#", data, len);

#endif
  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_MESSAGE, "OsOk",
                          tMessageParams_dict_obj, from, data_bytes_obj, len);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);

  DEBUG("" MESIBO_LISTENER_ON_MESSAGE " returned %d  \n", status_val);

  Py_DECREF(py_return_status);
  Py_DECREF(tMessageParams_dict_obj);
  Py_DECREF(data_bytes_obj);

  return status_val;
}

int CNotify::on_messagebundle(tMessageParams *p, const char *from,
                              tMessageBundle *m) {
  DEBUG("===> test app bundle received: channel %d type %u id %" PRIx64
        " refid %lu groupid %u, when %" PRIu64
        " from %s, flag: %x status: %d\n",
        p->channel, p->type, p->id, p->refid, p->groupid, p->when, from,
        p->flag, p->status);

  DEBUG(
      "Bundle: message %s len %u title %s filetype %u filesize %u "
      "filepath %s fileurl %s launchurl %s lat %f lon %f\n",
      m->message, m->msglen, m->title, m->filetype, m->filesize, m->filepath,
      m->fileurl, m->launchurl, m->lat_d, m->lon_d);

  mesibo_py_log_param_message(p);
  PyObject *tMessageParams_dict_obj = PyDict_New();
  mesibo_py_build_param_messagedict(tMessageParams_dict_obj, p);

  mesibo_py_log_param_bundle(m);
  PyObject *tMessageBundle_dict_obj = PyDict_New();
  mesibo_py_build_param_bundledict(tMessageBundle_dict_obj, m);

  PyObject *py_return_status = PyObject_CallMethod(
      PyNotifyClass, MESIBO_LISTENER_ON_MESSAGE_BUNDLE, "OsO",
      tMessageParams_dict_obj, from, tMessageBundle_dict_obj);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG("" MESIBO_LISTENER_ON_MESSAGE_BUNDLE " returned:%d \n", status_val);

  Py_DECREF(py_return_status);

  return status_val;
}

int CNotify::on_messagestatus(tMessageParams *p, const char *from, int last) {
  DEBUG("===> on_messagestatus status %u id %u when %u ms (%u %u) from: %s\n",
        p->status, p->id, m_api->timestamp() - p->when, m_api->timestamp(),
        p->when, from ? from : "");

  DEBUG("==> with message parameters\n");
  mesibo_py_log_param_message(p);
  DEBUG("with parameters from: %s last:%d \n", from, last);

  PyObject *tMessageParams_dict_obj = PyDict_New();
  mesibo_py_build_param_messagedict(tMessageParams_dict_obj, p);

  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_MESSAGE_STATUS,
                          "Osi", tMessageParams_dict_obj, from, last);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG(" " MESIBO_LISTENER_ON_MESSAGE_STATUS " returned : %d  \n", status_val);

  Py_DECREF(py_return_status);
  Py_DECREF(tMessageParams_dict_obj);

  return status_val;
}

int CNotify::on_status(int status, uint32_t substatus, uint8_t channel,
                       const char *from) {
  DEBUG("===> on_status: %u %u\n", status, substatus);

  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_STATUS, "ikBs",
                          status, substatus, channel, from);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG(" " MESIBO_LISTENER_ON_STATUS " returned:%d \n", status_val);
  Py_DECREF(py_return_status);

  return status_val;
}

int CNotify::on_error(uint8_t error) {
  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_ERROR, "B",
                          PyLong_FromUnsignedLong(error));

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);

  DEBUG(" " MESIBO_LISTENER_ON_ERROR ":%d \n", status_val);
  Py_DECREF(py_return_status);

  return status_val;
}

int CNotify::on_activity(tMessageParams *p, const char *from, uint32_t event) {
  DEBUG("===> on_activity: %x\n", event);

  mesibo_py_log_param_message(p);
  DEBUG("with parameters from: %s event: %" PRIu32 " \n", from, event);

  PyObject *tMessageParams_dict_obj = PyDict_New();

  mesibo_py_build_param_messagedict(tMessageParams_dict_obj, p);

  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_ACTIVITY, "Osk",
                          tMessageParams_dict_obj, from, event);
  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);

  DEBUG(" " MESIBO_LISTENER_ON_ACTIVITY " returned:%d \n", status_val);

  Py_DECREF(tMessageParams_dict_obj);
  Py_DECREF(py_return_status);

  return status_val;
}

int CNotify::on_call(uint32_t peerid, uint32_t callid, int status,
                     const char *data, int datalen, uint64_t flags) {
  DEBUG("===> on_call: %s status 0x%x flags 0x%x\n", data, status, flags);

  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_CALL, "kkisiK",
                          peerid, callid, status, data, datalen, flags);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG("" MESIBO_LISTENER_ON_CALL " returned %d", status_val);

  Py_DECREF(py_return_status);
  return status_val;
}

int CNotify::on_key(const char *key, const char *value) {
  DEBUG("===> on_key: %s %s\n", key, value);

  PyObject *py_return_status = PyObject_CallMethod(
      PyNotifyClass, MESIBO_LISTENER_ON_KEY, "ss", key, value);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG("" MESIBO_LISTENER_ON_KEY " returned %d", status_val);

  Py_DECREF(py_return_status);
  return status_val;
}

int CNotify::on_contact(const tContact *c) {
  DEBUG("===> on_contacts: (%s) (%s) (%u) (%s) (%s) (%s) (%" PRIu64
        ") (%" PRIu64 ") (%u) \n",
        c->name, c->address, c->groupid, c->status, c->photo, c->tn, c->ts,
        c->lastseen, c->flag);
  return 0;
}

int CNotify::on_rtc(int type, uint32_t flags, uint32_t peerid, const char *sdp,
                    int len) {
  return 0;

  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_RTC, "ikksi", type,
                          flags, peerid, sdp, len);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG(" " MESIBO_LISTENER_ON_RTC " returned %d", status_val);

  Py_DECREF(py_return_status);
  return status_val;
}

int CNotify::on_server(int type, const char *server, const char *username,
                       const char *password) {
  DEBUG("===> on_server: type %d server (%s)\n", type, server ? server : "");

  PyObject *py_return_status =
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_SERVER, "isss",
                          type, server, username, password);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG(" " MESIBO_LISTENER_ON_SERVER " returned %d", status_val);
  Py_DECREF(py_return_status);
  return status_val;
}
