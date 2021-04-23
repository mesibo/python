#!/usr/bin/python3
 
# first-app.py

from mesibo import Mesibo
from mesibo import MesiboListener

class MesiboReadListener(MesiboListener):
    def mesibo_on_message(self, msg_params, data):
        """Invoked on receiving a new message 
        or reading database messages
        data: python byte array 
        """
        print('---------')
        print("## on_message: ", msg_params)
        print("## Data: ", data)
        print('---------')
        return 0

api = Mesibo()

# Set the name of the database
if(Mesibo.RESULT_FAIL == api.set_database("mesibo-241095.db")):
    print("Unable to set database")
    exit(1)

# Create listener through which you will be notified of messages read
listener = MesiboReadListener()

# If you have not called add_listener before, pass a listener to read session 

# Create Read Session to read messages 
# from user with address "678" 
rs = api.ReadDbSession("678", 0, None, listener);
rs.enable_read_receipt(True)
count = rs.read(10)
print("read returned ", count)

# Create Read Session in summary mode
# Summmay mode = read the last message from each user 
rs = api.ReadDbSession(None, 0, None, listener)
rs.enable_summary(True)
count = rs.read(10)
print("read returned ", count)
# Create Read Session to read summary
rs = api.ReadDbSession(None, 0, None, listener)

