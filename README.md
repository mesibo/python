## Mesibo Python API  [ BETA ]

This repo contains the source code for Mesibo Real-Time Python API. Mesibo Python library is still **under-development**. However, it is completely functional. 

### What is Mesibo?
Mesibo offers everything to make your app real-time and scalable for your first billion users and the next. It's modular, lightweight and easy to integrate.

Mesibo supports almost all popular platforms and languages for you to quickly build your applications. Whether you are developing mobile apps (Android, iOS, Java, Objective-C, C++), web apps (Javascript), integrating with backend (Linux, MacOS, Windows, Python, C++) or creating cool devices using Raspberry Pi, Mesibo has APIs for you.

Mesibo's high performance C++ and Python libraries enable you to interface your chat clients with various scientific computing and machine learning systems on your backend like TensorFlow, Matlab, Octave, NumPy etc to create a powerful chat experience.


- **Website:** https://mesibo.com
- **Documentation:** https://mesibo.com/documentation/

### Supported Platforms
- CentOS / RedHat 7.x or above
- Debian / Ubuntu
- Mac OS
- Raspberry Pi

## Requirements
Mesibo Python API is an entirely open-source real-time library which can be built and installed from source. Building Mesibo Python Package requires the following software installed:

**1. Python 3 (3.4.x or newer preferred) / Python 2 (2.7.x or newer preferred)**

Install the development packages for Python : `python` and `python-dev`

Make sure that the Python package `distutils` is installed before continuing. For example, in Debian GNU/Linux, installing python-dev also installs distutils.

#### Debian/Ubuntu
```
sudo apt-get install libffi-dev python python-dev
```
#### Centos/RHEL/Fedora
```
sudo yum install libffi-devel python python-devel 
```

**2. Compiler**

Mesibo Python Library uses [Mesibo C/C++ SDK](https://mesibo.com/documentation/install/linux/). Hence, it has to compiled before installing the package. GCC 4.x (and later)are recommended. 


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

## API Usage
```python
from mesibo import Mesibo
from mesibo import MesiboNotify

#Mesibo invokes various Listeners for various events.
#For example, when you receive a message, receive an incoming call etc
#MesiboNotify is a class of listeners that can be invoked to get real-time notification of events  


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
        

def send_text_message(pymesibo,to,message):
        #pymesibo is the Mesibo Python API instance. Make sure the instance is initialised before you call API functions 
        msg_params = {"id":pymesibo.random(),"expiry":3600}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)
        return 1


#Initialisation code

#Create a Mesibo Instance
pymesibo = Mesibo() 

#Set Listener
pymesibo.set_listener(MesiboListener)  

#Set your AUTH_TOKEN obtained from the Mesibo Console
pymesibo.set_accesstoken("your_auth_token") 

#Set APP_ID which you used to create AUTH_TOKEN
pymesibo.set_appname(APP_ID)

#Set the name of the database
pymesibo.set_database("mesibo.db") 

#Start mesibo
pymesibo.start() 

```

For documentation and tutorials [refer](https://mesibo.com/documentation/)

## Let's get Real-Time!

This is a simple tutorial for sending/recieving a text-message using Mesibo python API.
Before you begin please go through [Get Started](https://mesibo.com/documentation/get-started/) guide.
Read the  [Preparation Guide](https://mesibo.com/documentation/tutorials/first-app/) and [Anatomy of a Mesibo Application](https://mesibo.com/documentation/tutorials/first-app/anatomy/)



**1. Import mesibo API and initialise it**

From mesibo python package import the function class `Mesibo` and the callback class `MesiboNotify`

```python
from mesibo import Mesibo
from mesibo import MesiboNotify
```

Now, initialize mesibo like shown below :
```python
#Initialisation code

#Create a Mesibo Instance
pymesibo = Mesibo() 

#Set Listener
pymesibo.set_listener(MesiboListener)  

#Set your AUTH_TOKEN obtained from the Mesibo Console
pymesibo.set_accesstoken("aea59d3713701704bed9fd5952d9419ba8c4209a335e664ef2g") 

#Set APP_ID which you used to create AUTH_TOKEN
pymesibo.set_appname(APP_ID)

#Set the name of the database
pymesibo.set_database("mesibo.db") 

#Start mesibo
pymesibo.start() 

```
Mesibo invokes various Listeners for various events.
For example, when you receive a message, receive an incoming call,etc.
MesiboNotify is a class of listeners that can be invoked to get real-time notification of events. You can derive your `MesiboListener` class from the base class `MesiboNotify` like below 

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
## Testing your Python application

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


**3. Sending Messages**

To send messages,you can use `send_message` real-time API for which you will need destination user, message id and message itself.

Invoke the following function from your code to send a message
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









