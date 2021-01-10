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
        .def(self  / double())
        .def(double() / self)
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

    class_<mat_lib::vector<double>>("Vector", init<int>())
        .def(init<boost::python::list>())
        .def(init<string>())
        .def("__str__", &mat_lib::vector<double>::str)
        .def("__repr__", &mat_lib::vector<double>::repr)
        .def("saveAs", &mat_lib::vector<double>::save_as)
        .def("size", &mat_lib::vector<double>::size)
        .def("random", &mat_lib::vector<double>::define_random)
        .def("define", &mat_lib::vector<double>::define_value)
        .def("isEmpty", &mat_lib::vector<double>::is_empty)
        .def("set", &mat_lib::vector<double>::set)
        .def("get", &mat_lib::vector<double>::get)
        .def(self + mat_lib::vector<double>())
        .def(self + double())
        .def(self - mat_lib::vector<double>())
        .def(self - double())
        .def(self * mat_lib::vector<double>())
        .def(self * double())
        .def(self / mat_lib::vector<double>())
        .def(self / double())
        .def(self += mat_lib::vector<double>())
        .def(self -= mat_lib::vector<double>())
        .def(self == mat_lib::vector<double>())
        .def(self /= mat_lib::vector<double>())
        .def(self != mat_lib::vector<double>())
    ;
}
