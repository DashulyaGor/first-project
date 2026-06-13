# setup.py
from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy as np
import os

# Корень проекта
here = os.path.abspath(os.path.dirname(__file__))

# Путь к папке с модулем
robinson_dir = os.path.join(here, "maraton")

extensions = [
    Extension(
        "maraton.robinson_cruise",  # Правильное имя модуля
        [
            os.path.join(robinson_dir, "robinson_cruise.pyx"),
            os.path.join(robinson_dir, "robinson_cruise_with_request_JSON.c")
        ],
        include_dirs=[
            robinson_dir,
            np.get_include()
        ],
        define_macros=[("NPY_NO_DEPRECATED_API", "NPY_1_7_API_VERSION")],
        extra_compile_args=['-O3', '-std=c99'],
        extra_link_args=[],
        language='c'
    )
]

setup(
    name="maraton",
    packages=["maraton"],
    ext_modules=cythonize(
        extensions,
        language_level=3,
        compiler_directives={
            'boundscheck': False,
            'wraparound': False,
            'initializedcheck': False,
            'nonecheck': False,
            'cdivision': True
        }
    ),
    zip_safe=False,
)
