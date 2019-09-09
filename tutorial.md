## Tutorial on using  the Mesibo Python API

This is a simple tutorial for sending/recieving a text-message using the entirely open-source and Real-Time Mesibo Python Library. 

### OS requirements
- CentOS / RedHat 7.x or above
- Debian / Ubuntu
- Mac OS

### Prerequisites
Before you begin,
- Please ensure that you have installed the Mesibo Real-Time Python Library by referring to the installation instructions [here](https://mesibo.com/documentation/install/python/)
- Also,please go through [Get Started](https://mesibo.com/documentation/get-started/) guide to gain an understanding about Mesibo
- Refer to [Write your First mesibo Enabled Application](https://mesibo.com/documentation/tutorials/first-app/) for information on how to create users and obtain access token

Let's get Real-Time !

**1. Create your application**

- Create a new application from the [Mesibo console](https://mesibo.com/console)

- Create Users (Endpoints)

Create users from the console by clicking on ‘New User’ button from the Application settings page. Create two users  named `TestUser1` and `TestUser2` and generate  access tokens for the users with your App Id. For example,the App Id could be `my_cpp_app` .


Please refer to our tutorial [Write your First mesibo Enabled Application](https://mesibo.com/documentation/tutorials/first-app/) about creating users for more information.

We will be communicating between `TestUser1` and `TestUser2`.
Note the Auth token and the App ID for users `TestUser1` and `TestUser2`.

**2. Import mesibo API and initialise it**

Import Mesibo Python Module and Notify/Listener Module

```python
from mesibo import Mesibo
from mesiboNotify.mesiboNotify import mesiboNotify
```

Mesibo invokes various Listeners for various events.
For example, when you receive a message, receive an incoming call,etc. 
mesiboNotify is a class of listeners that can be invoked to get real-time notification of events. 

mesiboNotify is the base class definition from which test_mesiboNotify is derived from. You can override the notify class behaviour to perform as per your requirements.  

```python

MESIBO_STATUS_ONLINE  = 1
MESIBO_MSGSTATUS_SENT = 1

class test_mesiboNotify(mesiboNotify): 

    def __init__(self):
        pass

    def set_api(self,mesibo_ref):
        pymesibo = mesibo_ref

    def on_status(self, status, sub_status, channel, p_from):
        
        if(int(status) == MESIBO_STATUS_ONLINE): 
            #Connection is setup and you are online
            print("Mesibo is Online! Sending Message to TestUser2 .. ")
            send_text_message(pymesibo,"TestUser2","Hello from Mesibo Python")
        
        return 1   

    def on_message(self, message_params_dict, p_from, data, p_len):
        #invoked on receiving a new message or reading database messages
        #You will receive messages here.
       
        print("You have recieved a message!")
        print(data[:p_len])  # data buffer/Python bytes object

        return 1

    def on_messagestatus(self,  message_params_dict, p_from, last):
        #Invoked when the status of outgoing or sent message is changed
        #You will receive status of sent messages here
        
        if(message_params_dict['status']== MESIBO_MSGSTATUS_SENT):
            print("Your message has been sent!")
        return 1


```
You need to initialise Mesibo for `TestUser1`. Enter the `AUTH TOKEN` and `APP ID`
for `TestUser1` as noted in Step-2

```python
#For TestUser1
AUTH_TOKEN = "aea59d3713701704bed9fd5952d9419ba8c4209a335e664ef2e"
APP_ID = "my_cpp_app"
```
You need to pass your `AUTH_TOKEN` to the function set_credentials and your `APP_ID` to the function set_device,during initialisation.

Initialization code :
```python
pymesibo = Mesibo()
pynotify = test_mesiboNotify()
pynotify.set_api(pymesibo)

#set user authentication token obtained by creating user
pymesibo.set_accesstoken(AUTH_TOKEN)
pymesibo.set_database("mesibo.db")
pymesibo.set_notify(test_mesiboNotify) #your custom listener class
pymesibo.set_device(1, "MyUser", APP_ID, "1.0.0")

# Initialisation complete. Start Mesibo ..
pymesibo.start()
pymesibo.wait()

```

You can run the same code to initialise `TestUser2`,you just need to change the `AUTH_TOKEN` and `APP_ID` that is linked with the user `TestUser2` . 

```python
#For TestUser2
AUTH_TOKEN = "2059cdd3e60de6482b0065fc12eb03d601cce7a8c60396e8fe446db9c"
APP_ID = "my_cpp_app"
```
Initialise mesibo in your application and start it.  

**3. Sending Messages**

We will be sending a message from `TestUser1` to `TestUser2`.

To send messages,you can use send_message real-time API for which you will need destination user, message id and message itself.

Invoke the following function from your code to send a text message
```python
def send_text_message(pymesibo,to,message):
        #pymesibo is the Mesibo Python API instance. Make sure the instance is initialised before you call API functions 
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
            send_text_message(pymesibo,"TestUser2","Hello from Mesibo Python")

        return 1
```
### Complete Code
```python
from mesibo import Mesibo
from mesiboNotify.mesiboNotify import mesiboNotify

MESIBO_STATUS_ONLINE  = 1
MESIBO_MSGSTATUS_SENT = 1

class test_mesiboNotify(mesiboNotify): 

    def __init__(self):
        pass

    def set_api(self,mesibo_ref):
        pymesibo = mesibo_ref

    def on_status(self, status, sub_status, channel, p_from):
        
        if(int(status) == MESIBO_STATUS_ONLINE): 
            #Connection is setup and you are online
            print("Mesibo is Online! Sending Message to TestUser2 .. ")
            send_text_message(pymesibo,"TestUser2","Hello from Mesibo Python")
        
        return 1   

    def on_message(self, message_params_dict, p_from, data, p_len):
        #invoked on receiving a new message or reading database messages
        #You will receive messages here.
       
        print("You have recieved a message!")
        print(data[:p_len])  # data buffer/Python bytes object

        return 1

    def on_messagestatus(self,  message_params_dict, p_from, last):
        #Invoked when the status of outgoing or sent message is changed
        #You will receive status of sent messages here
        
        if(message_params_dict['status']== MESIBO_MSGSTATUS_SENT):
            print("Your message has been sent!")
        return 1

def send_text_message(pymesibo,to,message):
        #pymesibo is the Mesibo Python API instance. Make sure the instance is initialised before you call API functions 
        msg_params = {"id":pymesibo.random()}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)
        return 1

#For TestUser1
AUTH_TOKEN = "aa484354915e702c89f3e6fcb5205efd7eaade0aadad0b725bedd6db8a"
APP_ID = "my_cpp_app"


pymesibo = Mesibo()
pynotify = test_mesiboNotify()
pynotify.set_api(pymesibo)

#set user authentication token obtained by creating user
pymesibo.set_accesstoken(AUTH_TOKEN)
pymesibo.set_database("mesibo.db")
pymesibo.set_notify(test_mesiboNotify) #your custom listener class
pymesibo.set_device(1, "MyUser", APP_ID, "1.0.0")
pymesibo.start()
pymesibo.wait()



### Run the scripts

Run the files
```
python user2.py
```
Note that the Connection status for `TestUser2` is online . You can verify it from the console of your app.
Now ,you can send a message from `TestUser1` to `TestUser2`.
```
python user1.py
```

You should recieve the message "Hello from Mesibo Python" at `TestUser2` and the same should be printed out in your terminal.
