#!/usr/bin/python3
 
# first-app.py
#
# Usage:
# Install mesibo python package from https://github.com/mesibo/python
# Create an application at https://mesibo.com/console
# Create a user and Obtain the token and app id for the user and set it
# Run the script 
#
# python first-app.py
#
# Send a message from console to the user. It should be received and printed by your python script
# Use Ctrl+Z or pkill to stop the script
#
# Refer to https://mesibo.com/documentation/tutorials/get-started/ to learn more

from mesibo import Mesibo
from mesibo import MesiboListener

class PyMesiboListener(MesiboListener):

    def mesibo_on_connectionstatus(self, status):
        """A status = 1 means the listener 
        successfully connected to the mesibo server
        """
        print("## Connection status: ", status)
        return 0

    def mesibo_on_message(self, msg_params, data):
        """Invoked on receiving a new message 
        or reading database messages
        data: python byte array 
        """
        message = None
        try:
            # try to decode string
            message = data.decode(encoding="utf-8", errors="strict") 
            print("\n ## Received message:", message)
        except:
            pass
        
        print("\n ## on_message: ", msg_params)
        print("## Received Data: \n", data)
        # handle: integer, bytes, etc

        return 0

    def mesibo_on_messagestatus(self, msg_params):
        """Invoked when the status 
        of an outgoing or sent message is changed. msg_params.status can be
        sent, delivered, or read
        """
        print("## on_messagestatus", msg_params)
        return 0

    def mesibo_on_activity(self, msg_params, activity):
        print("## on_activity", msg_params, activity)
        return 0
    
    def mesibo_on_file(self, msg_params, file_params):
        print("## on_file", msg_params, file_params)
        return 0 

def send_one_to_one_message(mesibo_api, destination_address, message):
    params = Mesibo.MessageParams()
    params.peer = destination_address
    params.flag = Mesibo.FLAG_READRECEIPT | Mesibo.FLAG_DELIVERYRECEIPT
    mid = api.random()
    mesibo_api.send_message(params, mid, message)

# Get access token and app id by creating a mesibo user
# See https://mesibo.com/documentation/tutorials/get-started/
ACCESS_TOKEN = "xxxx"
APP_ID = "xxxx"

# Create a Mesibo Instance
api = Mesibo()

# Set Listener
listener = PyMesiboListener()
api.add_listener(listener)

# Set your AUTH_TOKEN obtained while creating the user 
if(Mesibo.RESULT_FAIL == api.set_accesstoken(ACCESS_TOKEN)):
    print("===> Invalid ACCESS_TOKEN: ", ACCESS_TOKEN)
    print("See https://mesibo.com/documentation/tutorials/get-started/")
    exit(1) 

# Set APP_ID which you used to create AUTH_TOKEN
api.set_appname(APP_ID)

# Set the name of the database
api.set_database("mesibo.db")

# Start mesibo, 
api.start()

send_one_to_one_message(api, "456", "Hello from Python!")

#Wait for the application to exit
api.wait()

