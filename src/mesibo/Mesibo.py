import ctypes
import platform
import multiprocessing
import sys
import os
import warnings

PYMESIBO_LIB = "libpymesibo"
MESIBO_LIB = "libmesibo"
CLIB_DIR = "clib"

MESIBO_LISTENER_ON_MESSAGE = "Mesibo_OnMessage"
MESIBO_LISTENER_ON_FILE = "Mesibo_OnRichMessage"
MESIBO_LISTENER_ON_MESSAGE_STATUS = "Mesibo_OnMessageStatus"
MESIBO_LISTENER_ON_CONNECTION_STATUS = "Mesibo_OnConnectionStatus"
MESIBO_LISTENER_ON_ACTIVITY = "Mesibo_OnActivity"
MESIBO_LISTENER_ON_SYNC = "Mesibo_OnSync"


def get_platform_lib(libname):
    
    platform_tag = ""
    
    # e.g Linux, Darwin(macos), Windows, Java, etc
    system = platform.system()
    if("" == system):
        system = "unknown"

    platform_tag = platform_tag + "_" + system.lower() 
    
    # e.g x86_64, i386, etc
    machine = platform.machine()
    if("" == machine):
        machine = "unknown"

    platform_tag = platform_tag + "_" + machine.lower()
    return libname + platform_tag + ".so"

def get_full_path_to_lib(lib_name):
    package_dir = os.path.dirname(os.path.realpath(__file__))
    clib_dir = os.path.join(package_dir, CLIB_DIR)
    platform_lib = get_platform_lib(lib_name)
    lib_path = os.path.join(clib_dir, platform_lib)
    return lib_path


# Use MesiboListener on the client end
# Internally  _MesiboNotify then calls client MesiboListener
class _MesiboNotify:
    def __init__(self, api):
        self._api = api
        self._listener = None
    
    def _set_client_listener(self, listener):
        self._listener = listener

    def notify_on_connectionstatus(self, status):
        mesibo_on_connectionstatus = getattr(self._listener, MESIBO_LISTENER_ON_CONNECTION_STATUS, None)
        if(callable(mesibo_on_connectionstatus)):
            return mesibo_on_connectionstatus(status)
        
        return 0

    def notify_on_message(self, params_dict, peer, data, datalen):
        msg_params = Mesibo.MessageParams()
        msg_params._init_from_dict(params_dict)
        msg_params.peer = peer
        msg_params.datalen = datalen    
        
        if(Mesibo.ORIGIN_REALTIME != msg_params.origin 
                and self._api._read_session 
                and self._api._read_session._listener):
            mesibo_on_message = getattr(self._api._read_session._listener, MESIBO_LISTENER_ON_MESSAGE, None)
            if(callable(mesibo_on_message)):
                return mesibo_on_message(msg_params, data)
        else:
            mesibo_on_message = getattr(self._listener, MESIBO_LISTENER_ON_MESSAGE, None)
            if(callable(mesibo_on_message)):
                return mesibo_on_message(msg_params, data)
        
        return 0

    def notify_on_messagestatus(self, params_dict, peer):
        msg_params = Mesibo.MessageParams()
        msg_params._init_from_dict(params_dict)
        msg_params.peer = peer

        mesibo_on_messagestatus = getattr(self._listener, MESIBO_LISTENER_ON_MESSAGE_STATUS, None)
        if(callable(mesibo_on_messagestatus)):
            return mesibo_on_messagestatus(msg_params)
        
        return 0

    def notify_on_activity(self, params_dict, peer, activity):
        msg_params = Mesibo.MessageParams()
        msg_params._init_from_dict(params_dict)
        msg_params.peer = peer

        mesibo_on_activity = getattr(self._listener, MESIBO_LISTENER_ON_ACTIVITY, None)
        if(callable(mesibo_on_activity)):
            return mesibo_on_activity(msg_params, activity)
        
        return 0
    
    def notify_on_sync(self, rs, count, flags):
        mesibo_on_sync = getattr(self._listener, MESIBO_LISTENER_ON_SYNC, None)
        if(callable(mesibo_on_sync)):
            return mesibo_on_sync(count)

        return 0

    def notify_on_file(self, params_dict, peer, file_dict):
        msg_params = Mesibo.MessageParams()
        msg_params._init_from_dict(params_dict)
        msg_params.peer = peer

        file_params = Mesibo.MesiboRichMessage()
        file_params._init_from_dict(file_dict)

        mesibo_on_file = getattr(self._listener, MESIBO_LISTENER_ON_FILE, None)
        if(callable(mesibo_on_file)):
            return mesibo_on_file(msg_params, file_params)
        
        return 0

class ReadDbSession:
    def __init__(self, mesibo_instance, peer, groupid, query, listener):
        self.peer = peer 
        self.groupid = groupid 
        self.query = query 
        self._listener = listener
        self.count = 0
        self.flag = 0
        self.mesibo_instance = mesibo_instance
        
        self.mesibo_instance._cpy.mesibo_set_readsession.restype = ctypes.c_void_p
        
        # TBD
        # If addListener is never called and you are only passing read listner, 
        # then we need to call read listener
        if(not self.mesibo_instance._get_listner()):
            self.mesibo_instance.addListener(listener)
        
        # If both addListener is called and read listener is set, 
        # then we check in mesibo_on_message and call read listener
        self.mesibo_instance._read_session = self

        self.c_read_session = self.mesibo_instance._cpy.mesibo_set_readsession(_get_raw_string(self.peer), 
                self.groupid, _get_raw_string(self.query))

    def enableReadReceipt(self, enable):
        self._cpy.mesibo_instance._cpy.mesibo_rs_readreceipt(ctypes.c_void_p(self.c_read_session), enable)

    def enableSummary(self, enable):
        self._cpy.mesibo_instance._cpy.mesibo_rs_summary(ctypes.c_void_p(self.c_read_session), enable)

    def read(self, count):
        return self.mesibo_instance._cpy.mesibo_read(ctypes.c_void_p(self.c_read_session), count) 
    
    def sync(self, count):
        return self.mesibo_instance._cpy.mesibo_sync(ctypes.c_void_p(self.c_read_session), count)

    def stop(self):
        self._cpy.mesibo_instance._cpy.mesibo_rs_stop(ctypes.c_void_p(self.c_read_session))
        self.mesibo_instance._read_session = None

class Mesibo:
    FLAG_DELIVERYRECEIPT = 0x1
    FLAG_READRECEIPT = 0x2
    FLAG_DEFAULT = FLAG_DELIVERYRECEIPT | FLAG_READRECEIPT 
    PY_EXPIRY_DEFAULT = 604800

    #Activity 0-1000 reserved for Mesibo
    ACTIVITY_NONE = 0;
    ACTIVITY_ONLINE = 1;
    ACTIVITY_ONLINERESP = 2;
    ACTIVITY_TYPING = 3;
    ACTIVITY_TYPINGCLEARED = 4;
    ACTIVITY_JOINED = 10;
    ACTIVITY_LEFT = 11;

    READFLAG_READRECEIPT = 1;
    READFLAG_SENDLAST = 2;
    READFLAG_FIFO = 4;
    READFLAG_SUMMARY = 0x10;
   
    ORIGIN_REALTIME = 0
    ORIGIN_DBMESSAGE = 1
    ORIGIN_DBSUMMARY = 2
    ORIGIN_DBPENDING = 3
    ORIGIN_FILTER = 4
    ORIGIN_MESSAGESTATUS = 5

    RESULT_OK = 0
    RESULT_FAIL = -1

    class MessageParams:
        def __init__(self):
            self.type = 0
            self.expiry = None 
            self.groupid = 0
            self.mid = 0
            self.flags = 0
            self.peer = None
            self.ts = 0
            self.status = -1
            self.datalen = 0
            self.origin = None

        def __str__(self):
            return "<" + "type: "+ str(self.type) + " expiry: "+ str(self.expiry) + \
                    " groupid: "+ str(self.groupid) + " id: "+ str(self.mid) + \
                    " flag: "+ str(self.flags) + " peer: "+ str(self.peer) + \
                    " when: "+ str(self.ts) + " status: "+ str(self.status) + " origin: " + str(self.origin) + ">" 

        #For internal use only
        def _init_from_dict(self, params_dict):
            self.mid = params_dict["mid"] 
            self.type = params_dict["type"] 
            self.flags = params_dict["flags"] 
            self.expiry = params_dict["expiry"] 
            self.status = params_dict["status"]
            self.ts = params_dict["ts"] 
            self.groupid = params_dict["groupid"]
            self.origin = params_dict["origin"]
 
    class MesiboRichMessage:
        def __init__(self):
            self.filetype = 0
            self.filesize = 0 
            self.fileurl = ""
            self.title = "" 
            self.message = ""
             
        #For internal use only
        def _init_from_dict(self, file_dict):
            self.filetype = file_dict["filetype"] 
            self.filesize = file_dict["filesize"] 
            self.fileurl = file_dict["fileurl"] 
            self.title = file_dict["title"] 
            self.message = file_dict["message"]
 
        def __str__(self):
            return "<" + "filetype: "+ str(self.filetype) + " filesize: "+ str(self.filesize) + \
                    " fileurl: "+ str(self.fileurl) + \
                    " title: "+ str(self.title) + " message: "+ str(self.message) + ">" 

    
    def __init__(self):
        _pymesibo_lib = get_full_path_to_lib(PYMESIBO_LIB)
        _mesibo_lib = get_full_path_to_lib(MESIBO_LIB)
        try:
            self._cpy = ctypes.cdll.LoadLibrary(_pymesibo_lib)
        except:
            print('Unable to load: '+ _pymesibo_lib + ' Platform not supported. Contact us at https://mesibo.com/support')
            raise

        if(-1 == self._cpy.mesibo_init(_get_raw_string(_mesibo_lib))):
            raise OSError('Unable to load: '+ _mesibo_lib + ' Platform not supported. Contact us at https://mesibo.com/support')
        
        self._listener = None
        self._read_session = None
        #self._set_cpu_info()


    def ReadDbSession(self, peer, groupid, query, listener):
        return ReadDbSession(self, peer, groupid, query, listener)

    def _set_cpu_info(self):
        machine = platform.machine()
        core_count = multiprocessing.cpu_count()
        self._cpy.mesibo_set_cpu(_get_raw_string(machine), core_count)

    
    def setAccessToken(self, token):
        return self._cpy.mesibo_set_accesstoken(_get_raw_string(token))
    
    def setAppName(self, appid):
        return self._cpy.mesibo_set_appname(_get_raw_string(appid))
    
    def setDatabase(self, db_name):
        return self._cpy.mesibo_set_database(_get_raw_string(db_name))
    
    def addListener(self, client_listener):
        prototype = ctypes.PYFUNCTYPE(
                ctypes.c_char_p,
                ctypes.py_object
                )

        py_notify = _MesiboNotify(self)
        if(client_listener):
            py_notify._set_client_listener(client_listener)
            self._listener = client_listener

        mesibo_add_listener = prototype(('mesibo_add_listener', self._cpy))
        # py_notify will call client_listener internally
        # See _MesiboNotify.py
        return mesibo_add_listener(py_notify) 
    
    # For internal use only
    def _get_listner(self):
        return self._listener

    def start(self):
        return self._cpy.mesibo_start()
    
    def stop(self):
        return self._cpy.mesibo_stop()

    def wait(self):
        return self._cpy.mesibo_wait()
    
    def random(self):
        return self._cpy.mesibo_random32()
    
    def timestamp(self):
        return self._cpy.mesibo_timestamp()
    
    def setSecureConnection(self, enable):
        self._cpy.mesibo_set_secure_connection(int(enable))

    def sendMessage(self, params, mid, message):
        print("send_message", params, params.peer, mid, message)
        if(params.expiry == None):
            params.expiry = self.PY_EXPIRY_DEFAULT
        
        params.id = mid
        # Convert any message type into bytearry before sending
        data_bytes = bytearray() 
        msg_type = type(message)

        if(msg_type is bytearray):
            data_bytes = message #no change
        else:
            if(msg_type is bytes):
                data_bytes = bytearray(message)
            else:
                encoded_bytes = str(message).encode('utf-8') #convert to bytes first
                data_bytes = bytearray(encoded_bytes) 
                # You can also convert to bytearray directly, but this is more clear
            
        return self._cpy.mesibo_send_byte_array(params.type, params.expiry,
                params.groupid, params.flag, _get_raw_string(params.peer), 
                mid, ctypes.py_object(data_bytes))
    
    def sendActivity(self, params, mid, activity, interval):
        
        params.id = mid

        print("sendActivity", params, mid, activity);
        return self._cpy.mesibo_send_activity(params.type, params.expiry,
                params.groupid, params.flag, _get_raw_string(params.peer),
                mid, activity, interval)

    def sendFile(self, params, mid, fileinfo):
        
        params.id = mid
        if(params.expiry == None):
            params.expiry = self.PY_EXPIRY_DEFAULT

        print("sendFile", params, mid, fileinfo);
        return self._cpy.mesibo_send_file(params.type, params.expiry,
                params.groupid, params.flag, _get_raw_string(params.peer), mid,
                fileinfo.filetype, fileinfo.filesize, _get_raw_string(fileinfo.fileurl), fileinfo.thumbnail, _get_raw_string(fileinfo.title), _get_raw_string(fileinfo.message))


    def deleteMessage(self, mid): 
        return self._cpy.mesibo_delete_message(mid, None, 0);
        
    def deleteMessages(self, mid_list, count, del_type): 
        return self._cpy.mesibo_delete_messages(ctypes.py_object(mid_list), count, del_type);
        
def _get_raw_string(s):
    if(not s):
        s = ""
    return s.encode('raw_unicode_escape')
