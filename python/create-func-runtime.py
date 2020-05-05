from functools import wraps

def decorator_wo_args(func):
    def wrapper():
        print("[DECO]")
        func()
    return wrapper

def decorator_with_args(n):
    def inner(func):    
        def wrapper():
            print("[DECO {}]".format(n))
            func()
        return wrapper
    return inner

def class_decorator_wo_args(func, *args, **kwargs):
    def wrapper(*args, **kwargs):
        print("[CLASS_DECO]")
        func(*args, **kwargs)
    return wrapper

def class_decorator_with_args(n, *args, **kwargs):
    def inner(cls):
        def wrapper(func, *args, **kwargs):
            print("[CLASS_DECO {}]".format(n))
            func(*args, **kwargs)
        return wrapper
    return inner


l = ["hello", "hello_again"]
lcls = ["hello_from_static"]


class TestClass(object):
    static_val = 101

    @classmethod
    def static_factory_func(cls, string, n):
        @class_decorator_wo_args
        def f(obj):
            print("method: {}, {}".format(string, cls.static_val))
        return f

    @classmethod
    @class_decorator_with_args(111)
    # @class_decorator_wo_args
    def test_static(cls):
        print("Static method test")

    @classmethod
    def setup(cls):
        for i, item in enumerate(lcls):
            setattr(cls, item, cls.static_factory_func(item, i))

    def factory_func(self, string, n):
        @decorator_with_args(n)
        @decorator_wo_args
        def f():
            print("method: {}, {}".format(string, self.name))
        return f

    def __init__(self):
        self.name = "Boo"
        for i, item in enumerate(l, start=10):
            setattr(self, item, self.factory_func(item, i*2))
        print("Class {} is created".format(self.__class__.__name__))

print("### Setup")
TestClass.setup()

print("### Test static")
TestClass.test_static()

print("### Class instance")
c = TestClass()

print("### Call methods created from __init__")
c.hello()
c.hello_again()

print("### Call methods created from static")
c.hello_from_static()
