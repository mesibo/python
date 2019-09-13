// notify.h
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
