#!/Users/marktoms/Desktop/ana/anaconda/bin/python3

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


example_module = Extension('_example',
                           sources=['example_wrap.c', 'example.c'],
                           extra_compile_args = ['-fopenmp'],
                           extra_link_args=['-fopenmp'],
                           )

setup (name = 'example',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example from docs""",
       ext_modules = [example_module],
       py_modules = ["example"],
       )
