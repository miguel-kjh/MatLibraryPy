%module "matrix"
%{
    #include "matrix.hpp"
%}

namespace mat_lib {

    enum format {
        scientific,
        fixed
    };
    
    // template<typename T>
    class base_matrix{
    public:
        base_matrix(int);
        format getFormat() const;
        int getFractionalDigits() const;
        void setFormat(format format);
        void setFractionalDigits(int fractionalDigits);

    };

}

//using namespace mat_lib;

//%template(cin) base_matrix<int>;
//template class base_matrix<int>;