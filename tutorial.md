## Tutorial on using  the Mesibo Python API

This is a simple tutorial for sending/recieving a text-message using the open-source and Real-Time Mesibo Python Library. 

### Prerequisites
Before you begin,
- Please ensure that you have installed the Mesibo Real-Time Python Library by referring to the installation instructions [here](https://mesibo.com/documentation/install/python/)
- Also,please go through [Get Started](https://mesibo.com/documentation/get-started/) guide to gain an understanding about Mesibo
- Refer [Write your First mesibo Enabled Application](https://mesibo.com/documentation/tutorials/first-app/)

Let's get Real-Time !

**1. Create your application**

Create a new application from the [Mesibo console](https://mesibo.com/console)
Once your application is created, note down the App token. The App Token looks like following:
```
**cn9cvk6gnm15e7lrjb2k7ggggax5h90n5x7dp4sam6kwitl2hmg4cmwabet4zgdw**
```
Create Users (Endpoints)

Create users from the console by clicking on ‘New User’ button from the Application settings page.
Note the user Address 


**2. Import mesibo API and initialise it**

Import Mesibo Python Module and Notify/Listener Module

```python
from mesibo import Mesibo
from mesiboNotify.mesiboNotify import mesiboNotify
```

Mesibo invokes various Listeners for various events.
For example, when you receive a message, receive an incoming call,etc.
mesiboNotify is a class of listeners that can be invoked to get real-time notification of events  

```python

class test_mesiboNotify(mesiboNotify):

    def __init__(self):
        pass

    def on_status(self, status, sub_status, channel, p_from):
        #You will receive the connection status here
        print("===>on_status: " + str(status) + " substatus: " +
              str(sub_status) + " channel:" + str(channel) + "from: " + str(p_from))
        
        return 1
        

    def on_message(self, message_params_dict, p_from, data, p_len):
        #invoked on receiving a new message or reading database messages
        #You will receive messages here.
        print("===>on_message: from " + str(p_from) + " of len " + str(p_len))
        print(data[:p_len])  # data buffer/Python bytes object
        print(str(data[:p_len], encoding='utf-8', errors='strict'))

        print("with message parmeters:")
        print(message_params_dict)

        return 1

    def on_messagestatus(self,  message_params_dict, p_from, last):
        #Invoked when the status of outgoing or sent message is changed
        #You will receive status of sent messages here
        print("===>on_messagestatus: from " +
              str(p_from) + " " + str(last))
        print("with message_parameters")
        print(message_params_dict)
        return 1


```
Initialization code :
```python
pymesibo = Mesibo()
#set user authentication token obtained by creating user
pymesibo.set_accesstoken("cn9cvk6gnm15e7lrjb2k7ggggax5h90n5x7dp4sam6kwitl2hmg4cmwabet4zgdw") 
pymesibo.set_database("mesibo.db")
pymesibo.set_notify(test_mesiboNotify) #your custom listener class
pymesibo.set_device(1, "MyUser", "MyAppName", "1.0.0") 
pymesibo.start()
pymesibo.wait() 
```

**3. Sending Messages**

To send messages,you can use send_message real-time API for which you will need destination user, message id and message itself.

Invoke the following function from your code to send a text message
```python
def send_text_message(to,message):
        pymesibo = Mesibo() #Instantiate Mesibo(Singleton already initialised)
        msg_params = {"id":pymesibo.random()}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)

```
Call this function from on_status to send a message when you are online.
```python
    def on_status(self, status, sub_status, channel, p_from):
        print("===>on_status: " + str(status) + " substatus: " +
              str(sub_status) + " channel:" + str(channel) + "from: " + str(p_from))
        
        if(int(status) == 1 ): #Connection is setup and you are online
            #The destination address can even be a phone number like "91xxxxxxxxxx"
            send_text_message("TestUsr","Hello World! Mesibo is online"):

        return 1
```

