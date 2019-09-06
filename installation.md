# Mesibo for Python

## Getting started with Mesibo Python Sdk
Mesibo Python API is a completely open-source real-time library. You can build and install Mesibo Python Module from source. The entire source code and installation details can be found at our GitHub repo  [Mesibo Python API](https://github.com/mesibo/python)

## Build Requirements 

###  Mesibo C/C++ library
Mesibo Real-Time Python API is built as an extension to the Mesibo C/C++ library. 
Instructions to install the Mesibo C/C++ shared library can be found [here](https://mesibo.com/documentation/install/linux/#install-using-the-convenience-script). 
You can install [Mesibo C/C++ library](https://github.com/mesibo/libmesibo) using a convenience-script provided by Mesibo
```
curl -fsSL https://raw.githubusercontent.com/mesibo/libmesibo/master/install.sh | sudo bash -
```

### Python 3 (3.4 or newer ) / Python 2 (2.7 or newer)
  Install the development packages for Python. On CentOS,Debian and derivatives (Ubuntu): python, python-dev (or python3-dev/python2-dev).Make sure that the Python package distutils is installed. 

### Compiler(GCC 4.x and later are preferred)
The Mesibo Python Module is built on C-extensions and implemented using CPython .You need to compile from source to get a shared library file which will then be used by Python.
  C/C++ compiler.GCC 4.x (and later)are recommended.
  
## Build and Install

To build and install the Mesibo Python module from source
```
sudo python setup.py install

```
The files resulting from the compilation are placed in the build directory. All the files are automatically copied from this build directory into the lib directory path of your Python installation.

To perform an in-place build that can be run from the source folder run:
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
