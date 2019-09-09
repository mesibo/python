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

Create users from the console by clicking on ‘New User’ button from the Application settings page. Create two users  named `TestUser1` and `TestUser2` and generate  access tokens for the users with your App Id.For example,the App Id could be `my_cpp_app` .


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
mesiboNotify is a class of listeners that can be invoked to get real-time notification of events.mesiboNotify is the base class definition from which test_mesiboNotify is derived from. You can override the notify class behaviour to perform as per your requirements.  

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
#set user authentication token obtained by creating user
pymesibo.set_accesstoken(AUTH_TOKEN) 
pymesibo.set_database("mesibo.db")
pymesibo.set_notify(test_mesiboNotify) #your custom listener class
pymesibo.set_device(1, "MyUser", APP_ID, "1.0.0") 
pymesibo.start()
pymesibo.wait() 
```

You can run the same code to initialise `TestUser2`,you just need to change the `AUTH_TOKEN` and `APP_ID` that is linked with the user `TestUser2` . 

```python
#For TestUser2
AUTH_TOKEN = "2059cdd3e60de6482b0065fc12eb03d601cce7a8c60396e8fe446db9c"
APP_ID = "my_cpp_app"
```

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
            send_text_message("TestUser2","Hello from Mesibo Python"):

        return 1
```

