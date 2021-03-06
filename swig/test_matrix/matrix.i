%module "matrix"
%{
    #include "matrix.hpp"
%}

%include "std_vector.i"
%include "std_string.i"


%ignore mat_lib::operator/;
%rename(__div__) mat_lib::operator/;

namespace std {
    %template(line) vector <double>;
    %template(vector) vector<vector<double>>;
}

namespace mat_lib {

    enum format {
        scientific,
        fixed
    };

    class base_matrix{
    public:
        format getFormat() const;
        int getFractionalDigits() const;
        void setFormat(format format);
        void setFractionalDigits(int fractionalDigits);

    };

    class matrix : public base_matrix {
    public:
        matrix();
        matrix(size_t rows, size_t columns);
        matrix(std::vector<double> init);
        matrix(std::vector<std::vector<double>> init);
        explicit matrix(const std::string& file_name);


        size_t size() const;
        size_t rows() const;
        size_t columns() const;

        //matrix& operator=(const matrix& m);
        //matrix& operator=(matrix&& m);
        matrix& operator+=(const matrix& m);
        matrix& operator-=(const matrix& m);
        matrix& operator*=(double scalar);
        matrix& operator/=(double scalar);
        bool operator==(const matrix& m) const;

        matrix inverse();
        void save_as(const std::string& file_name);
        
        
    };


    void output(const matrix& m);

    matrix operator+( const matrix& a, const matrix& b);
    matrix operator-( const matrix& a, const matrix& b);
    matrix operator*(const matrix& a, const matrix& b);
    matrix operator*(const matrix& m, double scalar);
    matrix operator*(double scalar, const matrix& m);
    matrix operator/(const matrix& m, double scalar);  
    matrix operator/(double scalar,const matrix& m);
   

}

