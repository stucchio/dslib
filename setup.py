from distutils.core import setup, Extension
import os


_dslib = Extension('_dslib_ext',
                   sources = ['dslib/test.i', 'dslib/test.cpp'],
                   extra_compile_args = [],
                   swig_opts=['-py3', '-c++']
)

setup (name = 'Data structures lib',
       version = '0.1',
       description = 'Data structures',
       ext_modules = [_dslib],
       py_modules = ["dslib", 'dslib.dslib_ext'],
       package_dir = { 'dslib' : 'dslib' },
)
