import ctypes
import platform
import multiprocessing
import sys
import os
import warnings

package_dir = os.path.dirname(os.path.realpath(__file__))
clib_dir = os.path.join(package_dir, 'clib')

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

PYMESIBO_LIB = get_platform_lib("libpymesibo")
MESIBO_LIB = get_platform_lib("libmesibo")

PYMESIBO_LIB_PATH = os.path.join(clib_dir, PYMESIBO_LIB)
MESIBO_LIB_PATH = os.path.join(clib_dir, MESIBO_LIB)

# Use MesiboListener on the client end
# _MesiboNotify then calls client MesiboListener
# For internal use only
class _MesiboNotify:
    def __init__(self):
        self._listener = None 
    
    def _set_client_listener(self, listener):
        self._listener = listener

    def notify_on_connectionstatus(self, status):
        return self._listener.mesibo_on_connectionstatus(status) 

    def notify_on_message(self, params_dict, peer, data, datalen):
        msg_params = Mesibo.MessageParams()
        msg_params.init_from_dict(params_dict)
        msg_params.peer = peer
        msg_params.datalen = datalen    
       
        mesibo_on_message = getattr(self._listener, "mesibo_on_message", None)
        if(callable(mesibo_on_message)):
            return self._listener.mesibo_on_message(msg_params, data)
        
        return 0

    def notify_on_messagestatus(self, params_dict, peer):
        msg_params = Mesibo.MessageParams()
        msg_params.init_from_dict(params_dict)
        msg_params.peer = peer

        mesibo_on_messagestatus = getattr(self._listener, "mesibo_on_messagestatus", None)
        if(callable(mesibo_on_messagestatus)):
            return self._listener.mesibo_on_messagestatus(msg_params)
        
        return 0

    def notify_on_activity(self, params_dict, peer, activity):
        msg_params = Mesibo.MessageParams()
        msg_params.init_from_dict(params_dict)
        msg_params.peer = peer

        mesibo_on_activity = getattr(self._listener, "mesibo_on_activity", None)
        if(callable(mesibo_on_activity)):
            return self._listener.mesibo_on_activity(msg_params, activity)
        
        return 0
    
    def notify_on_sync(self, rs, count, flags):
        mesibo_on_sync = getattr(self._listener, "mesibo_on_sync", None)
        if(callable(mesibo_on_sync)):
            return self._listener.mesibo_on_sync(count)

        return 0

    def notify_on_file(self, params_dict, peer, file_dict):
        msg_params = Mesibo.MessageParams()
        msg_params.init_from_dict(params_dict)
        msg_params.peer = peer

        file_params = Mesibo.FileInfo()
        file_params.init_from_dict(file_dict)

        mesibo_on_file = getattr(self._listener, "mesibo_on_file", None)
        if(callable(mesibo_on_file)):
            return self._listener.mesibo_on_file(msg_params, file_params)
        
        return 0

class ReadDbSession:
    def __init__(self, mesibo_instance, peer, groupid, query, listener):
        self.peer = peer 
        self.groupid = groupid 
        self.query = query 
        self.listener = listener
        self.count = 0
        self.flag = 0
        self.mesibo_instance = mesibo_instance
        
        self.mesibo_instance._cpy.mesibo_set_readsession.restype = ctypes.c_void_p
        
        # TBD
        if(not self.mesibo_instance._get_listner()):
            self.mesibo_instance.add_listener(listener)

        self.c_read_session = self.mesibo_instance._cpy.mesibo_set_readsession(self.flag, _get_raw_string(self.peer), 
                self.groupid, _get_raw_string(self.query))

    def enable_read_receipt(self, enable):
        if(enable):
            self.flag = self.flag | Mesibo.READFLAG_READRECEIPT
        else:
            self.flag = self.flag & ~ Mesibo.READFLAG_READRECEIPT
       
        self.c_read_session = self.mesibo_instance._cpy.mesibo_set_readsession(self.flag, _get_raw_string(self.peer), 
                self.groupid, _get_raw_string(self.query))

    def enable_summary(self, enable):
        if(enable):
            self.flag = self.flag | Mesibo.READFLAG_SUMMARY
        else:
            self.flag = self.flag & ~ Mesibo.READFLAG_SUMMARY
       
        self.c_read_session = self.mesibo_instance._cpy.mesibo_set_readsession(self.flag, _get_raw_string(self.peer), 
                self.groupid, _get_raw_string(self.query))

    def read(self, count):
        return self.mesibo_instance._cpy.mesibo_read(ctypes.c_void_p(self.c_read_session), count) 
    
    def sync(self, count):
        return self.mesibo_instance._cpy.mesibo_sync(ctypes.c_void_p(self.c_read_session), count)

        
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
    READFLAG_SENDLAST    = 2;
    READFLAG_FIFO        = 4;
    READFLAG_SUMMARY    = 0x10;
    
    RESULT_OK = 0
    RESULT_FAIL = -1

    class MessageParams:
        def __init__(self):
            self.type = 0
            self.expiry = None 
            self.groupid = 0
            self.id = 0
            self.flag = 0
            self.peer = None
            self.when = 0
            self.status = -1
            self.datalen = 0

        def __str__(self):
            return "<" + "type: "+ str(self.type) + " expiry: "+ str(self.expiry) + \
                    " groupid: "+ str(self.groupid) + " id: "+ str(self.id) + \
                    " flag: "+ str(self.flag) + " peer: "+ str(self.peer) + \
                    " when: "+ str(self.when) + " status: "+ str(self.status) + ">" 

        def init_from_dict(self, params_dict):
            self.id = params_dict["id"] 
            self.type = params_dict["type"] 
            self.flag = params_dict["flag"] 
            self.expiry = params_dict["expiry"] 
            self.status = params_dict["status"]
            self.when = params_dict["when"] 
            self.groupid = params_dict["groupid"]
 
    class FileInfo:
        def __init__(self):
            self.filetype = 0
            self.filesize = 0 
            self.fileurl = 0
            self.thumbnail = 0
            self.title = "" 
            self.message = ""
             
        def init_from_dict(self, file_dict):
            self.type = file_dict["filetype"] 
            self.size = file_dict["filesize"] 
            self.url = file_dict["fileurl"] 
            self.tn = file_dict["thumbnail"]
            self.title = file_dict["title"] 
            self.message = file_dict["message"]
 
        def __str__(self):
            return "<" + "filetype: "+ str(self.filetype) + " filesize: "+ str(self.filesize) + \
                    " fileurl: "+ str(self.fileurl) + " thumbnail: "+ str(self.thumbnail) + \
                    " title: "+ str(self.title) + " message: "+ str(self.message) + ">" 

    
    def __init__(self):
        try:
            self._cpy = ctypes.cdll.LoadLibrary(PYMESIBO_LIB_PATH)
        except:
            print('Unable to load: '+ PYMESIBO_LIB_PATH + ' Platform not supported. Contact us at https://mesibo.com/support')
            raise

        if(-1 == self._cpy.mesibo_init(_get_raw_string(MESIBO_LIB_PATH))):
            raise OSError('Unable to load: '+ MESIBO_LIB_PATH + ' Platform not supported. Contact us at https://mesibo.com/support')
        
        self._listner = None
        self._set_cpu_info()


    def ReadDbSession(self, peer, groupid, query, listener):
        return ReadDbSession(self, peer, groupid, query, listener)

    def _set_cpu_info(self):
        machine = platform.machine()
        core_count = multiprocessing.cpu_count()
        self._cpy.mesibo_set_cpu(_get_raw_string(machine), core_count)

    
    def set_accesstoken(self, token):
        return self._cpy.mesibo_set_accesstoken(_get_raw_string(token))
    
    def set_appname(self, appid):
        return self._cpy.mesibo_set_appname(_get_raw_string(appid))
    
    def set_database(self, db_name):
        return self._cpy.mesibo_set_database(_get_raw_string(db_name))
    
    def add_listener(self, client_listener):
        prototype = ctypes.PYFUNCTYPE(
                ctypes.c_char_p,
                ctypes.py_object
                )

        py_notify = _MesiboNotify()
        py_notify._set_client_listener(client_listener)
        self._listner = client_listener

        mesibo_add_listener = prototype(('mesibo_add_listener', self._cpy))
        # py_notify will call client_listener internally
        # See _MesiboNotify.py
        return mesibo_add_listener(py_notify) 
    
    # For internal use only
    def _get_listner(self):
        return self._listner

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
    
    def set_secure_connection(self, enable):
        self._cpy.mesibo_set_secure_connection(int(enable))

    def send_message(self, params, mid, message):
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
    
    def send_activity(self, params, mid, activity, interval):
        
        params.id = mid

        print("send_activity", params, mid, activity);
        return self._cpy.mesibo_send_activity(params.type, params.expiry,
                params.groupid, params.flag, _get_raw_string(params.peer),
                mid, activity, interval)

    def send_file(self, params, mid, fileinfo):
        
        params.id = mid
        if(params.expiry == None):
            params.expiry = self.PY_EXPIRY_DEFAULT

        print("send_file", params, mid, fileinfo);
        return self._cpy.mesibo_send_file(params.type, params.expiry,
                params.groupid, params.flag, _get_raw_string(params.peer), mid,
                fileinfo.filetype, fileinfo.filesize, _get_raw_string(fileinfo.fileurl), fileinfo.thumbnail, _get_raw_string(fileinfo.title), _get_raw_string(fileinfo.message))


    def delete_message(self, mid): 
        return self._cpy.mesibo_delete_message(mid, None, 0);
        
    def delete_messages(self, mid_list, count, del_type): 
        return self._cpy.mesibo_delete_messages(ctypes.py_object(mid_list), count, del_type);
        
def _get_raw_string(s):
    if(not s):
        s = ""
    return s.encode('raw_unicode_escape')
