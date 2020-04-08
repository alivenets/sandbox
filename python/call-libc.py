# Call libc from Python and process errno
# Usage: python3 call-libc.py

import ctypes

libc = ctypes.CDLL("libc.so.6", use_errno=True)

ret = libc.fopen(ctypes.c_char_p(b"notexists"), ctypes.c_char_p(b"r"))
print(ret, ctypes.get_errno())

LEN = 1024
buf = ctypes.create_string_buffer(LEN)

ret = libc.klogctl(3, buf, LEN)
print(ret, ctypes.get_errno(), buf.value)
