import ctypes
import platform
import multiprocessing
import sys
import os
import warnings

from .version import __mesibo_version__

PYMESIBO_LIB = "libpymesibo"
MESIBO_LIB = "libmesibo"
CLIB_DIR = "clib"

MESIBO_LISTENER_ON_MESSAGE = "Mesibo_onMessage"
MESIBO_LISTENER_ON_MESSAGE_UPDATE = "Mesibo_onMessageUpdate"
MESIBO_LISTENER_ON_MESSAGE_STATUS = "Mesibo_onMessageStatus"
MESIBO_LISTENER_ON_CONNECTION_STATUS = "Mesibo_onConnectionStatus"
MESIBO_LISTENER_ON_ACTIVITY = "Mesibo_onPresence"
MESIBO_LISTENER_ON_SYNC = "Mesibo_onSync"

LIB_INSTANCE = None

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

    if(MESIBO_LIB != libname):
        libname = libname + platform.python_version_tuple()[0]

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

    def notify(self, params_dict, func):
        msg = MesiboMessage("")
        msg._init_from_dict(params_dict)
        
        if(Mesibo.ORIGIN_REALTIME != msg.origin 
                and self._api._read_session 
                and self._api._read_session._listener):
            mesibo_on_message = getattr(self._api._read_session._listener, func, None)
            if(callable(mesibo_on_message)):
                return mesibo_on_message(msg)
        else:
            mesibo_on_message = getattr(self._listener, func, None)
            if(callable(mesibo_on_message)):
                return mesibo_on_message(msg)
        
        return 0


    def notify_on_message(self, params_dict):
        self.notify(params_dict, MESIBO_LISTENER_ON_MESSAGE);
        return 0

    def notify_on_messageupdate(self, params_dict):
        self.notify(params_dict, MESIBO_LISTENER_ON_MESSAGE_UPDATE);
        return 0

    def notify_on_messagestatus(self, params_dict):
        self.notify(params_dict, MESIBO_LISTENER_ON_MESSAGE_STATUS);
        return 0

    def notify_on_activity(self, peer, groupid, activity):
        msg = MesiboPresence(peer)
        msg.peer = peer
        msg.groupid = groupid
        msg.presence = activity

        mesibo_on_activity = getattr(self._listener, MESIBO_LISTENER_ON_ACTIVITY, None)
        if(callable(mesibo_on_activity)):
            return mesibo_on_activity(msg)
        
        return 0
    
    def notify_on_sync(self, rs, count, flags):
        mesibo_on_sync = getattr(self._listener, MESIBO_LISTENER_ON_SYNC, None)
        if(callable(mesibo_on_sync)):
            return mesibo_on_sync(count)

        return 0

class MesiboEndToEndEncryption:
    def __init__(self, mesibo_instance):
        self.mesibo_instance = mesibo_instance
        self.mesibo_instance._cpy.mesibo_e2ee_getfp.argtypes = (ctypes.c_char_p, ctypes.c_int)
        # override the default return type which is int
        self.mesibo_instance._cpy.mesibo_e2ee_getfp.restype = ctypes.c_char_p
        self.mesibo_instance._cpy.mesibo_e2ee_getcertinfo.argtypes = (ctypes.c_char_p, ctypes.c_int)
        self.mesibo_instance._cpy.mesibo_e2ee_getcertinfo.restype = ctypes.c_char_p
        
    def enable(self, enable):
        self.mesibo_instance._cpy.mesibo_e2ee_enable(enable)

    def setLevel(self, level):
        self.mesibo_instance._cpy.mesibo_e2ee_setlevel(level)

    def setCiphers(self, supported, preferred):
        self.mesibo_instance._cpy.mesibo_e2ee_setciphers(supported, preferred)

    def setAuthenticationTaglen(self, len):
        self.mesibo_instance._cpy.mesibo_e2ee_settaglen(len)

    def setAuthenticationData(self, address, aad):
        return self.mesibo_instance._cpy.mesibo_e2ee_setaad(_get_raw_string(address), _get_raw_string(aad))

    def getPublicCertificate(self, filename):
        return self.mesibo_instance._cpy.mesibo_e2ee_getpubcert(_get_raw_string(filename))

    def setPrivateCertificate(self, filename):
        return self.mesibo_instance._cpy.mesibo_e2ee_setprivcert(_get_raw_string(filename))

    def setPeerCertificate(self, address, filename):
        return self.mesibo_instance._cpy.mesibo_e2ee_setpeercert(_get_raw_string(address), _get_raw_string(filename))

    def setPassword(self, address, password):
        return self.mesibo_instance._cpy.mesibo_e2ee_setpass(_get_raw_string(address), _get_raw_string(password))
    
    def getFingerprint(self, address):
        return self.mesibo_instance._cpy.mesibo_e2ee_getfp(_get_raw_string(address), 0).decode("utf-8")
    
    def getUserFingerprint(self, address):
        return self.mesibo_instance._cpy.mesibo_e2ee_getfp(_get_raw_string(address), 1).decode("utf-8")
    
    def getPeerCertificateOrg(self, address):
        return self.mesibo_instance._cpy.mesibo_e2ee_getcertinfo(_get_raw_string(address), 0).decode("utf-8")
    
    def getPeerCertificateCommonName(self, address):
        return self.mesibo_instance._cpy.mesibo_e2ee_getcertinfo(_get_raw_string(address), 1).decode("utf-8")
    

class MesiboReadSession:
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

class MessageParams:
    __slots__ = ("mid", "type", "flags", "expiry", "status", "ts", "groupid", "origin", "peer")

    def __init__(self, destination):
        self.type = 0
        self.expiry = -1 
        self.groupid = 0
        self.mid = -1
        self.flags = -1
        self.peer = None
        self.ts = 0
        self.status = -1
        self.origin = None
        if isinstance(destination, str):
            self.peer = destination
        else:   
            self.groupid = destination


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
        self.peer = params_dict["peer"]

class MesiboMessage(MessageParams):
    __slots__ = ("data", "message", "title", "subtitle", "filepath", "fileurl", "filetype", "filesize", "__content")

    def __init__(self, destination):
        super().__init__(destination)
        self.data = None
        self.filetype = 0
        self.filesize = 0 
        self.fileurl = ""
        self.title = "" 
        self.subtitle = "" 
        self.message = ""

        self.__content = ""

        #For internal use only
    def _init_from_dict(self, file_dict):
        super()._init_from_dict(file_dict)
        self.filetype = file_dict["filetype"] 
        self.filesize = file_dict["filesize"] 
        self.fileurl = file_dict["fileurl"] 
        self.filepath = file_dict["filepath"] 
        self.title = file_dict["title"] 
        self.subtitle = file_dict["subtitle"] 
        self.message = file_dict["message"]
        self.data = file_dict["data"]

    def __str__(self):
        return super().__str__() + " <" + "filetype: "+ str(self.filetype) + " filesize: "+ str(self.filesize) + \
                " fileurl: "+ str(self.fileurl) + " filepath: "+ str(self.filepath) + \
                " title: "+ str(self.title) + " subtitle: "+ str(self.subtitle) + " message: "+ str(self.message) + ">" 

    def setContent(self, path):
        self.__content = path

    def send(self):
        global LIB_INSTANCE
        # Convert any message type into bytearry before sending
        data_bytes = bytearray() 
        msg_type = type(self.data)

        if(msg_type is bytearray):
            data_bytes = self.data #no change
        elif(msg_type is bytes):
            data_bytes = bytearray(self.data)
        else:
            if isinstance(self.data, str):
               encoded_bytes = str(self.data).encode('utf-8') #convert to bytes first
               data_bytes = bytearray(encoded_bytes) 

            # You can also convert to bytearray directly, but this is more clear

        return LIB_INSTANCE.mesibo_send(super().type, super().expiry,
                super().groupid, super().flags, _get_raw_string(super().peer), 
                super().mid, _get_raw_string(self.__content), 
                _get_raw_string(self.title),
                _get_raw_string(self.subtitle),
                _get_raw_string(self.message),
                ctypes.py_object(data_bytes))


    def delete(self):
        global LIB_INSTANCE
        return LIB_INSTANCE.mesibo_delete_message(mid, None, 0);

class MesiboPresence:
    __slots__ = ("peer", "groupid", "presence", "interval")

    def __init__(self, destination):
        self.groupid = 0
        self.presence = 0 
        self.interval = 0
        self.peer = "" 

    def __str__(self):
        return " <" + "presence: "+ str(self.presence) + " peer: "+ str(self.peer) + ">" 

    def send(self):
        global LIB_INSTANCE

        return LIB_INSTANCE.mesibo_send_activity(self.groupid, _get_raw_string(self.peer), 
                self.presence, self.interval)

class Mesibo:
    FLAG_DELIVERYRECEIPT = 0x1
    FLAG_READRECEIPT = 0x2
    FLAG_DEFAULT = FLAG_DELIVERYRECEIPT | FLAG_READRECEIPT 

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

    def __init__(self):
        _pymesibo_lib = get_full_path_to_lib(PYMESIBO_LIB)
        _mesibo_lib = get_full_path_to_lib(MESIBO_LIB)
        global LIB_INSTANCE
        try:
            self._cpy = ctypes.cdll.LoadLibrary(_pymesibo_lib)
            LIB_INSTANCE = self._cpy
        except:
            print('Unable to load: '+ _pymesibo_lib + ' Platform not supported. Contact us at https://mesibo.com/support')
            raise

        print("mesibo Python module Version: " + __mesibo_version__)

        if(-1 == self._cpy.mesibo_init(_get_raw_string(_mesibo_lib), _get_raw_string(__mesibo_version__))):
            raise OSError('Unable to load: '+ _mesibo_lib + ' Platform not supported. Contact us at https://mesibo.com/support')

        # TBD, initialize all function arg types
        self._cpy.mesibo_e2ee_getfp.argtypes = (ctypes.c_char_p, ctypes.c_int)
        # override the default return type which is int
        self._cpy.mesibo_e2ee_getfp.restype = ctypes.c_char_p

        self._listener = None
        self._read_session = None
        self._e2ee = MesiboEndToEndEncryption(self)
        #self._set_cpu_info()

    def e2ee(self):
        return self._e2ee

    def createReadSession(self, peer, groupid, query, listener):
        return MesiboReadSession(self, peer, groupid, query, listener)

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

    def backupDatabase(self, path):
        return self._cpy.mesibo_backup_database(_get_raw_string(path), 1, 0)

    def restoreDatabase(self, path):
        return self._cpy.mesibo_backup_database(_get_raw_string(path), 0, 0)

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

    def getUniqueMessageId(self):
        return self._cpy.mesibo_msgid()

    def timestamp(self):
        return self._cpy.mesibo_timestamp()

    def sendActivity(self, params, mid, activity, interval):

        #print("sendActivity", params, mid, activity);
        return self._cpy.mesibo_send_activity(params.groupid, _get_raw_string(params.peer), activity, interval)

        def deleteMessage(self, mid): 
            return self._cpy.mesibo_delete_message(mid, None, 0);

    def deleteMessages(self, mid_list, count, del_type): 
        return self._cpy.mesibo_delete_messages(ctypes.py_object(mid_list), count, del_type);

def _get_raw_string(s):
    if(not s):
        s = ""
    return s.encode('raw_unicode_escape')
