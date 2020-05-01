// core.h

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

void mesibo_py_init();
PyObject *mesibo_py_start(PyObject *self);
PyObject *mesibo_py_stop(PyObject *self);

PyObject *mesibo_py_reconnect_now(PyObject *self, PyObject *type_arg);

PyObject *mesibo_py_set_debug(PyObject *self, PyObject *debug_args);

PyObject *mesibo_py_set_uniqid(PyObject *self, PyObject *uniqid_obj);
PyObject *mesibo_py_set_appname(PyObject *self, PyObject *device_args);
PyObject *mesibo_py_set_accesstoken(PyObject *self, PyObject *PyAppToken);

PyObject *mesibo_py_set_notify(PyObject *self, PyObject *notify_class_ref);
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
