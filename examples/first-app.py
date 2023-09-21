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
from mesibo import MesiboMessage
from mesibo import MesiboListener

class PyMesiboListener(MesiboListener):

    def Mesibo_onConnectionStatus(self, status):
        """A status = 1 means the listener 
        successfully connected to the mesibo server
        """
        print("## Mesibo_onConnectionStatus: ", status)
        return 0

    def Mesibo_onMessage(self, msg):
        """Invoked on receiving a new message 
        or reading database messages
        msg: Message Object 
        """
        try:
            # try to decode string
            message = msg.message.decode(encoding="utf-8", errors="strict") 
            print("\n ## Received message:", message)
        except:
            pass
        
        print("\n ## Mesibo_onMessage: ", msg)
        # handle: integer, bytes, etc

        return 0

    def Mesibo_onMessageUpdate(self, msg):
        """Invoked on receiving a message update
        """
        print("\n ## Mesibo_onMessageUpdate: ", msg)
        return 0

    def Mesibo_onMessageStatus(self, msg):
        """Invoked when the status 
        of an outgoing or sent message is changed.
        """
        print("## Mesibo_onMessageStatus", msg)
        return 0

    def Mesibo_onPresence(self, msg):
        print("## Mesibo_onPresence", msg)
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

input("Press Enter to send a message...\n")
msg = MesiboMessage("destination")
msg.title = "Hello"
msg.message = "Hello message"
#msg.setContent("pic1.jpg")
#msg.setContent("https://mesibo.com")
msg.send()

#e2ee.getPublicCertificate("/root/pycert.cert")
#print("fingerPrint: " + e2ee.getFingerprint("destination"))

#Wait for the application to exit
api.wait()

