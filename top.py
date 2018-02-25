import time
import timeit




class A(object):
    def __init__(self, x):
        self._x = x
        self._y = None

    def f(self, v, args):
        self._y = self._x
        print(self._y, '-', id(v), '_', id(args))
        time.sleep(1)


class Dummy:
    def __init__(self):
        pass


def py_func(a, i, j, args):

    assert(isinstance(a, list))
    a[i].f(a[j], args)


def c_func_py_wrapper(a, N, args):
    c_func(a, N, args)


def c_func(a, N, args):
    """ this function should be implemented in C """
    for i in range(N):
        for j in range(i+1, N):
            py_func(a[i], a[j], args)




if __name__ == "__main__":
    dummy = Dummy()
    N = 10
    al = [A(i) for i in range(N)]

    import example

    t1 = timeit.default_timer()
    example.c_funct(al, N, dummy)

    t2 = timeit.default_timer()
    print("walltime- %.2f seconds" % (t2 - t1))

    #c_func_py_wrapper(al, N, dummy)
