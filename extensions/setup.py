from setuptools import setup, Extension

cpp_args = ['-std=c++11']

extension = Extension(name="nms",
                      sources=["pybind11.cpp", "nms.cpp"],
                      include_dirs=["/Users/hujiahao1/opt/anaconda3/lib/python3.9/site-packages/pybind11/include"],
                      library_dirs=["/usr/local/lib"],
                      extra_compile_args=cpp_args)

setup(ext_modules=[extension])