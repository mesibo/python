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

    def mesibo_on_connectionstatus(self, status):
        """A status = 1 means the listener 
        successfully connected to the mesibo server
        """
        print("## Connection status: ", status)
        return 0

    def mesibo_on_message(self, msg_params, data):
        """Invoked on receiving a new message 
        or reading database messages
        data: python byte array 
        """
        message = None
        try:
            # try to decode string
            message = data.decode(encoding="utf-8", errors="strict") 
            print("\n ## Received message:", message)
        except:
            pass
        
        print("\n ## on_message: ", msg_params)
        print("## Received Data: \n", data)
        # handle: integer, bytes, etc

        return 0

    def mesibo_on_messagestatus(self, msg_params):
        """Invoked when the status 
        of an outgoing or sent message is changed. msg_params.status can be
        sent, delivered, or read
        """
        print("## on_messagestatus", msg_params)
        return 0

def send_one_to_one_message(mesibo_api, destination_address, message):
    params = Mesibo.MessageParams()
    params.peer = destination_address
    params.flag = Mesibo.FLAG_READRECEIPT | Mesibo.FLAG_DELIVERYRECEIPT
    mid = api.random()
    mesibo_api.send_message(params, mid, message)

# Get access token and app id by creating a mesibo user
# See https://mesibo.com/documentation/tutorials/get-started/
ACCESS_TOKEN = "xxxxx"
APP_ID = "xxxxx"

# Create a Mesibo Instance
api = Mesibo()

# Set Listener
listener = PyMesiboListener()
api.add_listener(listener)

# Set your AUTH_TOKEN obtained while creating the user 
if(Mesibo.RESULT_FAIL == api.set_accesstoken(ACCESS_TOKEN)):
    print("===> Invalid ACCESS_TOKEN: ", ACCESS_TOKEN)
    print("See https://mesibo.com/documentation/tutorials/get-started/")
    exit(1) 

# Set APP_ID which you used to create AUTH_TOKEN
api.set_appname(APP_ID)

# Set the name of the database
api.set_database("mesibo.db")

# Start mesibo, 
api.start()

send_one_to_one_message(api, "xxx", "Hello from Python!")

# Wait for the application to exit
api.wait()
```

## Installation
See [requirements](https://mesibo.com/documentation/install/python/#requirements) to learn about installation requirements before you continue.
```
$ sudo python -m pip install mesibo
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
