# setup.py

from setuptools import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize(
        "test/test_int.pyx",
        language_level=3
    )
)