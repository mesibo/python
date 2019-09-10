## Tutorial on using  the Mesibo Python API

In this part, we will create a simple real-time app using Python.

### OS requirements
- CentOS / RedHat 7.x or above
- Debian / Ubuntu
- Mac OS
- Raspberry Pi

### Prerequisites

You MUST go through the following prerequisites before you read further.

- Installed the Mesibo Real-Time Python Library by referring to the installation instructions 
  [here](https://mesibo.com/documentation/install/python) 

- Read the [Preparation Guide](https://mesibo.com/documentation/tutorials/first-app/)

- Read the [Anatomy of a Mesibo Application](https://mesibo.com) about using the Mesibo API and listener class

- Basic knowledge of writing and runnning Python code


### First Python App

Now let’s quickly start coding:

From `mesibo` python package import the function class `Mesibo` and the callback class`mesiboNotify` 

```python
from mesibo import Mesibo 
from mesiboNotify.mesiboNotify import mesiboNotify
```

Now, initialize mesibo like shown below
```python
#Create Mesibo Instance
pymesibo = Mesibo()

pynotify = test_mesiboNotify() 
pynotify.set_api(pymesibo)

#set user authentication token obtained by creating user from console
pymesibo.set_accesstoken("aea59d3713701704bed9fd5952d9419ba8c4209a335e664ef2g")
pymesibo.set_database("mesibo.db")
pymesibo.set_notify(test_mesiboNotify) #your custom listener class
pymesibo.set_device(1, "MyUser", "mypythonapp", "1.0.0")

# Initialisation complete. Start Mesibo ..
pymesibo.start()
pymesibo.wait()

```

As explained in [Anatomy of Mesibo Application](https://mesibo.com), Mesibo invokes a class of Listeners for various events. 

Derive from the `mesiboNotify` class to implement listeners as shown below.


```python

class test_mesiboNotify(mesiboNotify): 

    def __init__(self):
        pass
    
    def set_api(self,mesibo_ref):
        pymesibo = mesibo_ref
    
    def on_status(self, status, sub_status, channel, p_from):
        #You will receive the connection status here
        
        print("===>on_status: " + str(status) + " substatus: " +
              str(sub_status) + " channel:" + str(channel) + "from: " + str(p_from))
        
        return 0

    def on_message(self, message_params_dict, p_from, data, p_len):
        #Invoked on receiving a new message or reading database messages
        #You will receive messages here.
       
        print("You have recieved a message!")
        print(data[:p_len])  # data buffer/Python bytes object

        return 0

    def on_messagestatus(self,  message_params_dict, p_from, last):
        #Invoked when the status of outgoing or sent message is changed
        #You will receive status of sent messages here
        
        print("===>on_messagestatus: from " +
              str(p_from) + " " + str(last))
        print("with message_parameters")
        print(message_params_dict)

        return 0


```
That’s it - you are now ready to receive your first real-time message.

## Testing your Python application
1. Run your Python script 

```bash
python myfirstapp.py
```

2. `on_status` should cycle through various status information. Finally, you should receive status=1 which indicates that your app is successfully connected to the mesibo real-time server and ready to send and receive real-time messages.

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
        msg_params = {"id":pymesibo.random()}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)

```
Call this function from `on_status` to send a message when you are online.
```python
    def on_status(self, status, sub_status, channel, p_from):
        print("===>on_status: " + str(status) + " substatus: " +
              str(sub_status) + " channel:" + str(channel) + "from: " + str(p_from))
        
        if(int(status) == 1 ): #Connection is setup and you are online
            send_text_message(pymesibo,"TestUser","Hello from Mesibo Python. I am Online!")

        return 1
```
That’s it! Try it out by creating two users and send messages to each other by using the above function.
