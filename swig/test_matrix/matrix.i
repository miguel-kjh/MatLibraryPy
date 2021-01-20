%module "matrix"
%{
    #include "matrix.hpp"
%}

namespace mat_lib {

    enum format {
        scientific,
        fixed
    };
    
    //template<typename T>
    class base_matrix{
    public:
        //base_matrix(int);
        format getFormat() const;
        int getFractionalDigits() const;
        void setFormat(format format);
        void setFractionalDigits(int fractionalDigits);

    };

    class matrix : public base_matrix {
    public:
        matrix();
        matrix(size_t rows, size_t columns);
        //matrix(initializer_list<int> init);


        size_t size() const;
        size_t rows() const;
        size_t columns() const;

    };

    //%template(base_matrixInt) base_matrix<int>;
    //%template(base_matrixDouble) base_matrix<double>;

}

