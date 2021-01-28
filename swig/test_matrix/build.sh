swig -python -c++ -Isrc matrix.i


g++ -Isrc -fPIC -c $(pkg-config --cflags --libs python3) matrix.cpp matrix_wrap.cxx
g++ -shared -o _matrix.so matrix.o matrix_wrap.o

python3.8 setup.py build_ext

python3.8 setup.py install --install-platlib=.