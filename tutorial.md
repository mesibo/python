---
title: Write your First mesibo Enabled Application - Python
description: Write your First mesibo Enabled Application - Python
keywords: mesibo, android, ios, cpp, python
---
{% include_relative nav.html selected="python" %}

In this part, we will create a simple real-time app using Python.

### Supported Platforms
- CentOS / RedHat 7.x or above
- Debian / Ubuntu
- Mac OS
- Raspberry Pi

### Prerequisites

You MUST go through the following prerequisites before you read further.

- Installed the Mesibo Real-Time Python Library. If not, refer installation instructions [here](/documentation/install/python/) 
- Read the [Preparation Guide](https://mesibo.com/documentation/tutorials/first-app/)

- Read the [Anatomy of a Mesibo Application](https://mesibo.com) about using the Mesibo API and listener class

- Basic knowledge of writing and running Python code


### First Python App

Now let’s quickly start coding:

From `mesibo` python package import the function class `Mesibo` and the callback class `MesiboNotify` 

```python
from mesibo import Mesibo
from mesibo import MesiboNotify
```

Now, initialize mesibo like shown below

```python
#Initialisation code

#Get auth token and app id from console 
AUTH_TOKEN = "baad7b35749832539002bbff9936130a42aaadd7b2cb0a3e664eabc"
APP_ID = "mypythonapp"

#Create a Mesibo Instance
pymesibo = Mesibo() 

#Set Listener
pymesibo.set_listener(MesiboListener)  

#Set your AUTH_TOKEN obtained from the Mesibo Console
pymesibo.set_accesstoken(AUTH_TOKEN) 

#Set APP_ID which you used to create AUTH_TOKEN
pymesibo.set_appname(APP_ID)

#Set the name of the database
pymesibo.set_database("mesibo.db") 

#Start mesibo
pymesibo.start() 

```

As explained in [Anatomy of Mesibo Application](https://mesibo.com), Mesibo invokes a class of Listeners for various events. 

Derive from the `MesiboNotify` class to implement listeners as shown below.

```python

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
```

That’s it - you are now ready to receive your first real-time message.

### Testing your Python application

1. Run your Python script 

```bash
python myfirstapp.py
```

2. `on_connectionstatus` should cycle through various status information. Finally, you should receive status=1 which indicates that your app is successfully connected to the mesibo real-time server and ready to send and receive real-time messages.

3. Since we do not have any other users right now, we will use **mesibo console** to send a test message. In a later section, we will learn how to send messages from the code itself.

- Go to **Console ->Application->Users**. You should see the user you have created.

- Go to user details by clicking the `Edit` button. Scroll down, you will see a section to `Message User`
Enter 1000 (or anything) in `From` field, check `Create This User` checkbox, type message and click on `Send`.

4. You will instantly receive this message in your console/terminal in `on_message` listener.


## Sending Messages
In the previous section, we have used mesibo console to send a message. Now we will quickly learn how to send messages from the code itself. To send messages, we will use `send_message` real-time API for which we will need destination user, message-id and the message itself.

Invoke the following function anywhere from your code to send a text message. 

```python
def send_text_message(pymesibo,to,message):
        #pymesibo is the Mesibo Python API instance. 
        #Make sure the instance is initialised before you call API functions
        
        msg_params = {"id":pymesibo.random(),"expiry":3600}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)

```

That’s it! Try it out by creating two users and send messages to each other by using the above function.
