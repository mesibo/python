# Mesibo for Python

## Getting started with Mesibo Python Sdk
Mesibo Python API is a completely open-source real-time library which can be built and installed from source. The entire source code and installation details can be found at our GitHub repo  [Mesibo Python API](https://github.com/mesibo/python)

### Platforms Supported 
Currently the Mesibo Real-Time Python library is under-development and supports Linux,Mac and Raspberry Pi.

## Build Requirements 

**1. Python 3 (3.4 or newer ) / Python 2 (2.7 or newer)**
  
  Install the development packages for Python.For example,on Linux based systems such as CentOS,Debian and derivatives (Ubuntu) the packages are `python` and `python-dev` (or python3-dev/python2-dev).
  
  Make sure that the Python package `distutils` is installed. 
#### Debian/Ubuntu
```
apt-get install libffi-dev python-dev python3-dev
```
#### Centos/RHEL/Fedora
```
yum install libffi-devel python3-devel python-devel
```

**2. Mesibo C/C++ library**
Mesibo Real-Time Python API is interfaced with the Mesibo C/C++ library(supported on Linux,Mac and Raspberry Pi) to perform API calls and is implemented using CPython.

Instructions to install the Mesibo C/C++ shared library can be found [here](https://mesibo.com/documentation/install/linux/#install-using-the-convenience-script). 
You can install [Mesibo C/C++ library](https://github.com/mesibo/libmesibo) using a convenience-script provided by Mesibo
```
curl -fsSL https://raw.githubusercontent.com/mesibo/libmesibo/master/install.sh | sudo bash -
```

**3. Compiler(GCC 4.x and later are preferred)**
The Mesibo Python Module is built on C-extensions and hence you need to compile from source files to get a shared library file which will then be loaded into Python as a module.
  C/C++ compiler.GCC 4.x (and later)are recommended.
   

  
## Build and Install

Download the source files from [Mesibo Python API](https://github.com/mesibo/python) and ensure the following directory structure:
```
|-- include
|-- mesiboNotify
|-- src
|-- setup.py

```
It is recommended that you clone the GitHub repository
```
git clone https://github.com/mesibo/python.git
```

To build and install the Mesibo Python module from source
```
sudo python setup.py install

```
The entire module is built and installed automatically by copying files in the generated build folder,into the lib directory path of your Python installation.

If you prefer not to install it automatically ,you can perform an in-place build that can be run from the source folder to obtain a shared libaray file which can be then installed as per your needs.
```
python setup.py build_ext --inplace
```

If you have installed Mesibo Python Library sucessfully  you should be able to import the module in Python like so
```python
from mesibo import Mesibo
from mesiboNotify.mesiboNotify import mesiboNotify
```
## Next Steps
- Refer to the Mesibo Python API usage [tutorial](https://github.com/mesibo/python)
- Build an image recoginition chatbot by integrating Mesibo and TensorFlow.Check out the Jupyter Notebook [demo](https://colab.research.google.com/drive/1KDASF7tCVMsmvpD1mMrD4uEo-MKiZ6DA#scrollTo=KPr32jdGYOnU)
