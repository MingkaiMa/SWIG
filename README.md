Run command:

1. OpenMP

swig -python example.i 

CC=gcc-6 python setup.py build_ext --inplace

python top.py

2. 不用OpenMP, 注意需要修改 setup.py里面的两行

swig -python example.i

python setup.py build_ext --inplace

python top.py 
