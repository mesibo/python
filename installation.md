## Mesibo for Python

## Getting started with Mesibo Python Sdk
Mesibo Real-Time Python API is an extenstion module to the Mesibo C/C++ library. You can build and install Mesibo Python Module from source. The entire source code can be found at [Mesibo GitHub Repo](https://github.com/mesibo/python)

Build Requirements :
-Mesibo Real-Time Python API is built as an extension to the Mesibo C/C++ library. Instructions to install the Mesibo C/C++ shared library can be found [here](https://mesibo.com/documentation/install/linux/#install-using-the-convenience-script)

-  Python 3 (3.4 or newer ) / Python 2 (2.7 or newer)
  On CentOS,Debian and derivatives (Ubuntu): python, python-dev (or python3-dev/python2-dev)
  Make sure that the Python package distutils is installed. For example,in Debian GNU/Linux, installing python-dev also      installs distutils.

- The Mesibo Python Module is built on C-extensions and implemented using CPython .You need to compile from source to get a shared library file which will then be used by Python.
  C/C++ compiler.GCC 4.x (and later)are recommended.
  
## Installation

To build and install the Mesibo Python module
```
sudo python setup.py install

```
The files resulting from the compilation are placed in the build directory. All the files are copied from this build directory into the lib directory path of your Python installation.

To perform an in-place build that can be run from the source folder run:
```
python setup.py build_ext --inplace
```


If you have installed Mesibo Python Library sucessfully  you should be able to import the module in Python like so
```
from mesibo import Mesibo
from mesiboNotify.mesiboNotify import mesiboNotify
```

