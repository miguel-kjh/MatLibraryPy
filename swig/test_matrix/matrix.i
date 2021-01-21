%module "matrix"
%{
    #include "matrix.hpp"
%}

%include "std_vector.i"
%include "std_iostream.i"

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


        size_t size() const;
        size_t rows() const;
        size_t columns() const;

        
    };

    ostream& output(ostream& os, const matrix& m);
    
   

}

