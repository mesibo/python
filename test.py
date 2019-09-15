

from mesibo import Mesibo
from mesibo import MesiboNotify

MESIBO_FLAG_DELIVERYRECEIPT = 0x1
MESIBO_FLAG_READRECEIPT     = 0x2

class MesiboListener(MesiboNotify):

    def __init__(self):
        pass

    def on_connectionstatus(self, status):
        print("===>on_connectionstatus: " + str(status))
        return 1


    def on_message(self, message_params,data):
        #invoked on receiving a new message or reading database messages
        print("===>on_message: from " + str(message_params['peer'])) 
        print(data) 
        return 1

    def on_messagestatus(self, message_params):
        #Invoked when the status of outgoing or sent message is changed
        print("===>on_messagestatus: from " + str(message_params['peer'])+ " status "+ str(message_params['status']))
        return 1



AUTH_TOKEN = "9f079c04b6bdb9d7253be331240f2d33780e97bbe4387e8e557933c"
APP_ID = "myfirstapp"

#Create Mesibo Instance
api = Mesibo()
api.set_listener(MesiboListener) #your custom listener class
api.set_accesstoken(AUTH_TOKEN) #set user authentication token obtained by creating user
api.set_database("mesibo.db")
api.set_appname(APP_ID)

def send_text_message(to,message):
        #api is the Mesibo Python API instance. Make sure the instance is initialised before you call API functions
        p = {}
        p['peer'] = to
        p['expiry] = 3600
        p['flag'] = MESIBO_FLAG_DELIVERYRECEIPT | MESIBO_FLAG_READRECEIPT
        data = str(message)
        api.send_message(p,api.random(),data)

api.start()
send_text_message("917019882153","Hi from Mesibo Python");



while(1):
    pass



