#include "matrix.hpp"

using namespace mat_lib;

//template<typename T>
base_matrix::base_matrix(int value) {
    fractional_digits__ = value;
}

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