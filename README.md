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
Building Mesibo Python module requires the following software installed:

**1. Python 3 (3.4.x or newer preferred) / Python 2 (2.7.x or newer preferred)**

Install the development packages for Python. On CentOS,Debian and derivatives (Ubuntu): `python`, `python-dev` (or python3-dev/python2-dev)

Make sure that the Python package `distutils` is installed before continuing. For example, in Debian GNU/Linux, installing python-dev also installs distutils.

#### Debian/Ubuntu
```
apt-get install libffi-dev python-dev python3-dev
```
#### Centos/RHEL/Fedora
```
yum install libffi-devel python3-devel python-devel
```

**2. Mesibo C/C++ library**

Install the shared library (On Linux based systems). For detailed instructions [refer](https://mesibo.com/documentation/install/linux/#install-using-the-convenience-script).
Mesibo Python Module is a C extension module for [mesibo C/C++ library](https://github.com/mesibo/libmesibo)
```
curl -fsSL https://raw.githubusercontent.com/mesibo/libmesibo/master/install.sh | sudo bash -
  
```

**3. Compiler**

 C/C++ compiler.GCC 4.x (and later)are recommended. 
 
```
|-- include
|-- mesibo
|-- setup.py
|-- src

```

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

To perform an in-place build that can be run from the source folder run:
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


class test_MesiboNotify(MesiboNotify):

    def __init__(self):
        pass

    def on_status(self, status, sub_status, channel, p_from):
        #You will receive the connection status here
        print("===>on_status: " + str(status) + " substatus: " +
              str(sub_status) + " channel:" + str(channel) + "from: " + str(p_from))

        return 1
        

    def on_message(self, message_params_dict, p_from, data, p_len):
        #invoked on receiving a new message or reading database messages 
        print("===>on_message: from " + str(p_from) + " of len " + str(p_len))
        print(data[:p_len])  # data buffer/Python bytes object

        print("with message parmeters:")
        print(message_params_dict)

        return 1

    def on_messagestatus(self,  message_params_dict, p_from, last):
        #Invoked when the status of outgoing or sent message is changed
        print("===>on_messagestatus: from " +
              str(p_from) + " " + str(last))
        print("with message_parameters")
        print(message_params_dict)
        return 1


#Initialisation code

#Create a Mesibo Instance
pymesibo = Mesibo() 

#Add Listener
pymesibo.set_notify(test_MesiboNotify) 

#Set your AUTH_TOKEN obtained from the Mesibo Console
pymesibo.set_accesstoken("your_auth_token") 

#Set APP_ID which you used to create AUTH_TOKEN
pymesibo.set_device(1, "my_device_id", "your_app_id", "1.0.0")

#Set the name of the database
pymesibo.set_database("mesibo.db") 

#Start mesibo
pymesibo.start() 

pymesibo.wait()

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

#Add Listener
pymesibo.set_notify(test_MesiboNotify) 

#Set your AUTH_TOKEN obtained from the Mesibo Console
pymesibo.set_accesstoken("aea59d3713701704bed9fd5952d9419ba8c4209a335e664ef2g") 

#Set APP_ID which you used to create AUTH_TOKEN
pymesibo.set_device(1, "my_device_id", "mypythonapp", "1.0.0")

#Set the name of the database
pymesibo.set_database("mesibo.db") 

#Start mesibo
pymesibo.start() 

```
Mesibo invokes various Listeners for various events.
For example, when you receive a message, receive an incoming call,etc.
MesiboNotify is a class of listeners that can be invoked to get real-time notification of events  

```python

class test_MesiboNotify(MesiboNotify):

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


**3. Sending Messages**

To send messages,you can use send_message real-time API for which you will need destination user, message id and message itself.

Invoke the following function from your code to send a text message
```python
def send_text_message(pymesibo,to,message):
        msg_params = {"id":pymesibo.random(),"expiry":3600}
        data = str(message)
        datalen = len(data)
        pymesibo.send_message(msg_params,to,data,datalen)

```
For example,Call this function from on_status to send a message when you are online.
```python
    def on_status(self, status, sub_status, channel, p_from):
        print("===>on_status: " + str(status) + " substatus: " +
              str(sub_status) + " channel:" + str(channel) + "from: " + str(p_from))
        
        if(int(status) == 1 ): #Connection is setup and you are online
            send_text_message("TestUsr","Hello from Mesibo Python"):

        return 1
```










