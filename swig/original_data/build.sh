swig -python -c++ -Isrc matrix.i

g++ -Isrc -fPIC -c $(pkg-config --cflags --libs python3) matrix.cpp matrix_wrap.cxx
g++ -shared -o _matrix.so matrix.o matrix_wrap.o