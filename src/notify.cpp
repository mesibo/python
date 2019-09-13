// notify.cpp

#define MESIBO_LISTENER_ON_MESSAGE "on_message"
#define MESIBO_LISTENER_ON_MESSAGE_BUNDLE "on_file"
#define MESIBO_LISTENER_ON_MESSAGE_STATUS "on_messagestatus"
#define MESIBO_LISTENER_ON_STATUS "on_connectionstatus"
#define MESIBO_LISTENER_ON_ACTIVITY "on_activity"
#define MESIBO_LISTENER_ON_LOCATION "on_location"

#include "notify.h"
#include <inttypes.h>
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
  data_bytes_obj = Py_BuildValue("y", data); //Python bytes object
#else
  data_bytes_obj = Py_BuildValue("s#", data, len); // Python string buffer object

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
                          "Os", tMessageParams_dict_obj, from);

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
      PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_STATUS, "i",
                          status);

  int status_val = 0;
  status_val = PyLong_AsLong(py_return_status);
  DEBUG(" " MESIBO_LISTENER_ON_STATUS " returned:%d \n", status_val);
  Py_DECREF(py_return_status);

  return status_val;
}

int CNotify::on_error(uint8_t error) {
  return 0;
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

  return 0;

}

int CNotify::on_key(const char *key, const char *value) {
  DEBUG("===> on_key: %s %s\n", key, value);

  return 0;

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
}

int CNotify::on_server(int type, const char *server, const char *username,
                       const char *password) {
  DEBUG("===> on_server: type %d server (%s)\n", type, server ? server : "");

  return 0;

}

int on_location(tMessageParams *p, const char *from, float lat, float lon,
                  const char *title, const char *message, const char *thumbnail,
                  int tnlen) {
    DEBUG("===> on_location: from: %s origin %d %f %f (%s) (%s)\n", from,
             p->origin, lat, lon, title, message);

    mesibo_py_log_param_message(p);

    PyObject *tMessageParams_dict_obj = PyDict_New();
    mesibo_py_build_param_messagedict(tMessageParams_dict_obj, p);

    PyObject *py_return_status =
        PyObject_CallMethod(PyNotifyClass, MESIBO_LISTENER_ON_LOCATION, "Odds",
                            tMessageParams_dict_obj, lat, lon,from);
    int status_val = 0;
    status_val = PyLong_AsLong(py_return_status);

    DEBUG(" " MESIBO_LISTENER_ON_LOCATION " returned:%d \n", status_val);

    Py_DECREF(tMessageParams_dict_obj);
    Py_DECREF(py_return_status);

    return status_val;

    return 0;
  }

