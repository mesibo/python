// notify.h

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

#include <mesibo.h>
#include <Python.h>

extern PyObject * PyNotifyClass;

class CNotify : public INotify {
 
 public:

  void set_api(IMesibo *api);
  int on_message(tMessageParams *p, const char *from, const char *data,
                 uint32_t len);

  int on_messagebundle(tMessageParams *p, const char *from, tMessageBundle *m);
  int on_messagestatus(tMessageParams *p, const char *from, int last);
  int on_status(int status, uint32_t substatus, uint8_t channel,
                const char *from);
  int on_error(uint8_t error);
  int on_activity(tMessageParams *p, const char *from, uint32_t event);

  int on_call(uint32_t peerid, uint32_t callid, int status, const char *data,
              int datalen, uint64_t flags);
  int on_key(const char *key, const char *value);
  int on_contact(const tContact *c);
  int on_rtc(int type, uint32_t flags, uint32_t peerid, const char *sdp,
             int len);
  int on_server(int type, const char *server, const char *username,
                const char *password);
  int on_location(tMessageParams *p, const char *from, float lat, float lon,
                  const char *title, const char *message, const char *thumbnail,
                  int tnlen);
};
