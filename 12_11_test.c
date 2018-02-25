#include <Python.h>

void getcurrent()
{
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import time");
    PyRun_SimpleString("sys.path.append('./')");
    return;
}

void c_funct()
{
    Py_Initialize();
    getcurrent();


    //get py_func

    PyObject *pModule = PyImport_ImportModule("top"); //引入模块
    PyObject *pDict = PyModule_GetDict(pModule); //获取模块字典属性 //相当于Python模块对象的__dict__ 属性，得到模块名称空间下的字典对象
    PyObject *pFunc = PyDict_GetItemString(pDict, "py_func");

    //get class

    PyObject *pClass = PyDict_GetItemString(pDict, "A");

    PyObject *pClass_2 = PyDict_GetItemString(pDict, "Dummy");
    PyObject *plist = PyList_New(3);

    for(int i = 0; i < 3; ++i){

        PyObject *value = Py_BuildValue("(i)", i);
        PyObject *oneObj = PyObject_CallObject(pClass, value);

        PyList_SetItem(plist, i, oneObj);
    }

    PyObject *arg3 = PyInstance_New(pClass_2, NULL, NULL);

    for(int i = 0; i < 3; ++i){
        for(int j = i + 1; j < 3; ++j){

            printf("%d-%d\n", i, j);
            PyObject *x = PyList_GetItem(plist, i);
            PyObject *y = PyList_GetItem(plist, j);
            PyObject *pArg = Py_BuildValue("(O, O, O)",x, y, arg3);
            PyEval_CallObject(pFunc,pArg);

        }

    }

    printf("end\n");

    Py_Finalize();
    return;
}

int main(int argc, char *argv[]){
    c_funct();
    return 0;
}