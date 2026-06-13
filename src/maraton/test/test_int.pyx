# test_int.pyx

from libc.stdint cimport int32_t, int64_t

def test_function():
    cdef int32_t a = 42
    cdef int64_t b = 1000000
    return {'a': a, 'b': b}