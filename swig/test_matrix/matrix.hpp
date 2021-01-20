#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <initializer_list>
#include <exception>
#include <stdexcept>
#include <system_error>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <complex>
#include <regex>
#include <iomanip>


using namespace std;

namespace mat_lib
{

  enum format{
      scientific,
      fixed
  };

  //template<typename T>
  class base_matrix{
    public:
        base_matrix(int);
        format getFormat() const;
        int getFractionalDigits() const;
        void setFormat(format format);
        void setFractionalDigits(int fractionalDigits);

    protected:
        format format__         = fixed;
        int fractional_digits__ = 6;
    };

}

#endif