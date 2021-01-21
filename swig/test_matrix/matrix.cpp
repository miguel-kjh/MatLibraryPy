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

/*
>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ""
                 matrix operators
>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< "
*/

matrix& matrix::operator=(const matrix& m) // copy assigment
{
  if(size()!=m.size())
  {
    delete [] elements__;
    elements__=((m.size())? new double[m.size()]: nullptr);
  }
  copy_elements__(m);
  return *this;
}

matrix& matrix::operator=(matrix&& m) // move assigment
{
  delete [] elements__;
  
  elements__=m.elements__;  
  rows__=m.rows__; columns__=m.columns__;

  m.elements__=nullptr;  
  m.rows__=m.columns__=0;

  return *this;
}

matrix& matrix::operator+=(const matrix& m) {

  if((rows()!=m.rows()) || (columns()!=m.columns())) 
  {
    ostringstream str_stream;
    str_stream<<"size mismatch! cannot add matrices ("
      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
    throw invalid_argument(str_stream.str());
  }

  for(size_t i=0; i<rows__; i++)
    for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]+=m[i][j];
    
  return *this;
}

matrix& matrix::operator-=(const matrix& m) {
  if((rows()!=m.rows()) || (columns()!=m.columns())) 
  {
    ostringstream str_stream;
    str_stream<<"size mismatch! cannot substract matrices ("
      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
    throw invalid_argument(str_stream.str());
  }

  for(size_t i=0; i<rows__; i++)
    for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]-=m[i][j];
    
  return *this;
}

matrix& matrix::operator*=(double scalar) {
  for(size_t i=0; i<rows__; i++)
    for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]*=scalar;

  return *this;
}

matrix& matrix::operator/=(double scalar) {
  if(scalar==0) 
  {
    ostringstream str_stream;
    str_stream<<"divide by zero! bad scalar provided ("
      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
    throw invalid_argument(str_stream.str());
  }
  for(size_t i=0; i<rows__; i++)
    for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]/=scalar;

  return *this;
}

bool matrix::operator==(const matrix& m) const
{
  if((rows__!=m.rows()) || (columns__!=m.columns())) return false; 

  for(size_t i=0; i<rows__; i++)
    for(size_t j=0; j<columns__; j++) 
      if(elements__[offset__(i,j)]!=m[i][j]) return false;
  
  return true;
}


/* ostream& mat_lib::output(ostream& os, const matrix& m)
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
  } */



  void mat_lib::output(const matrix& m)
  {
    static const char* prefix="  ";
    size_t i,j;

    cout<<"mat_lib::matrix["<<m.rows()<<"x"<<m.columns()<<"]{";
    for(i=0; i<m.rows(); i++)
    {
      cout<<"\n"<<prefix;
      for(j=0; j<m.columns()-1; j++) cout<<m[i][j]<<", ";
      if (m.getFormat() == mat_lib::fixed)
          cout << std::fixed << setprecision(m.getFractionalDigits()) << m[i][j];
      else
          cout << std::scientific << setprecision(m.getFractionalDigits()) << m[i][j];
    }
    cout<<"\n}";

  }