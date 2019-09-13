from distutils.core import setup,Extension
import os

#Install Mesibo C/C++ library
#os.system("curl -fsSL https://raw.githubusercontent.com/mesibo/libmesibo/master/install.sh | sudo bash -")

module=Extension("mesibo.mesibo",
        sources=["src/bind.cpp","src/notify.cpp","src/core.cpp","src/globals.cpp","src/utils.cpp"],

        include_dirs = ['include'],
        libraries = ['mesibo']
        )

setup( name="mesibo",
        version="0.0.3",
        classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Natural Language :: English',
        'Programming Language :: Python :: 3 :: 2',
        'Programming Language :: Python :: Implementation :: CPython',
        "Operating System :: Linux"
        ],
        description="Mesibo Real-Time Python Library. Documentation: https://mesibo.com/documentation/",
        ext_modules=[module],
        py_modules = ['mesibo.mesibonotify']
        )

