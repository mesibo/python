#!/usr/bin/python3
 
#reading-messages.py

from mesibo import Mesibo
from mesibo import MesiboListener

class MesiboReadListener(MesiboListener):
    def Mesibo_OnMessage(self, msg_params, data):
        """Invoked on receiving a new message 
        or reading database messages
        data: python byte array 
        """
        print("## Mesibo_OnMessage: ", msg_params)
        print("## data: ", data)
        return 0

api = Mesibo()

# Set the name of the database
if(Mesibo.RESULT_FAIL == api.setDatabase("mesibo-241095.db")):
    print("Unable to set database")
    exit(1)

# Create listener through which you will be notified of messages read
listener = MesiboReadListener()

# If you have not called add_listener before, pass a listener to read session 

# Create Read Session to read messages 
# from user with address "678" 
rs = api.ReadDbSession("456", 0, None, listener);
rs.enableReadReceipt(True)
count = rs.read(10)
print("read returned ", count)

# Create Read Session in summary mode
# Summmay mode = read the last message from each user 
rs = api.ReadDbSession(None, 0, None, listener)
rs.enableSummary(True)
count = rs.read(10)
print("read returned ", count)
# Create Read Session to read summary
rs = api.ReadDbSession(None, 0, None, listener)

