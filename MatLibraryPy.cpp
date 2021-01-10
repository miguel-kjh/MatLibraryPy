#include <iostream>
using namespace std;

#include "matrix.hpp"
using namespace mat_lib;

#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(MatLibraryPy)
{
    class_<matrix<double>>("Matrix", init<>())
        .def(init<int,int>())
        .def(init<boost::python::list>())
        .def(init<string>())
        .def(init<matrix<double>>())
        .def("__str__", &matrix<double>::str)
        .def("__repr__", &matrix<double>::repr)
        .def(self + matrix<double>())
        .def(self - matrix<double>())
        .def(self  / int())
        .def(int() / self)
        .def(self * matrix<double>())
        .def(self += matrix<double>())
        .def(self -= matrix<double>())
        .def(self == matrix<double>())
        .def("size", &matrix<double>::size)
        .def("rows", &matrix<double>::rows)
        .def("columns", &matrix<double>::columns)
        .def("get", &matrix<double>::get)
        .def("set", &matrix<double>::set)
        .def("inv", &matrix<double>::inverse)
        .def("transpose", &matrix<double>::make_transpose)
        .def("saveAs", &matrix<double>::save_as)
    ;
}
