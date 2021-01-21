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
#include <vector>


using namespace std;

namespace mat_lib
{

    enum format {
        scientific,
        fixed
    };

  //template<typename T>
    class base_matrix {
    public:
        
        format getFormat() const;
        int getFractionalDigits() const;
        void setFormat(format format);
        void setFractionalDigits(int fractionalDigits);

    protected:
        format format__ = fixed;
        int fractional_digits__ = 6;
    };

    class matrix: public base_matrix {
    public:

        matrix();
        matrix(size_t rows, size_t columns);
        matrix(vector<double> init);
        matrix(vector<vector<double>> init);
        


        size_t size() const { return rows__*columns__; }
        size_t rows() const { return rows__; }
        size_t columns() const { return columns__; }


      double* operator[](size_t i) { return &(elements__[row_offset__(i)]); }
      const double* operator[](size_t i) const { return &(elements__[row_offset__(i)]); }


    private:
        size_t rows__;
        size_t columns__;
        double* elements__;

        bool check_initilizer_list__(const vector<vector<double>>& init){
            auto column_size=init.begin()[0].size();
            for(size_t i=1; i<init.size(); i++)
            if(init.begin()[i].size()!=column_size) return false;
            return true;
        }

            
        size_t row_offset__(size_t i) const { return i*columns__; }
        size_t offset__(size_t i,int j) const { return row_offset__(i)+j; }


         
    };

    ostream& output(ostream& os, const matrix& m);

}

#endif