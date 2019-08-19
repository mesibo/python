// globals.h
#pragma once

#include <mesibo.h>

extern int gDebugEnabled ;

#define DEBUG(format, ...)               \
  do {                                      \
    if(gDebugEnabled == 1)fprintf(stderr, format, ##__VA_ARGS__); \
  } while (0)


int keypress();

extern IMesibo* m_api;
extern INotify* n;

#define ID "id"
#define REFID "refid"
#define UID "uid"
#define GROUPID "groupid"
#define EXPIRY "expiry"
#define FLAG "flag"
#define WHEN "when"
#define RETAINTS "retaints"
#define UFLAGS "uflags"
#define STATUS "status"
#define CHANNEL "channel"
#define TYPE "type"
#define ORIGIN "origin"
#define SAVED "saved"
#define THUMBNAIL "thumbnail"
#define TNLEN "tnlen"
#define FILEPATH "filepath"
#define READ_SESSION "read_session"

#define DATA "data"
#define DATALEN "datalen"
#define MSGLEN "msglen"
#define MESSAGE "message"
#define TITLE "title"
#define FILESIZE "filesize"
#define FILETYPE "filetype"
#define FILEURL "fileurl"
#define FILEPATH "filepath"
#define LAUNCHURL "launchurl"
#define THUMBNAIL_SEND "thumbnail_send"
#define TNSLEN "tnslen"
#define THUMBNAIL "thumbnail"
#define TNLEN "tnlen"
#define HAS_LOCATION "has_location"
#define LAT "lat"
#define LON "lon"
#define LAT_D "lat_d"
#define LON_D "lon_d"
#define LOCATION "location"
#define RRID "rrid"
#define ACTIVITY "activity"
#define HAS_ACTIVITY "has_activity"

