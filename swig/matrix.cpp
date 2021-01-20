#include "matrix.hpp"

using namespace mat_lib;

template<typename T>
base_matrix<T>::base_matrix(int value) {
    fractional_digits__ = value;
}

// base_matrix definition
template<typename T>
format base_matrix<T>::getFormat() const {
    return format__;
}

template<typename T>
int base_matrix<T>::getFractionalDigits() const {
    return fractional_digits__;
}

template<typename T>
void base_matrix<T>::setFormat(format format) {
    format__ = format;
}

template<typename T>
void base_matrix<T>::setFractionalDigits(int fractionalDigits) {
    if (fractionalDigits <= 0) throw logic_error("bad decimal precision");

    fractional_digits__ = fractionalDigits;
}




// matrix definition