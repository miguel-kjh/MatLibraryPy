#include <iostream>
using namespace std;

#include "matrix.hpp"
using namespace mat_lib;

using matrix_t=matrix<double>;

int main(int arc, char* argv[])
try
{
    cout<<"This is testing_mat_lib!"<<endl;

    cout<<"####################### Test Matrix #######################"<<endl;

    matrix_t a{
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12}
    };
    a.setFractionalDigits(10);
    a.setFormat(mat_lib::scientific);

    cout<<"a="<<a<<endl;

    matrix_t b{a};
    cout<<"b="<<b<<endl;

    a+=b;
    cout<<"a="<<a<<endl;

    matrix_t  c=3.5*(a-b);
    cout<<"c="<<c<<endl;

    matrix_t d=a*3-b;
    cout<<"d="<<d<<endl;

    matrix_t e=-a;
    cout<<"e="<<e<<endl;

    matrix_t f=a.make_transpose();
    cout<<"f="<<f<<endl;

    a/=3;
    cout<<"a="<<a<<endl;

    matrix_t a2=a*a.make_transpose();
    cout<<"a2="<<a2<<endl;

    matrix_t l{1, 2, 3, 4, 5, 6};
    cout<<"l="<<l<<endl;

    cout<<"l*lt="<<l*~l<<endl;

    cout<<"lt*l="<<~l*l<<endl;

    matrix_t at=~a;
    cout<<"at="<<at<<endl;
    cout<<"at*a="<<~a*a<<endl;
    cout<<"a*at="<<a*~a<<endl;

    a.save_as("a.matrix");
    at.save_as("at.matrix");
    (~l*l).save_as("ltl.matrix");

    matrix_t g{"ltl.matrix"};
    cout<<"g="<<g<<endl;

    cout<<~matrix_t{"at.matrix"}<<endl;

    cout<<"at = "<<matrix_t{"at.matrix"}<<endl;

    cout<<boolalpha<<(at==matrix_t{"at.matrix"})<<endl;

    cout<<"####################### Test Vector #######################"<<endl;

    mat_lib::vector<float> v1 = {1,2,3,4};
    //v1.setFractionalDigits(1);
    //v1.setFormat(mat_lib::scientific);

    cout << v1 << endl;

    cout << v1[0] << endl;

    mat_lib::vector<float> v2(5);
    cout << v2 << endl;

    cout << (v1 == v2) << endl;
    cout << (v1 != v2) << endl;
    cout << (v1 == v1) << endl;

    mat_lib::vector<float> v3 = {-1,-2,-3,-4};

    cout << (v1 += v3) << endl;
    cout << (v1 -= v3) << endl;

    cout << "mult " << v1 * v3 << endl;

    v1.save_as("v.vector");

    mat_lib::vector<double> v_file{"v.vector"};

    cout << "file vector " << v_file << endl;

    mat_lib::vector<double> v4 = {1,2,3,4};
    matrix_t n{
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12}
    };
    cout << "sum vector and matrix:  " << n * v4 << endl;

    mat_lib::matrix<double> inv{
            {5,  7,  9},
            {4,  3,  8},
            {7,  5,  6}
    };

    /*
     Inversa
    -0.209524, 0.028571, 0.276190
    0.304762, -0.314286, -0.038095
    -0.009524, 0.228571, -0.123810
     */


    cout << "Inv is possible\n" << inv.inverse() << endl;

    /*double** test_pointer;
    matrix_t test = test_pointer;*/


    return 0;
}
catch(exception& e)
{ cerr<<"[EXCEPTION] "<<e.what()<<endl; }
