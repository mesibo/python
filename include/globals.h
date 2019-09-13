// globals.h

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

