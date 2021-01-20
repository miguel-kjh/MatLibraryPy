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
#include <boost/algorithm/string.hpp>
/* #include <boost/python.hpp> */

using namespace std;

namespace mat_lib
{
  enum format{
    scientific,
    fixed
  };

  template<typename T>
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

  template<typename T>
  class matrix: public base_matrix<T>
  {
    public:
      using element_t=T;

      static_assert(
        is_integral<T>::value || 
        is_floating_point<T>::value ||
        is_same<T,complex<float>>::value ||
        is_same<T,complex<double>>::value ||
        is_same<T,complex<long double>>::value,
        "\n"
        "[ERROR] >>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< [ERROR]\n"
        "[ERROR] >>>> BAD TYPE PROVIDED FOR TEMPLATE mat_lib::matrix! <<<< [ERROR]\n"
        "[ERROR] >>>> ACCEPTED TYPES:                                 <<<< [ERROR]\n"
        "[ERROR] >>>>   - All numeric primitive types                 <<<< [ERROR]\n"
        "[ERROR] >>>>   - std::complex<float>                         <<<< [ERROR]\n"
        "[ERROR] >>>>   - std::complex<double>                        <<<< [ERROR]\n"
        "[ERROR] >>>>   - std::complex<long double>                   <<<< [ERROR]\n"
        "[ERROR] >>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< [ERROR]\n"
      );

      matrix() // default constructor
      : rows__{0},
        columns__{0},
        elements__{nullptr}
      {}

      matrix(size_t rows, size_t columns)
      : rows__{rows},
        columns__{columns},
        elements__{new element_t[rows*columns]}
      {}

      matrix(
        initializer_list<
          initializer_list<element_t>
        > init
      );

      matrix(initializer_list<element_t> init)
      : rows__{1},
        columns__{init.size()},
        elements__{new element_t[rows__*columns__]}
      { for(size_t i=0; i<init.size(); i++) elements__[i]=init.begin()[i]; }

      matrix(const matrix& m) // copy constructor
      : elements__{new element_t[m.size()]}
      { copy_elements__(m); }

      matrix(matrix&& m)// move constructor
      : rows__{m.rows__},
        columns__{m.columns__},
        elements__{m.elements__}
      {
        m.elements__=nullptr;
        m.rows__=m.columns__=0;
      }


      explicit matrix(const string& file_name); // constructor from a file

      ~matrix() { delete [] elements__; }

      matrix& operator=(const matrix& m) // copy assigment
      {
        if(size()!=m.size())
        {
          delete [] elements__;
          elements__=((m.size())? new element_t[m.size()]: nullptr);
        }
        copy_elements__(m);
        return *this;
      }

      matrix& operator=(matrix&& m) // move assigment
      {
        delete [] elements__;
        
        elements__=m.elements__;  
        rows__=m.rows__; columns__=m.columns__;

        m.elements__=nullptr;  
        m.rows__=m.columns__=0;

        return *this;
      }

      size_t size() const { return rows__*columns__; }
      size_t rows() const { return rows__; }
      size_t columns() const { return columns__; }

      element_t at(size_t i, size_t j) const;

      element_t* operator[](size_t i) { return &(elements__[row_offset__(i)]); }
      const element_t* operator[](size_t i) const { return &(elements__[row_offset__(i)]); }

      element_t get(std::size_t row, std::size_t column) const {
          if (column >= this->columns() || row >= this->rows())
              throw logic_error("bad dimension");
          if (column < 0 || row < 0)
              throw logic_error("rows and columns must be positive integers");
          return elements__[offset__(row,column)];
      }

      void set(std::size_t row, std::size_t column, element_t number) {
          if (column >= this->columns() || row >= this->rows())
              throw logic_error("bad dimension");
          if (column < 0 || row < 0)
              throw logic_error("rows and columns must be positive integers");
          elements__[offset__(row,column)] = number;
      }

      bool operator==(const matrix& m) const;

      matrix& operator+=(const matrix& m);
      matrix& operator-=(const matrix& m);

      matrix<T> inverse();

      matrix& operator*=(element_t scalar)
      {
        for(size_t i=0; i<rows__; i++)
          for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]*=scalar;

        return *this;
      }

      matrix& operator/=(float scalar);

      matrix make_transpose() const
      {
        matrix t(columns__,rows__);

        for(size_t i=0; i<t.rows(); i++)
          for(size_t j=0; j<t.columns(); j++)
            t[i][j]=elements__[offset__(j,i)];

        return t;
      }

      void save_as(const string &file_name) const;

      std::string str() const;
      std::string repr() const;

  private:

      size_t rows__;
      size_t columns__;
      element_t* elements__;


      bool check_initilizer_list__(const initializer_list<initializer_list<element_t>>& init)
      {
        auto column_size=init.begin()[0].size();
        for(size_t i=1; i<init.size(); i++)
          if(init.begin()[i].size()!=column_size) return false;
        return true;
      }

      void copy_elements__(const matrix& m)
      { 
        rows__=m.rows__; columns__=m.columns__;
        for(size_t i=0; i<rows__; i++) 
          for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]=m.elements__[offset__(i,j)]; 
      }

      element_t** get_elements_pointer()
      {
          int size = rows()*columns() + 2;
          element_t** matrix = new element_t*[size];
          for (int i = 0; i < size; i++)
              matrix[i] = new element_t[size];

          for (int i = 0; i < rows(); ++i) {
              for (int j = 0; j < columns(); ++j) {
                  matrix[i][j] = elements__[offset__(i,j)];
              }
          }

          return matrix;
      }

      size_t row_offset__(size_t i) const { return i*columns__; }
      size_t offset__(size_t i,int j) const { return row_offset__(i)+j; }
  };

  template<typename T>
  matrix<T>::matrix(
    initializer_list<
      initializer_list<typename matrix<T>::element_t>
    > init)
  {
    if(!check_initilizer_list__(init))
    {
      ostringstream str_stream;
      str_stream<<"column length mismatch! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    rows__=init.size(); columns__=init.begin()->size();
    elements__=new element_t[rows__*columns__];

    for(size_t i=0; i<init.size(); i++)
      for(size_t j=0; j<init.begin()[i].size(); j++)
        elements__[offset__(i,j)]=init.begin()[i].begin()[j];
  }

  /* template<typename T>
  matrix<T>::matrix(const string& file_name) // constructor from a file
  : rows__{0},
    columns__{0},
    elements__{nullptr}
  {
    ifstream ifs(file_name);
    if(!ifs)
    {
      ostringstream str_stream;
      str_stream<<"cannot open file \""<<file_name<<"\"! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw logic_error(str_stream.str());
    }

    string str((istreambuf_iterator<char>(ifs)),
               istreambuf_iterator<char>());

    regex rx(R"(mat_lib::matrix\[(\d+)x(\d)\]\{\n\s*(([-+]?\d*\.?\d+([eE][-+]?\d+)?(,\s|\n\s*)?)+)+\n\})");
    cmatch results;
    if (not regex_match(str.c_str(),results,rx)) {
        throw logic_error("the file are incorrect: bad expresion");
    }

    rows__ = stoi(results.str(1));
    columns__ = stoi(results.str(2));
    vector<string> numbers;
    boost::split(numbers, results.str(3), boost::is_any_of("(,|\n)"));


    if (numbers.size() != rows__*columns__) {
      throw logic_error("the file are incorrect: bad declaration of matrix");
    }

    elements__ = new element_t[rows__*columns__];

    int index = 0;
    for(size_t i=0; i<rows__; i++){
      for(size_t j=0; j<columns__; j++) {
          elements__[offset__(i, j)] = stod(numbers[index]);
          index++;
      }
    }
  } */

  template<typename T>
  typename matrix<T>::element_t matrix<T>::at(size_t i, size_t j) const 
  { 
    if((i>=rows__) || (j>=columns__)) 
    {
      ostringstream str_stream;
      str_stream<<"out_of range exception ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw out_of_range(str_stream.str());
    }

    return elements__[offset__(i,j)];
  }

  template<typename T>
  bool matrix<T>::operator==(const matrix<T>& m) const
  {
    if((rows__!=m.rows()) || (columns__!=m.columns())) return false; 

    for(size_t i=0; i<rows__; i++)
      for(size_t j=0; j<columns__; j++) 
        if(elements__[offset__(i,j)]!=m[i][j]) return false;
    
    return true;
  }

  template<typename T>
  matrix<T>& matrix<T>::operator+=(const matrix<T>& m)
  {
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

  template<typename T>
  matrix<T>& matrix<T>::operator-=(const matrix<T>& m)
  {
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

  template<typename T>
  matrix<T>& matrix<T>::operator/=(float scalar)
  {
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

  template<typename T>
  void matrix<T>::save_as(const string& file_name) const
  {
    ofstream ofs(file_name);
    if(!ofs)
    {
      ostringstream str_stream;
      str_stream<<"cannot open file \""<<file_name<<"\"! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw logic_error(str_stream.str());
    }

    if(this->format__ == fixed)
        ofs << std::fixed << setprecision(this->fractional_digits__) << *this;
    else
        ofs << std::scientific << setprecision(this->fractional_digits__) << *this;
  }

    template<typename T>
    matrix<T> matrix<T>::inverse() {
        if(rows() != columns() || rows()*columns() <= 1)
            throw logic_error("Inverse operation not possible, the elementsPointer need be square and the order grater than one");

        T** elementsPointer = get_elements_pointer();
        std::size_t order = rows();
        for (int i = 0; i < order; i++) {
            for (int j = 0; j < 2 * order; j++) {
                if (j == (i + order))
                    elementsPointer[i][j] = 1;
            }
        }

        for (int i = order - 1; i > 0; i--) {
            if (elementsPointer[i - 1][0] < elementsPointer[i][0]) {
                T* temp = elementsPointer[i];
                elementsPointer[i] = elementsPointer[i - 1];
                elementsPointer[i - 1] = temp;
            }
        }

        T temp;
        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (j != i) {
                    temp = elementsPointer[j][i] / elementsPointer[i][i];
                    for (int k = 0; k < 2 * order; k++) {
                        elementsPointer[j][k] -= elementsPointer[i][k] * temp;
                    }
                }
            }
        }

        for (int i = 0; i < order; i++) {
            temp = elementsPointer[i][i];
            for (int j = 0; j < 2 * order; j++) {
                elementsPointer[i][j] = elementsPointer[i][j] / temp;
            }
        }

        matrix<T> inv (rows(), columns());
        for (int i = 0; i < order; ++i) {
            for (int j = order; j < 2*order; ++j) {
                inv[i][j - order] = elementsPointer[i][j];
            }
        }

        return inv;
    }

    template<typename T>
    std::string matrix<T>::str() const {
        std::stringstream s;
        s << *this;
        return s.str();
    }

    template<typename T>
    std::string matrix<T>::repr() const {
        return str();
    }

    template<typename T>
  matrix<T> operator+(const matrix<T>& a, const matrix<T>& b)
  {
    if((a.rows()!=b.rows()) || (a.columns()!=b.columns()))
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot add matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    matrix<T> c{a};
    return c+=b;
  }

  template<typename T>
  matrix<T> operator-(const matrix<T>& a, const matrix<T>& b)
  {
    if((a.rows()!=b.rows()) || (a.columns()!=b.columns())) 
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot substract matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    matrix<T> c{a};
    return c-=b;
  }

  template<typename T>
  inline matrix<T> operator~(const matrix<T>& m) { return m.make_transpose(); }

  template<typename T>
  inline matrix<T> operator-(const matrix<T>& m)
  {
    matrix<T> r{m}; 

    for(size_t i=0; i<r.rows(); i++)
      for(size_t j=0; j<r.columns(); j++) r[i][j]=-m[i][j];

    return r; 
  }

  template<typename T>
  matrix<T> operator*(const matrix<T>& a, const matrix<T>& b)
  {
    if(a.columns()!=b.rows())
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot multiple matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    matrix<T> c(a.rows(),b.columns());

    for(size_t i=0; i<c.rows(); i++)
      for(size_t j=0; j<c.columns(); j++)
      {
        c[i][j]=0;
        for(size_t k=0; k<a.columns(); k++)
          c[i][j]+=a[i][k]*b[k][j];
      }

    return c;
  }

  template<typename T>
  inline matrix<T> operator*(const matrix<T>& m, typename matrix<T>::element_t scalar) 
  { matrix<T> r{m}; r*=scalar; return r; }

  template<typename T>
  inline matrix<T> operator*(typename matrix<T>::element_t scalar, const matrix<T>& m) 
  { matrix<T> r{m}; r*=scalar; return r; }

  template<typename T>
  inline matrix<T> operator/(const matrix<T>& m, typename matrix<T>::element_t scalar) 
  { matrix<T> r{m}; r/=scalar; return r; }

  template<typename T>
  inline matrix<T> operator/(typename matrix<T>::element_t scalar, const matrix<T>& m) 
  { matrix<T> r{m}; r/=scalar; return r; }

  template<typename T>
  ostream& operator<<(ostream& os, const matrix<T>& m)
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




  /**
   * Class Vector
   */
  /* template<typename T>
  class vector{
  public:
      using element_t=T;

      static_assert(
              is_integral<T>::value ||
              is_floating_point<T>::value ||
              is_same<T,complex<float>>::value ||
              is_same<T,complex<double>>::value ||
              is_same<T,complex<long double>>::value,
              "\n"
              "[ERROR] >>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< [ERROR]\n"
              "[ERROR] >>>> BAD TYPE PROVIDED FOR TEMPLATE mat_lib::matrix! <<<< [ERROR]\n"
              "[ERROR] >>>> ACCEPTED TYPES:                                 <<<< [ERROR]\n"
              "[ERROR] >>>>   - All numeric primitive types                 <<<< [ERROR]\n"
              "[ERROR] >>>>   - std::complex<float>                         <<<< [ERROR]\n"
              "[ERROR] >>>>   - std::complex<double>                        <<<< [ERROR]\n"
              "[ERROR] >>>>   - std::complex<long double>                   <<<< [ERROR]\n"
              "[ERROR] >>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< [ERROR]\n"
      );

      vector();

      vector(size_t maxSize) : max_size__(maxSize) {
          element_t value = 0;
          for(size_t i=0; i<max_size__; i++) container__.push_back(value);
      }

      vector(initializer_list<element_t> init): max_size__{init.size()} {
          for(size_t i=0; i<init.size(); i++) container__.push_back(init.begin()[i]);
      }


      explicit vector(const string& file_name); // constructor from a file

      size_t size() const {
          return max_size__;
      }

      std::string str() const;
      std::string repr() const;

      void define_random();

      void define_value(int value);

      bool operator==(const vector &rhs) const {
          if(this->size() != rhs.size()) return false;

          for (int i = 0; i < rhs.size(); ++i) {
            if(container__[i] != rhs[i]) return false;
          }

          return true;
      }

      bool operator!=(const vector &rhs) const {
          return !(rhs == *this);
      }

      vector operator+=(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad sum operations");

          for (int i = 0; i < rhs.size(); ++i) {
              container__[i] += rhs[i];
          }

          return *this;
      }

      vector operator+(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad sum operations");
          vector<element_t> res(this->size());

          for (int i = 0; i < rhs.size(); ++i) {
              res.set(i,container__[i] + rhs[i]);
          }

          return res;
      }

      vector operator+(const element_t rhs){
          vector<element_t> res(this->size());

          for (int i = 0; i < this->size(); ++i) {
              res.set(i,container__[i] + rhs);
          }

          return res;
      }

      vector operator-(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad sum operations");
          vector<element_t> res(this->size());

          for (int i = 0; i < rhs.size(); ++i) {
              res.set(i,container__[i] - rhs[i]);
          }

          return res;
      }

      vector operator-(const element_t rhs){
          vector<element_t> res(this->size());

          for (int i = 0; i < this->size(); ++i) {
              res.set(i,container__[i] - rhs);
          }

          return res;
      }

      vector operator*(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad sum operations");
          vector<element_t> res(this->size());

          for (int i = 0; i < rhs.size(); ++i) {
              res.set(i,container__[i] * rhs[i]);
          }

          return res;
      }

      vector operator*(const element_t rhs){
          vector<element_t> res(this->size());

          for (int i = 0; i < this->size(); ++i) {
              res.set(i,container__[i] * rhs);
          }

          return res;
      }

      vector operator/(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad sum operations");
          vector<element_t> res(this->size());

          for (int i = 0; i < rhs.size(); ++i) {
              res.set(i,container__[i] - rhs[i]);
          }

          return res;
      }

      vector operator/(const element_t rhs){
          vector<element_t> res(this->size());

          for (int i = 0; i < this->size(); ++i) {
              res.set(i,container__[i] - rhs);
          }

          return res;
      }

      vector operator*=(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad sum operations");

          for (int i = 0; i < rhs.size(); ++i) {
              container__[i] *= rhs[i];
          }

          return *this;
      }

      vector operator-=(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad subtract operations");

          for (int i = 0; i < rhs.size(); ++i) {
              container__[i] -= rhs[i];
          }

          return *this;
      }

      vector operator/=(const vector &rhs){
          if(this->size() != rhs.size()) throw logic_error("bad subtract operations");

          for (int i = 0; i < rhs.size(); ++i) {
              container__[i] /= rhs[i];
          }

          return *this;
      }

      bool is_empty() const{
          return container__.empty();
      }

      friend ostream &operator<<(ostream &os, const vector &vector) {
          os << "mat_lib::vector[" << vector.size() << "]{";

          if(vector.is_empty()){
             os << "}";
             return os;
          }

          auto formatter = vector.getFormat() == mat_lib::fixed ? std::fixed : std::scientific;
          for(int i = 0 ; i < vector.size()-1; i++)
          {
              os << formatter << setprecision(vector.getFractionalDigits()) << vector[i] << ", ";
          }
          os<< vector[vector.size()-1] << "}";
          return os;
      }

      element_t operator[](size_t i) { return container__[i]; }
      const element_t operator[](size_t i) const { return container__[i]; }

      void save_as(const string& file_name) const;

      element_t get(size_t index){
          return container__[index];
      }

      void set(size_t index, element_t value){
          container__[index] = value;
      }

      format getFormat() const;

      int getFractionalDigits() const;

      void setFormat(format format);

      void setFractionalDigits(int fractionalDigits);


  private:
      std::size_t max_size__;
      std::vector<T> container__;

      format format__         = fixed;
      int fractional_digits__ = 6;

      bool is_the_vector_full__(){
          return max_size__ > container__.size();
      }

      void copy_elements__(vector<T> v1);
  };

    template<typename T>
    void vector<T>::copy_elements__(vector<T> v1) {
        for (int i = 0; i < v1.size(); ++i)
            container__.push_back(v1[i]);
    }

    template<typename T>
    format vector<T>::getFormat() const {
        return format__;
    }

    template<typename T>
    int vector<T>::getFractionalDigits() const {
        return fractional_digits__;
    }

    template<typename T>
    void vector<T>::setFormat(format format) {
        format__ = format;
    }

    template<typename T>
    void vector<T>::setFractionalDigits(int fractionalDigits) {
        if(fractionalDigits <= 0) throw logic_error("bad decimal precision");
        fractional_digits__ = fractionalDigits;
    }

    template<typename T>
    void vector<T>::save_as(const string &file_name) const {
        ofstream ofs(file_name);
        if(!ofs)
        {
            ostringstream str_stream;
            str_stream<<"cannot open file \""<<file_name<<"\"! ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw logic_error(str_stream.str());
        }

        auto formatter = format__ == mat_lib::fixed ? std::fixed : std::scientific;
        ofs << formatter << setprecision(fractional_digits__) << *this;
    } */

    /* template<typename T>
    vector<T>::vector(const string &file_name) {
        ifstream ifs(file_name);
        if(!ifs)
        {
            ostringstream str_stream;
            str_stream<<"cannot open file \""<<file_name<<"\"! ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw logic_error(str_stream.str());
        }

        string str((istreambuf_iterator<char>(ifs)),
                   istreambuf_iterator<char>());

        regex rx(R"(mat_lib::vector\[(\d)\]\{(([-+]?\d*\.?\d+([eE][-+]?\d+)?(,\s|\n\s*)?)+)+\})");
        cmatch results;
        if (not regex_match(str.c_str(),results,rx)) {
            throw logic_error("the file are incorrect: bad expresion");
        }

        max_size__ = stoi(results.str(1));
        std::vector<string> numbers;
        boost::split(numbers, results.str(2), boost::is_any_of("(,|\n)"));


        if (numbers.size() != max_size__) {
            throw logic_error("the file are incorrect: bad declaration of matrix");
        }

        for(size_t i=0; i<max_size__; i++) {
            container__.push_back(stod(numbers[i]));
        }

    } */

    /* template<typename T>
    void vector<T>::define_random() {
        for (int i = 0; i < max_size__; ++i) {
            container__[i] = rand();
        }
    }

    template<typename T>
    void vector<T>::define_value(int value) {
        for (int i = 0; i < max_size__; ++i) {
            container__[i] = value;
        }
    }

    template<typename T>
    std::string vector<T>::str() const {
        std::stringstream s;
        s << *this;
        return s.str();
    }

    template<typename T>
    std::string vector<T>::repr() const {
        return str();
    }

    template<typename T>
    vector<T>::vector(): max_size__{0}
    {}

    template<typename T>
    vector<T> operator+(const vector<T>& a, const vector<T>& b)
    {
        if(a.size() != b.size())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vectors ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        vector<T> r(a.size());
        r += a;
        r += b;
        return r;
    }

    template<typename T>
    vector<T> operator-(const vector<T>& a, const vector<T>& b)
    {
        if(a.size() != b.size())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vectors ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        vector<T> r(a.size());
        r += a;
        r -= b;
        return r;
    }

    template<typename T>
    vector<T> operator*(const vector<T>& a, const vector<T>& b)
    {
        if(a.size() != b.size())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vectors ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        vector<T> r(a.size());
        r += a;
        r *= b;
        return r;
    }

    template<typename T>
    vector<T> operator/(const vector<T>& a, const vector<T>& b)
    {
        if(a.size() != b.size())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vectors ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        vector<T> r(a.size());
        r += a;
        r /= b;
        return r;
    }

    template<typename T>
    matrix<T> operator+(const vector<T>& vector, const matrix<T>& matrix)
    {
        if(vector.size() != matrix.columns())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vector and matrix ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        mat_lib::matrix<T> result{matrix};
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.columns(); ++j) {
                result[i][j] += vector[j];
            }
        }
        return result;
    }

    template<typename T>
    matrix<T> operator+(const matrix<T>& matrix,const vector<T>& vector)
    {
        if(vector.size() != matrix.columns())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vector and matrix ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        mat_lib::matrix<T> result{matrix};
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.columns(); ++j) {
                result[i][j] += vector[j];
            }
        }
        return result;
    }

    template<typename T>
    matrix<T> operator*(const vector<T>& vector, const matrix<T>& matrix)
    {
        if(vector.size() != matrix.columns())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vector and matrix ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        mat_lib::matrix<T> result{matrix};
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.columns(); ++j) {
                result[i][j] *= vector[j];
            }
        }
        return result;
    }

    template<typename T>
    matrix<T> operator*(const matrix<T>& matrix,const vector<T>& vector)
    {
        if(vector.size() != matrix.columns())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vector and matrix ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        mat_lib::matrix<T> result{matrix};
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.columns(); ++j) {
                result[i][j] *= vector[j];
            }
        }
        return result;
    }

    template<typename T>
    matrix<T> operator-(const vector<T>& vector, const matrix<T>& matrix)
    {
        if(vector.size() != matrix.columns())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vector and matrix ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        mat_lib::matrix<T> result{matrix};
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.columns(); ++j) {
                result[i][j] -= vector[j];
            }
        }
        return result;
    }

    template<typename T>
    matrix<T> operator-(const matrix<T>& matrix,const vector<T>& vector)
    {
        if(vector.size() != matrix.columns())
        {
            ostringstream str_stream;
            str_stream<<"size mismatch! cannot add vector and matrix ("
                      <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
            throw invalid_argument(str_stream.str());
        }
        mat_lib::matrix<T> result{matrix};
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.columns(); ++j) {
                result[i][j] -= vector[j];
            }
        }
        return result;
    } */

} // namespace mat_lib

#endif //MATRIX_HPP
