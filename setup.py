
from distutils.core import setup,Extension
import subprocess


module=Extension("mesibo",
        sources=["src/bind.cpp","src/notify.cpp","src/core.cpp","src/globals.cpp","src/utils.cpp"], 
        
        include_dirs = ['include'],
        libraries = ['mesibo64']
        )

setup(name="mesibo",
        version="0.0.3",
        classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Natural Language :: English',
        'Programming Language :: Python :: 3 :: 2',
        'Programming Language :: Python :: Implementation :: CPython',
        "Operating System :: Linux"
        ],
        description="Python bindings for mesibo C/C++ API. Documentation: https://mesibo.com/documentation/",
        ext_modules=[module],
        py_modules = ['mesiboNotify.mesiboNotify']
        )
