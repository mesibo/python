## Mesibo Python API  [ BETA ]

This repo contains the source code for Mesibo Real-Time Python API. Mesibo Python library is still **under-development**. However, it is completely functional. 

### What is Mesibo?
Mesibo offers everything to make your app real-time and scalable for your first billion users and the next. It's modular, lightweight, and easy to integrate.

Mesibo supports almost all popular platforms and languages for you to quickly build your applications. Whether you are developing mobile apps (Android, iOS, Java, Objective-C, C++), web apps (Javascript), integrating with backend (Linux, macOS, Windows, Python, C++), or creating cool devices using Raspberry Pi, Mesibo has APIs for you.

Mesibo's high-performance C++ and Python libraries enable you to interface your chat clients with various scientific computing and machine learning systems on your backend like TensorFlow, Matlab, Octave, NumPy, etc to create a powerful chat experience.


- **Website:** https://mesibo.com
- **Documentation:** https://mesibo.com/documentation/

### Supported Platforms
- CentOS / RedHat 7.x or above
- Debian / Ubuntu
- Mac OS
- Raspberry Pi

## Requirements
Mesibo Python API is an entirely open-source real-time library that can be built and installed from source. Building the Mesibo Python Package requires the following software installed:

**1. Python 3 (3.4.x or newer preferred) / Python 2 (2.7.x or newer preferred)**

Install the development packages for Python: `python` and `python-dev`
Make sure that the Python package `setuptools` is installed before continuing. 

#### Debian/Ubuntu
```
sudo apt-get install libffi-dev python python-dev
```
#### Centos/RHEL/Fedora
```
sudo yum install libffi-devel python python-devel 
```

**2. Compiler**

Mesibo Python Library uses [Mesibo C/C++ SDK](https://mesibo.com/documentation/install/linux/). Hence, it has to be compiled before installing the package. GCC 4.x (and later)are recommended. 


## Installing Mesibo Python Library

Download the source files from [ Mesibo Python repo on GitHub](https://github.com/mesibo/python)
```
git clone https://github.com/mesibo/python.git
```
You will find the following directory structure:
```
|-- include
|-- mesibo
|-- setup.py
|-- src

```

To build and install the Mesibo Python Package from source
```
sudo python setup.py install
```
The entire module is built and installed automatically by copying files from the generated build folder into the lib directory path of your Python installation.

If you prefer not to install it automatically, you can perform an in-place build from the source directory:
```
python setup.py build_ext --inplace
```

Once you have installed Mesibo Python Library successfully, you should be able to import the Mesibo module in Python as follows:
```python
from mesibo import Mesibo
from mesibo import MesiboNotify
```

## API Usage
```python
from mesibo import Mesibo
from mesibo import MesiboNotify

#Mesibo invokes various Listeners for various events.
#For example, when you receive a message, receive an incoming call, etc
#MesiboNotify is a class of listeners that can be invoked to get real-time notification of events  

class MesiboListener(MesiboNotify):

    def on_connectionstatus(self, status):
        """A status = 1 means the listener successfully connected to the Mesibo server
        """
        print(f"## Connection status: {status}")
        return 0

    def on_message(self, msg_params, data, datalen):
        """Invoked on receiving a new message or reading database messages
        """
        print(f"## Received message from {msg_params['peer']}: {data} of len {datalen}")
        print(msg_params)
        print("Message: ", data[: datalen].decode('utf-8'))
        return 0

    def on_messagestatus(self, msg_params):
        """Invoked when the status of an outgoing or sent message is changed. Statuses can be
        sent, delivered, or read
        """
        print(f"## Outgoing msg. To: {msg_params['peer']}, Status: {msg_params['status']}")
        return 0


def send_text_message(to, message):
    #pymesibo is the Mesibo Python API instance. 
    #Make sure the instance is initialised before you call API functions
    p = {}
    p['peer'] = to
    data = message
    pymesibo.send_message(p, pymesibo.random(), data)

#Initialisation code

#Create a Mesibo Instance
pymesibo = Mesibo() 

#Set Listener
pymesibo.set_listener(MesiboListener)  
#Set your AUTH_TOKEN obtained from the Mesibo Console
pymesibo.set_accesstoken("your_auth_token") 
#Set APP_ID which you used to create AUTH_TOKEN
pymesibo.set_appname("your_app_id")
#Set the name of the database
pymesibo.set_database("mesibo.db") 

#Start mesibo
pymesibo.start() 

#Wait for the application to exit, Press Ctrl+Z to exit
pymesibo.wait()

```

For documentation and tutorials [refer](https://mesibo.com/documentation/)

## Let's get Real-Time!

This is a simple tutorial for sending/receiving a text-message using Mesibo python API.
Before you begin please go through [Get Started](https://mesibo.com/documentation/get-started/) guide.
Read the  [Preparation Guide](https://mesibo.com/documentation/tutorials/first-app/) and [Anatomy of a Mesibo Application](https://mesibo.com/documentation/tutorials/first-app/anatomy/)

### Import Mesibo and initialize it

From `mesibo` Python Package import the function class `Mesibo` and the callback class `MesiboNotify`

```python
from mesibo import Mesibo
from mesibo import MesiboNotify
```

Now, initialize mesibo like shown below :

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

#Wait for the application to exit, Press Ctrl+Z to exit
pymesibo.wait()

```
Mesibo invokes various Listeners for various events.
For example, when you receive a message, receive an incoming call, etc.
MesiboNotify is a class of listeners that can be invoked to get real-time notification of events. You can derive your `MesiboListener` class from the base class `MesiboNotify` like below 

```python

class MesiboListener(MesiboNotify):

    def on_connectionstatus(self, status):
        """A status = 1 means the listener successfully connected to the Mesibo server
        """
        print(f"## Connection status: {status}")
        return 0

    def on_message(self, msg_params, data, datalen):
        """Invoked on receiving a new message or reading database messages
        """
        print(f"## Received message from {msg_params['peer']}: {data} of len {datalen}")
        print(msg_params)
        print("Message: ", data[: datalen].decode('utf-8'))
        return 0

    def on_messagestatus(self, msg_params):
        """Invoked when the status of an outgoing or sent message is changed. Statuses can be
        sent, delivered, or read
        """
        print(f"## Outgoing msg. To: {msg_params['peer']}, Status: {msg_params['status']}")
        return 0
                   
```
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


### Sending Messages

To send messages, you can use `send_message` real-time API for which you will need destination user, message-id, and the message itself.

Invoke the following function from your code to send a message
```python
def send_text_message(to, message):
    #pymesibo is the Mesibo Python API instance. 
    #Make sure the instance is initialised before you call API functions
    p = {}
    p['peer'] = to
    data = message
    pymesibo.send_message(p, pymesibo.random(), data)
```
### Creating a chatbot
For example, you may be creating a chatbot and want to send an automated reply back to the user as follows:
```python
    def on_message(self, msg_params, data, datalen):
        """Invoked on receiving a new message or reading database messages
        """
        print(f"## Received message from {msg_params['peer']}: {data} of len {datalen}")
        print("Message: ", data[: datalen].decode('utf-8'))
        
        send_text_message(msg_params['peer'], "I got your message! Please wait..");
        #Now you can process the message(data) and send an appropriate response later
        
	return 0
```


That’s it! Try it out by creating two users and send messages to each other by using the above function.





