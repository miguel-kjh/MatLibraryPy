#include <iostream>
using namespace std;

#include "matrix.hpp"
using namespace mat_lib;

#include <boost/python.hpp>

using matrix_t=matrix<double>;
using namespace boost::python;

BOOST_PYTHON_MODULE(MatLibraryPy)
{
    class_<matrix<int>>("Matrix", init<>())
        .def(init<int,int>())
    ;
}
