// docs.cpp
// Contains docstrings for python methods

#include <Python.h>
#ifndef PyDoc_STR
#define PyDoc_VAR(name) static char name[]
#define PyDoc_STR(str) (str)
#define PyDoc_STRVAR(name, str) PyDoc_VAR(name) = PyDoc_STR(str)
#endif

PyDoc_STRVAR(answer__doc__,
             "answer(video) -> int \n\n"
             "Parameters \n---------- \n"
             "video: int \n"
             "Answer video call");
PyDoc_STRVAR(call__doc__,
             "call(destination,type) -> int \n\n"
             "Parameters \n---------- \n"
             "destination: string \n"
             "type: int \n"
             "Make a call");
PyDoc_STRVAR(callStatus__doc__,
             "call_status(status,sdp,sdplen)->int \n\n"
              "Parameters \n---------- \n"
              "status: int \n"
              "sdp: str \n"
              "sdplen: int \n"
              "Call Status from a proxy rtc ");
PyDoc_STRVAR(cancel__doc__,
    	     "cancel(type,id) ->int \n\n"
    	     "Parameters \n---------- \n"
    	     "type:int \n"
    	     "MessageParams"
    	     "id:unsigned int \n" 	
    	     "Message ID \n\n"
    	     "Cancel a message.Message can not be canceled if already sent & delivered");

PyDoc_STRVAR(countKey__doc__,
             "count_key(key,value) ->int \n\n"
             "Parameters \n---------- \n"
             "key:str \n"
             "value:str \n"
             "Count Key");
PyDoc_STRVAR(deleteContact__doc__,
             "delete_contact(address,groupid) ->int \n\n"
             "Parameters \n---------- \n"
             "address:str \n"
             "groupid:unsigned int \n"
             "Delete Contact");
PyDoc_STRVAR(deleteKey__doc__,
             "delete_key(key) ->int \n\n"
             "Parameters \n---------- \n"
             "key:str \n"
             "Delete Key");
PyDoc_STRVAR(deleteMessage__doc__,
             "delete_message(id,from,groupid,ts) ->int \n\n"
             "Parameters \n---------- \n"
             "id: unsigned int \n"
             "from: str \n"
             "groupid: unsigned int \n"
             "ts: unsigned int \n\n"
             "Delete message with a specific criteria");

PyDoc_STRVAR(deleteMessages__doc__,
             "delete_messages(ids,count,deltype) ->int \n\n"
             "Parameters \n---------- \n"
             "ids: list of unsigned int \n"
             "Message ID(s) (list) \n"
             "count: int \n"
             "deltype: int \n\n"
             "Delete single/multiple messages");
PyDoc_STRVAR(deletePolicy__doc__,
             "delete_policy(maxinterval,deletetype) ->int \n\n"
             "Parameters \n---------- \n"
             "maxinterval: int \n"
             "deletetype: int \n\n"
             "Delete Policy");

PyDoc_STRVAR(forwardMessage__doc__,
             "forward_message(parameters,to,id) ->int \n\n"
             "Parameters \n---------- \n"
             "parameters: dict \n"
             "MessageParams \n"
             "to: str \n"
             "Destination \n"
             "id: unsigned int \n"
             "ID of message to be forwared \n\n"
             " Forward a message ");
PyDoc_STRVAR(freeKeyValueBuffer__doc__,
             "free_keyvaluebuffer(value) ->void \n\n"
             "Parameters \n---------- \n"
             "value: str \n"
             "Free Key Value Buffer");
PyDoc_STRVAR(hangup__doc__,
             "hangup(callid,status) ->int \n\n"
             "Parameters \n---------- \n"
             "callid: unsigned int \n"
             "status: int \n"
             "Hangup call");
PyDoc_STRVAR(hold__doc__,
             "hold(enable) ->int \n\n"
             "Parameters \n---------- \n"
             "enable: int \n"
             "Hold call");
PyDoc_STRVAR(getLoginStatus__doc__,
             "get_loginstatus()-> int \n\n"
             "Get Login Status");
PyDoc_STRVAR(getMapimageUrl__doc__,
             "get_map_imageurl(lat,lon,width,zoom,url) \n\n"
             "Parameters \n---------- \n"
             "lat: float \n"
             "lon: float \n"
             "width: int \n"
             "zoom: int \n"
             "url: int \n"
             " Get Map Image URL ");
PyDoc_STRVAR(getUid__doc__,
             "get_uid() ->uint32 \n\n"
             "Get User ID");
PyDoc_STRVAR(messageSend__doc__,
             "message_send()->int \n\n"
             "Message send");
PyDoc_STRVAR(mute__doc__,
             "mute(audio,video,enable) ->int \n\n"
             "Parameters \n---------- \n"
             "audio: int \n"
             "video: int \n"
             "enable:int \n"
             "Mute");
PyDoc_STRVAR(muteStatus__doc__,
             "mute_status() ->int \n\n"
             "Get Mute Status");
PyDoc_STRVAR(phoneFqn__doc__,
             "phone_fqn(phone,country_code,mcc,fqn) -> void \n\n"
             "Parameters \n---------- \n"
             "phone: str \n"
             "country_code: int \n "
             "mcc: int \n"
             "fqn: str \n"
             "Phone fqn");
PyDoc_STRVAR(phoneStrip__doc__,
             "phone_strip(phone,strip_prefix,fqn)-> void \n\n"
             "Parameters \n---------- \n"
             "phone:str \n"
             "strip_prefix:int \n"
             "fqn:str \n"
             "Phone strip");
PyDoc_STRVAR(random__doc__,
             "random()->uint32 \n\n"
             "Returns 32-bit pseudo-random number");
PyDoc_STRVAR(read__doc__,
             "read(rs,count) -> int \n\n"
             "Parameters \n---------- \n"
             "rs: unsigned int (void ptr) \n"
             "count:int \n"
             "Parameters:Number of messages to be read \n\n"
             "Read messages. All subsequent read() will read next messages.");

PyDoc_STRVAR(readContact__doc__,
             "read_contact(address,groupid,orderby,count) ->int \n\n"
             "Parameters \n---------- \n"
             "address: str \n"
             "groupid: unsigned int \n"
             "orderby: str \n"
             "count: int \n\n"
             "Read Contact");

PyDoc_STRVAR(readKey__doc__,
             "read_key(key)->int \n\n"
             "Parameters \n---------- \n"
             "key:str \n\n"
             "Read key");
PyDoc_STRVAR(reconnect__doc__,
             "reconnect(type) ->void \n\n"
             "Parameters \n---------- \n"
             "type:int \n\n"
             "Reconnect Now");
PyDoc_STRVAR(resend__doc__,
             "resend(id) ->int \n\n"
             "Parameters \n---------- \n"
             "id: unsigned int \n"
             "Message ID of failed message \n\n"
             "Resend a failed message");
PyDoc_STRVAR(resetDatabase__doc__,
             "reset_database(tables) ->int \n\n"
             "Parameters \n---------- \n"
             "tables: unsigned int \n\n"
             "Reset database object");

PyDoc_STRVAR(sendActivity__doc__,
             "send_activity(parameters,to,activity,interval) ->int \n\n"
             "Parameters \n---------- \n"
             "parameters: MessageParams dict\n"
             "to: str \n"
             "activity: unsigned int \n"
             "interval: unsigned int \n\n"
             "Send Activity");
PyDoc_STRVAR(sendMessage__doc__,
             "send_message(parameters,to,data,len) ->int \n\n"
             "Parameters \n---------- \n"
             "parameters: MessageParams dict \n"
             "to: str \n"
             "data: str/bytes \n"
             "len: int \n\n"             
             "Send a message\n"
	       "There are overloaded functions to send message \n"
             "In different formats, for example, string, byte array etc.");

PyDoc_STRVAR(
    sendFile__doc__,
    "send_file(messagesParameters,to,fileParameters) -> int \n\n"
    "Parameters \n---------- \n"
    "messagesParameters: MessageParams dict \n"
    "to: str \n"
    "fileParameters: FileParams dict \n\n"
    "Send File bundle");

PyDoc_STRVAR(sendPending__doc__,
             "send_pending(id,flag) ->int \n\n"
             "Parameters \n---------- \n"
             "id: unsigned int \n"
             "flag: int \n"
             "Send Pending");
PyDoc_STRVAR(sendReadReceipt__doc__,
             "send_readreceipt(id) ->int \n\n"
             "Parameters \n---------- \n"
             "id: unsigned int \n\n"
             "Manually send a read receipt");
PyDoc_STRVAR(setAnswerMode__doc__,
             "set_answermode(lateconnect)->int \n\n"
             "Parameters \n---------- \n"
             "lateconnect:int \n\n"
             "Set Answer Mode");
PyDoc_STRVAR(setAppstore__doc__,
             "set_appstore(stroreid,store) ->int \n\n"
             "Parameters \n---------- \n"
             "storeid:int \n"
             "store: str \n\n"
             "Set Appstore");
PyDoc_STRVAR(setBufferLen__doc__,
             "set_bufferlen(len,empty) ->int \n\n"
             "Parameters \n---------- \n"
             "len:int \n"
             "empty:int \n\n"
             "Set BufferLen");
PyDoc_STRVAR(setCallFactory__doc__,
             "set_callfactory(type,factory)->void \n\n"
             "Parameters \n---------- \n"
             "type: int \n"
             "factory: unsigned int(void ptr) \n\n"
             "Set Call Factory");
PyDoc_STRVAR(setCallProcessing__doc__,
             "set_callprocessing(callRejectStatus,currentCallStatus) ->void \n\n"
             "Parameters \n---------- \n"
             "callRejectStatus:int \n"
             "currentCallStatus:int \n"
             "Set Call Processing");
PyDoc_STRVAR(setCpu__doc__,
             "set_cpu(family,features,count) ->void \n\n"
             "Parameters \n---------- \n"
             "family:int \n"
             "features: unsigned int \n"
             "count: int \n\n"
             "Set CPU");
PyDoc_STRVAR(setAccessToken__doc__,
             "set_accesstoken(cookie) -> int \n\n"
             "Parameters \n---------- \n"
             "cookie: str \n\n"
             "Set access token for the user.");
PyDoc_STRVAR(setDatabase__doc__,
             "set_database(path) -> int \n\n"
             "Parameters \n---------- \n"
             "path:str \n"
             " Name or complete path of the database. If path is \n"
             "not specified, the database will be stored in the default path \n"
             "or the path set by setPath API. \n\n"

             "Enable local database to store messages, and other \n"
             "information.If setDatabase is called before set_accesstoken(), \n"
             "same database will be used for all the users. It is recommended \n"
             "to call it after set_accesstoken() API.");
PyDoc_STRVAR(setDebug__doc__,
             "set_debug(loglevel,debugflags) ->void \n\n"
             "Parameters \n---------- \n"
             "loglevel: int \n"
             "debugflags: unsigned int \n\n"
             "Set Debug");

PyDoc_STRVAR(setDevice__doc__,
             "set_appname(app_id) ->int\n\n"
             "Parameters \n---------- \n"
             "app_id: str \n\n"
             "Set Device");
PyDoc_STRVAR(setKey__doc__,
             "set_key(key,value) ->int \n\n"
             "Parameters \n---------- \n"
             "key:str \n"
             "value:str \n\n"
             "set Key");
PyDoc_STRVAR(setNetwork__doc__,
             "set_network(type,ipaddr,gwaddr,lastport) ->int \n\n"
             "Parameters \n---------- \n"
             "type: unsigned int \n"
             "ipaddr: unsigned int \n"
             "gwaddr:unsigned int \n"
             "lastport:unsigned int \n\n"
             "Set Network");
PyDoc_STRVAR(setNotify__doc__,
             "set_listener(listener_class) -> void \n\n"
             "Parameters \n---------- \n"
             "listener_class: Python class object \n\n"
             "Set Notify");
PyDoc_STRVAR(setPstn__doc__,
             "set_pstn(server,port) ->int \n\n"
             "server:str \n"
             "port:int \n"
             "Set Pstn");
PyDoc_STRVAR(setReadingSession__doc__,
             "set_readingsession(data,flag,from,groupid,searchquery) -> int \n\n"
             "Parameters \n---------- \n"
             "data: unsigned int (void ptr) \n"
             "flag: unsigned int \n"
             "from: str \n"
             "groupid: unsigned int \n"
             "searchquery: str \n\n"
      
             "Set a reading session");
PyDoc_STRVAR(setSecureConnection__doc__,
             "set_secureconnection(secure) -> void \n\n"
             "Parameters \n---------- \n"
             "secure: int \n"
             "Enable encrypted connection");
PyDoc_STRVAR(setServer__doc__,
             "set_server(server) ->int \n\n"
             "Set Server");

PyDoc_STRVAR(setUniqid__doc__,
             "set_uniqid(uniqid) -> void \n\n"
             "Set Uniquid");
PyDoc_STRVAR(
    start__doc__,
    "start() ->int \n\n"
    "Parameters: Void  \n\n"
    "Start mesibo connection establishment. mesibo will not establish network \n"
    "connection till the start() is called. However, once the start() is \n"
    "called, mesibo will automatically manage any future reconnections till \n"
    "stop() is called.");
PyDoc_STRVAR(stop__doc__,
             "stop()->int \n\n"
             "Parameters: Void \n\n"
             "Disconnect any existing connection and also prevent future "
             "reconnections.");
PyDoc_STRVAR(timestamp__doc__,
             "timestamp()->uint64_t \n\n"
             "Get current timestamp (in ms)");
PyDoc_STRVAR(updateMessage__doc__,
             "update_message(id,flag,status,thumbnail,tnlen,filepath)->int \n\n"
             "Update Message");
PyDoc_STRVAR(wait__doc__,
             "wait()->void \n\n"
             "Wait");
