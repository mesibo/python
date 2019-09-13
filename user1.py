

from mesibo import Mesibo
from mesibo import MesiboNotify


class MesiboListener(MesiboNotify):

    def __init__(self):
        pass

    def on_connectionstatus(self, status):
        print("===>on_connectionstatus: " + str(status))
        return 1


    def on_message(self, message_params, p_from, data, p_len):
        #invoked on receiving a new message or reading database messages
        print("===>on_message: from " + str(p_from) + " of len " + str(p_len))
        print(data[:p_len])  # data buffer/Python bytes object

        print("with message parmeters:")
        print(message_params)

        return 1

    def on_messagestatus(self, message_params, p_from):
        #Invoked when the status of outgoing or sent message is changed
        print("===>on_messagestatus: from " +
              str(p_from))
        print("with message_parameters")
        print(message_params)
        return 1

def send_text_message(pymesibo,to,message):
        #pymesibo is the Mesibo Python API instance. Make sure the instance is initialised before you call API functions 
        msg_params = {"id":pymesibo.random(),"expiry":3600}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)
        return 1


AUTH_TOKEN = "baad7b35749832539002bbff9936130a42aaadd7b2cb0a3e664ef1f"
APP_ID = "dialogflowmesibo"

#Create Mesibo Instance
pymesibo = Mesibo()
pymesibo.set_listener(MesiboListener) #your custom listener class
pymesibo.set_accesstoken(AUTH_TOKEN) #set user authentication token obtained by creating user
pymesibo.set_database("mesibo.db")
pymesibo.set_appname(APP_ID)
pymesibo.start()
send_text_message(pymesibo,"Nagendra","Hi from Mesibo Python");

#try:
 #   while True :
  #      pass
#except KeyboardInterrupt:
 #   pass


while(1):
    pass
