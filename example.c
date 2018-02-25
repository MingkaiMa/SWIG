#include "example.h"
#include <Python.h>
#include <stdio.h>
#include <time.h>

void getcurrent()
{
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    return;
}

void test0(void)
{
	Py_Initialize();
    getcurrent();
	PyRun_SimpleString("print('hello world123')");
	Py_Finalize();
	return;
}

void test1(void)
{
    Py_Initialize();
    getcurrent();

    PyObject *pModule = PyImport_ImportModule("demo");
    PyObject *pFunc = PyObject_GetAttrString(pModule, "print_arg");
    PyObject *pArg = Py_BuildValue("(s)", "hello_python");
    PyEval_CallObject(pFunc, pArg);

    Py_Finalize();

    return;

}

void test2(char *sfun)
{
    Py_Initialize();
    getcurrent();


    //PyObject *pModule = NULL, *pDict = NULL, *pFunc = NULL, *pArg = NULL, *result = NULL;
    PyObject *pModule = PyImport_ImportModule("demo"); //引入模块
    PyObject *pDict = PyModule_GetDict(pModule); //获取模块字典属性 //相当于Python模块对象的__dict__ 属性，得到模块名称空间下的字典对象
    PyObject *pFunc = PyDict_GetItemString(pDict, sfun); //从字典属性中获取函数
    PyObject *pArg = Py_BuildValue("(i, i)", 1, 2); //参数类型转换，传递两个整型参数
    PyObject *result = PyEval_CallObject(pFunc, pArg); //调用函数，并得到python类型的返回值
    int sum;
    PyArg_Parse(result, "i", &sum); //将python类型的返回值转换为c/c++类型
    printf("sum=%d\n", sum);

    //Py_Finalize(); 如果不注释此行，调用该函数后会出现 Segmentation fault: 11
}

void c_funct(PyObject *plist, int N, PyObject *arg2)
{
    Py_Initialize();



    //PyEval_InitThreads();
    //PyEval_ReleaseThread(PyThreadState_Get());

    getcurrent();

    //get py_func

    PyObject *pModule = PyImport_ImportModule("top"); //引入模块
    PyObject *pDict = PyModule_GetDict(pModule); //获取模块字典属性 //相当于Python模块对象的__dict__ 属性，得到模块名称空间下的字典对象
    PyObject *pFunc = PyDict_GetItemString(pDict, "py_func");


    //get class

    //PyObject *pClass = PyDict_GetItemString(pDict, class_one);

    //PyObject *pClass_2 = PyDict_GetItemString(pDict, class_two);
    //PyObject *plist = PyList_New(N);

    //for(int i = 0; i < N; ++i){

     //   PyObject *value = Py_BuildValue("(i)", i);
     //   PyObject *oneObj = PyObject_CallObject(pClass, value);

    //    PyList_SetItem(plist, i, oneObj);
   // }

    //PyObject *arg3 = PyObject_CallObject(pClass_2, NULL);

    //PyGILState_Ensure();

    //clock_t start, finish;
    //double Thetimes;

    //start = clock();


    #pragma omp parallel for
    for(int i = 0; i < N; ++i){
        for(int j = i + 1; j < N; ++j){

            printf("%d--%d\n", i, j);
          //  PyObject *x = PyList_GetItem(plist, i);
           // PyObject *y = PyList_GetItem(plist, j);
            PyObject *pArg = Py_BuildValue("(O, i, i, O)",plist, i, j, arg2);


            PyGILState_STATE gstate;
            gstate = PyGILState_Ensure();

            PyEval_CallObject(pFunc,pArg);


            PyGILState_Release(gstate);


        }

    }

    //finish = clock();


    //Thetimes = (double)(finish-start)/CLOCKS_PER_SEC;

    //printf("%f seconds\n", Thetimes);

    printf("end\n");

    //Py_Finalize();
    return;
}


int fact(int n) {
    if (n < 0){ /* This should probably return an error, but this is simpler */
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    else {
        /* testing for overflow would be a good idea here */
        return n * fact(n-1);
    }
}

void print_flag(char *s){
    printf("%s\n", s);
    return;
}

char get_size(char *s, int index) {

    //int length = sizeof(s) / sizeof(char);
    return s[index];
}