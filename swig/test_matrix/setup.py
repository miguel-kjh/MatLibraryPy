from distutils.core import setup, Extension

name = "matrix"    # name of the module
version = "1.0"        # the module's version number

setup(name=name, version=version,
      # distutils detects .i files and compiles them automatically
      ext_modules=[Extension(name='_matrix', # SWIG requires _ as a prefix for the module name
                             sources=["matrix.i", 
                                      "matrix.cpp"],
                             swig_opts=["-c++"])
    ])