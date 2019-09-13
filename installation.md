# Mesibo for Python

Mesibo Python API is a completely open-source real-time library which can be built and installed from source. The entire source code and installation details can be found at our GitHub repo  [Mesibo Python API](https://github.com/mesibo/python)

### Platforms Supported 
Currently the Mesibo Real-Time Python library is under-development and supports Linux,Mac and Raspberry Pi.

## Requirements 

Building Mesibo Python Module requires the following software installed:

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

Once you have installed Mesibo Python Library sucessfully, you should be able to import Mesibo module in Python as follows:
```python
from mesibo import Mesibo
from mesibo import MesiboNotify
```


## Next Steps
- Checkout the tutorial [Write your First Mesibo Enabled Application in Python](https://mesibo.com/documentation/tutorials/first-app/python/)
