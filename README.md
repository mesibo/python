## mesibo Python Package 

mesibo offers everything to make your app real-time and scalable. It's modular, lightweight, and easy to integrate.

mesibo supports almost all popular platforms and languages for you to quickly build your applications. Whether you are developing mobile apps (Android, iOS, Java, Objective-C, C++), web apps (Javascript), integrating with backend (Linux, macOS, Windows, Python, C++), or creating cool devices using Raspberry Pi, mesibo has APIs for you.

mesibo's high-performance Python library enables you to interface your chat clients with various scientific computing and machine learning systems on your backend like TensorFlow, Matlab, Octave, NumPy, etc to create a powerful chat experience.

- **Website:** https://mesibo.com
- **Documentation:** https://mesibo.com/documentation/
- **Tutorials:** https://mesibo.com/documentation/tutorials/get-started

### Supported Platforms
Mesibo Python Package is still under-development and supports the following platforms. However, it is completely functional.
- CentOS / RedHat 7.x or above
- Debian / Ubuntu
- Mac OS (In Progress)
- Raspberry Pi (In Progress)

## Example
Below are some examples of typical usage. For more examples, see the [examples](https://github.com/mesibo/python/tree/master/examples) directory on the GitHub repo.

### Sending and Receiving Messages
```python
from mesibo import Mesibo
from mesibo import MesiboListener

class PyMesiboListener(MesiboListener):

    def Mesibo_OnConnectionStatus(self, status):
        """A status = 1 means the listener 
        successfully connected to the mesibo server
        """
        print("## Mesibo_OnConnectionStatus: ", status)
        return 0

    def Mesibo_OnMessage(self, msg_params, data):
        """Invoked on receiving a new message 
        or reading database messages
        data: bytearray 
        """
        message = None
        try:
            # try to decode string
            message = data.decode(encoding="utf-8", errors="strict") 
            print("\n ## Received message:", message)
        except:
            pass
        
        print("\n ## Mesibo_OnMessage: ", msg_params)
        print("## Received Data: \n", data)
        # handle: integer, bytes, etc

        return 0

    def Mesibo_OnMessageStatus(self, msg_params):
        """Invoked when the status 
        of an outgoing or sent message is changed. msg_params.status can be
        sent, delivered, or read
        """
        print("## Mesibo_OnMessageStatus", msg_params)
        return 0

    def Mesibo_OnActivity(self, msg_params, activity):
        print("## on_activity", msg_params, activity)
        return 0
    
    def Mesibo_OnFile(self, msg_params, file_params):
        print("## on_file", msg_params, file_params)
        return 0 

def send_text_message(api, address, message):
    params = Mesibo.MessageParams()
    params.peer = address
    params.flag = Mesibo.FLAG_READRECEIPT | Mesibo.FLAG_DELIVERYRECEIPT
    mid = api.random()
    api.sendMessage(params, mid, message)

# Get access token and app id by creating a mesibo user
# See https://mesibo.com/documentation/tutorials/get-started/
ACCESS_TOKEN = "xxxx"
APP_ID = "xxxx"

# Create a Mesibo Instance
api = Mesibo()

# Set Listener
listener = PyMesiboListener()
api.addListener(listener)

# Set your AUTH_TOKEN obtained while creating the user 
if(Mesibo.RESULT_FAIL == api.setAccessToken(ACCESS_TOKEN)):
    print("===> Invalid ACCESS_TOKEN: ", ACCESS_TOKEN)
    print("See https://mesibo.com/documentation/tutorials/get-started/")
    exit(1) 

# Set APP_ID which you used to create AUTH_TOKEN
api.setAppName(APP_ID)

# Set the name of the database
api.setDatabase("mesibo.db")

# Start mesibo, 
api.start()

send_text_message(api, "456", "Hello from Python!")

#Wait for the application to exit
api.wait()
```

## Installing using pip
See [requirements](https://mesibo.com/documentation/install/python/#requirements) to learn about installation requirements before you continue.
```
$ sudo python -m pip install mesibo
```

## Installing from source
Alternatively, you can build and install the package by downloading the source code from the GitHub repo.

Download the source files from [mesibo Python repo on GitHub](https://github.com/mesibo/python)
```
git clone https://github.com/mesibo/python.git
```
You will find the following directory structure:
```
|-- examples 
|-- setup.py
|-- src
```

To build the mesibo Python package from source
```
sudo python setup.py build 
```

To build and install the mesibo Python package from source
```
sudo python setup.py install
```

## Tutorial
[Write your First mesibo Enabled Application - Python](https://mesibo.com/documentation/tutorials/get-started/python)

## Troubleshooting
If you are facing issues installing the package, execute the following to print verbose logs. 
```
$ sudo python -m pip install mesibo -v
```
Then, raise an issue [here](https://github.com/mesibo/python/issues) with the complete logs.

If you get a run-time error like
```
Unable to load: ... Platform not supported ...  
```
then mesibo does not support this platform. Contact us at [https://mesibo.com/support/](https://mesibo.com/support/) with your platform details, python version, installation logs, etc and we will help you out.
