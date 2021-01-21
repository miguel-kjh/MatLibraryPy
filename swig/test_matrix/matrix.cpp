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

matrix::matrix(vector<vector<double>> init) {


    if(!check_initilizer_list__(init))
    {
      ostringstream str_stream;
      str_stream<<"column length mismatch! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }
    
    rows__=init.size(); columns__=init.begin()->size();
    elements__=new double[rows__*columns__];

    for(size_t i=0; i<init.size(); i++)
      for(size_t j=0; j<init.begin()[i].size(); j++)
        elements__[offset__(i,j)]=init.begin()[i].begin()[j];
  }


ostream& mat_lib::output(ostream& os, const matrix& m)
  {
    static const char* prefix="  ";
    size_t i,j;



    os<<"mat_lib::matrix["<<m.rows()<<"x"<<m.columns()<<"]{";
    for(i=0; i<m.rows(); i++)
    {
      os<<"\n"<<prefix;
      for(j=0; j<m.columns()-1; j++) os<<m[i][j]<<", ";
      if (m.getFormat() == mat_lib::fixed)
          os << std::fixed << setprecision(m.getFractionalDigits()) << m[i][j];
      else
          os << std::scientific << setprecision(m.getFractionalDigits()) << m[i][j];
    }
    os<<"\n}";

    return os;
  }