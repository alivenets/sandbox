from functools import wraps

def test_decorator_wo_args(func):
    def wrapper():
        print("[Called decorator without args]")
        func()
    return wrapper

def test_decorator_with_args(n):
    def inner(func):    
        def wrapper():
            print("[Called decorator with {}]".format(n))
            func()
        return wrapper
    return inner

def class_decorator_wo_args(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print("[Called CLASS decorator without args]")
        func(*args, **kwargs)
    return wrapper

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
    @class_decorator_wo_args
    def test_static(cls):
        print("Static method test")

    @classmethod
    def setup(cls):
         for i, item in enumerate(lcls):
            setattr(cls, item, cls.static_factory_func(item, i))

    def factory_func(self, string, n):
        @test_decorator_with_args(n)
        def f():
            print("method: {}, {}".format(string, self.name))
        return f

    def __init__(self):
        self.name = "Boo"
        for i, item in enumerate(l, start=10):
            setattr(self, item, self.factory_func(item, i*2))
        print("Class {} is created".format(self.__class__.__name__))

TestClass.setup()

TestClass.test_static()

c =  TestClass()

print("### Call methods created from __init__")
c.hello()
c.hello_again()

print("### Call methods created from static")
c.hello_from_static()
