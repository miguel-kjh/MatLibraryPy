#include "matrix.hpp"

using namespace mat_lib;

/*
>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ""
                Definition of class base_matrix
>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< "
*/

//template<typename T>
format base_matrix::getFormat() const {
    return format__;
}

//template<typename T>
int base_matrix::getFractionalDigits() const {
    return fractional_digits__;
}

//template<typename T>
void base_matrix::setFormat(format format) {
    format__ = format;
}

//template<typename T>
void base_matrix::setFractionalDigits(int fractionalDigits) {
    if (fractionalDigits <= 0) throw logic_error("bad decimal precision");
    fractional_digits__ = fractionalDigits;
}


/*
>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ""
                Definition of class matrix
>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< "
*/

matrix::matrix() {
    rows__ = 0;
    columns__ = 0;
    elements__ = nullptr;
}

matrix::matrix(size_t rows, size_t columns) {
    rows__ = rows;
    columns__ = columns;
    elements__ = new double[rows*columns];
}

matrix::matrix(vector<double> init) {
    rows__ = 1;
    columns__ = init.size();
    elements__ = new double[rows__*columns__];
    for(size_t i=0; i<init.size(); i++) 
        elements__[i]= init[i];
}

/* matrix::matrix(vector<vector<double>> init) {

} */

