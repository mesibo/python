// core.h
#pragma once

#include <Python.h>

void mesibo_py_init();
PyObject *mesibo_py_start(PyObject *self);
PyObject *mesibo_py_stop(PyObject *self);

PyObject *mesibo_py_reconnect_now(PyObject *self, PyObject *type_arg);

PyObject *mesibo_py_set_debug(PyObject *self, PyObject *debug_args);

PyObject *mesibo_py_set_uniqid(PyObject *self, PyObject *uniqid_obj);
PyObject *mesibo_py_set_device(PyObject *self, PyObject *device_args);
PyObject *mesibo_py_set_cpu(PyObject *self, PyObject *cpu_args);
PyObject *mesibo_py_set_accesstoken(PyObject *self, PyObject *PyAppToken);

PyObject *mesibo_py_set_notify(PyObject *self, PyObject *notify_class_ref);
PyObject *mesibo_py_set_appstore(PyObject *self, PyObject *appstore_args);
PyObject *mesibo_py_set_bufferlen(PyObject *self, PyObject *buffer_args);
PyObject *mesibo_py_set_network(PyObject *self, PyObject *network_args);

PyObject *mesibo_py_send_message(PyObject *self, PyObject *message_args);
PyObject *mesibo_py_message_send(PyObject *self);
PyObject *mesibo_py_cancel(PyObject *self, PyObject *cancel_args);
PyObject *mesibo_py_random32(PyObject *self);
PyObject *mesibo_py_timestamp(PyObject *self);

PyObject *mesibo_py_set_secure(PyObject *self, PyObject *secure_obj);
PyObject *mesibo_py_set_server(PyObject *self, PyObject *server_obj);

PyObject *mesibo_py_set_readsession(PyObject *self, PyObject *session_args);
PyObject *mesibo_py_read(PyObject *self, PyObject *session_args);

PyObject *mesibo_py_set_database(PyObject *self, PyObject *PyDbName);
PyObject *mesibo_py_reset_database(PyObject *self, PyObject *tables_obj);
PyObject *mesibo_py_delete_messages(PyObject *self, PyObject *msg_args);
PyObject *mesibo_py_delete_message(PyObject *self, PyObject *msg_args);
PyObject *mesibo_py_delete_policy(PyObject *self, PyObject *policy_args);

PyObject *mesibo_py_set_key(PyObject *self, PyObject *args);
PyObject *mesibo_py_delete_key(PyObject *self, PyObject *key_arg);
PyObject *mesibo_py_read_key(PyObject *self, PyObject *read_args);
PyObject *mesibo_py_free_keyvaluebuffer(PyObject *self, PyObject *value_obj);
PyObject *mesibo_py_count_key(PyObject *self, PyObject *args);

PyObject *mesibo_py_read_contact(PyObject *self, PyObject *contact_args);
PyObject *mesibo_py_delete_contact(PyObject *self, PyObject *contact_args);

PyObject *mesibo_py_get_loginstatus(PyObject *self);
PyObject *mesibo_py_get_mapimage_url(PyObject *self, PyObject *mapimage_args);
PyObject *mesibo_py_phone_fqn(PyObject *self, PyObject *fqn_args);
PyObject *mesibo_py_phone_strip(PyObject *self, PyObject *strip_args);

PyObject *mesibo_py_send_readreceipt(PyObject *self, PyObject *receipt_args);
PyObject *mesibo_py_send_activity(PyObject *self, PyObject *activity_args);

PyObject *mesibo_py_send_messagebundle(PyObject *self, PyObject *bundle_args);

PyObject *mesibo_py_forward_message(PyObject *self, PyObject *message_args);
PyObject *mesibo_py_update_message(PyObject *self, PyObject *message_args);
PyObject *mesibo_py_send_pending(PyObject *self, PyObject *args);
PyObject *mesibo_py_resend_message(PyObject *self, PyObject *id_arg);

PyObject *mesibo_py_call(PyObject *self, PyObject *args);
PyObject *mesibo_py_answer(PyObject *self, PyObject *video_arg);
PyObject *mesibo_py_hangup(PyObject *self, PyObject *args);
PyObject *mesibo_py_mute(PyObject *self, PyObject *args);
PyObject *mesibo_py_hold(PyObject *self, PyObject *args);
PyObject *mesibo_py_set_pstn(PyObject *self, PyObject *args);
PyObject *mesibo_py_set_callprocessing(PyObject *self, PyObject *args);
PyObject *mesibo_py_set_answer_mode(PyObject *self, PyObject *args);
PyObject *mesibo_py_mute_status(PyObject *self);
PyObject *mesibo_py_set_callfactory(PyObject *self, PyObject *args);
PyObject *mesibo_py_callstatus_from_proxyrtc(PyObject *self, PyObject *args);
PyObject *mesibo_py_get_uid(PyObject *self);

PyObject *mesibo_py_wait(PyObject *self);

