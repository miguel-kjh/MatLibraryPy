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
        explicit matrix(const string& file_name);

        matrix(const matrix& m) // copy constructor
        : elements__{new double[m.size()]}
        { copy_elements__(m); }

        matrix(matrix&& m)// move constructor
        : rows__{m.rows__},
            columns__{m.columns__},
            elements__{m.elements__}
        {
            m.elements__=nullptr;
            m.rows__=m.columns__=0;
        }
        

        size_t size() const { return rows__*columns__; }
        size_t rows() const { return rows__; }
        size_t columns() const { return columns__; }

        matrix& operator=(const matrix& m);
        matrix& operator=(matrix&& m);
        matrix& operator+=(const matrix& m);
        matrix& operator-=(const matrix& m);
        matrix& operator*=(double scalar);
        matrix& operator/=(double scalar);
        bool operator==(const matrix& m) const;

        double* operator[](size_t i) { return &(elements__[row_offset__(i)]); }
        const double* operator[](size_t i) const { return &(elements__[row_offset__(i)]); }

        void save_as(const string &file_name) const;

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

        void copy_elements__(const matrix& m) { 
            rows__=m.rows__; columns__=m.columns__;
            for(size_t i=0; i<rows__; i++) 
            for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]=m.elements__[offset__(i,j)]; 
        }

            
        size_t row_offset__(size_t i) const { return i*columns__; }
        size_t offset__(size_t i,int j) const { return row_offset__(i)+j; }


         
    };

    matrix operator+( const matrix& a, const matrix& b);
    matrix operator-( const matrix& a, const matrix& b);
    matrix operator*(const matrix& a, const matrix& b);
    matrix operator*(const matrix& m, double scalar);
    matrix operator*(double scalar, const matrix& m);
    matrix operator/(const matrix& m, double scalar);  
    matrix operator/(double scalar,const matrix& m);


    ostream& operator<<(ostream& os, const matrix& m);
    void output(const matrix& m);
    

}

#endif