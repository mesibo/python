#!/usr/bin/python3
 
# first-app.py
#
# Usage:
# Install mesibo python package from https://github.com/mesibo/python
# Create an application at https://mesibo.com/console
# Create a user and Obtain the token and app id for the user and set it
# Run the script 
#
# $ python3 first-app.py
#
# Send a message from console to the user. It should be received and printed by your python script
# Use Ctrl+Z or pkill to stop the script
#
# Refer to https://mesibo.com/documentation/tutorials/get-started/ to learn more

from mesibo import Mesibo
from mesibo import MesiboListener

class PyMesiboListener(MesiboListener):

    def Mesibo_OnConnectionStatus(self, status):
        """A status = 1 means the listener 
        successfully connected to the mesibo server
        """
        print("## Mesibo_OnConnectionStatus: ", status)
        return 0

    def Mesibo_OnMessage(self, msg_params, data):
        """Invoked on receiving a new message 
        or reading database messages
        data: bytearray 
        """
        message = None
        try:
            # try to decode string
            message = data.decode(encoding="utf-8", errors="strict") 
            print("\n ## Received message:", message)
        except:
            pass
        
        print("\n ## Mesibo_OnMessage: ", msg_params)
        print("## Received Data: \n", data)
        # handle: integer, bytes, etc

        return 0

    def Mesibo_OnMessageStatus(self, msg_params):
        """Invoked when the status 
        of an outgoing or sent message is changed. msg_params.status can be
        sent, delivered, or read
        """
        print("## Mesibo_OnMessageStatus", msg_params)
        return 0

    def Mesibo_OnActivity(self, msg_params, activity):
        print("## Mesibo_OnActivity", msg_params, activity)
        return 0
    
    def Mesibo_OnRichMessage(self, msg_params, message):
        print("## Mesibo_OnRichMessage", msg_params, message)
        return 0 

def send_text_message(api, address, message):
    params = Mesibo.MessageParams()
    params.peer = address
    params.flag = Mesibo.FLAG_READRECEIPT | Mesibo.FLAG_DELIVERYRECEIPT
    mid = api.random()
    api.sendMessage(params, mid, message)

# Get access token and app id by creating a mesibo user
# See https://mesibo.com/documentation/tutorials/get-started/
ACCESS_TOKEN = "<use your user token>"
APP_ID = "com.mesibo.python"

# Create a Mesibo Instance
api = Mesibo()

# Enable or disable End-to-end-encryption
e2ee = api.e2ee();
e2ee.enable(1)

# Set Listener
listener = PyMesiboListener()
api.addListener(listener)

# Set your AUTH_TOKEN obtained while creating the user 
if(Mesibo.RESULT_FAIL == api.setAccessToken(ACCESS_TOKEN)):
    print("===> Invalid ACCESS_TOKEN: ", ACCESS_TOKEN)
    print("See https://mesibo.com/documentation/tutorials/get-started/")
    exit(1) 

# Set APP_ID which you used to create AUTH_TOKEN
api.setAppName(APP_ID)

# Set the name of the database
api.setDatabase("mesibo.db")

# Start mesibo, 
api.start()

send_text_message(api, "456", "Hello from Python!")

#Wait for the application to exit
api.wait()

