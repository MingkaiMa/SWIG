Run command:

1. OpenMP

swig -python example.i 

CC=gcc-6 python setup.py build_ext --inplace

python top.py

2. Use without OpenMP, need to change towlinesin setup.py

swig -python example.i

python setup.py build_ext --inplace

python top.py 
