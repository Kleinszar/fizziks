
#include <string>
#include <iostream>
#include <assert.h>

#include <FIZX/mat.hpp>
#include "testlib.hpp"

using namespace fizx;
using namespace std;

int main(void)
{
    cout << "TEST MATRIX" << endl;
    bool error = false;

    cout << "Creation and assignment test" << endl;
    mat2f a(vec2f(1.4, 2.4), vec2f(2.1, 4.9));
    mat2f b = mat2f (
        3.4, -2.5,
        -3.2, 1.2
    );
    mat2f c;
    if (T_Fail(c[0][0] == 0, "Initialization not zero")) error = true;
    if (T_Fail(c[0][1] == 0, "Initialization not zero")) error = true;
    if (T_Fail(c[1][0] == 0, "Initialization not zero")) error = true;
    if (T_Fail(c[1][1] == 0, "Initialization not zero")) error = true;


    cout << "Addition test" << endl;
    c = a + b;
    if (T_Fail(compareRealEqual(c[0][0], 4.8), "Matrix addition")) error = true;
    if (T_Fail(compareRealEqual(c[0][1], -0.1), "Matrix addition")) error = true;
    if (T_Fail(compareRealEqual(c[1][0], -1.1), "Matrix addition")) error = true;
    if (T_Fail(compareRealEqual(c[1][1], 6.1), "Matrix addition")) error = true;
    
    cout << "Equality test" << endl;
    if (T_Fail(c == mat2f(4.8, -0.1, -1.1, 6.1), "Matrix addition")) error = true;
    if (T_Fail(c != mat2f(8.8, -0.1, -1.1, 6.1), "Matrix addition")) error = true;
    if (T_Fail(c != mat2f(4.8, -1.1, -1.1, 6.1), "Matrix addition")) error = true;
    if (T_Fail(c != mat2f(4.8, -0.1, -1.1, 0.0), "Matrix addition")) error = true;

    cout << "Template test" << endl;
    mat3f x, y, z;
    mat4f u, v, w;
    mat3x2f p;
    mat2x4f q;
    mat3x4f r;

    cout << "Scaling test" << endl;
    x = mat3f(
        0.000'01, 0.000'01, 0.000'01,
        0.000'01, 0.000'01, 0.000'01,
        0.000'01, 0.000'01, 0.000'01
    );
    y = x * 100'000;
    z = 100'000 * x;

    if (T_Fail(y == z, "Commutative scalar multiplication")) error = true;
    if (T_Fail(y == mat3f(1, 1, 1, 1, 1, 1, 1, 1, 1), "Vec scaling")) error = true;

    cout << "Matrix multiplication test" << endl;
    x = mat3f(
        3, 2, 1,
        4, 5, 6,
        0, 1, 2
    );
    y = mat3f(
        3, 4, -5,
        7, -8, 9,
        -4, 0, 2
    );
    z = mat3f(
        19, -4, 5,
        23, -24, 37,
        -1, -8, 13
    );
    if (T_Fail(x * y == z, "Matrix multiplication")) error = true;

    p = mat3x2f(
        0, 1,
        5, 2,
        1, 1
    );

    q = mat2x4f(
        1, 2, 3, 4,
        5, 6, 7, 8
    );

    r = mat3x4f(
        5, 6, 7, 8,
        15, 22, 29, 36,
        6, 8, 10, 12
    );
    if (T_Fail(p * q == r, "Matrix multiplication")) error = true;

    cout << "Copy and Move semantic test" << endl;
    mat2f o_mat(2, 3, 4, 5);

    mat2f c_mat(o_mat);
    c_mat[0][0] = 0;
    if (T_Fail(o_mat[0][0] == 2, "Copy constructor")) error = true;

    c_mat = o_mat;
    c_mat[0][0] = 0;
    if (T_Fail(o_mat[0][0] == 2, "Copy assignment")) error = true;

    mat2f m_mat(mat2f(0, 1, 2, 3));
    if (T_Fail(m_mat == mat2f(0, 1, 2, 3), "Move constructor")) error = true;
    
    m_mat = mat2f(2, 3, 1, 0);
    if (T_Fail(m_mat == mat2f(2, 3, 1, 0), "Move assignment")) error = true;

    if (error)
    {
        cout << "TEST MATRIX Ended with errors" << endl;
    }   
    else
    {
        cout << "TEST MATRIX PASSED" << endl;
    }

    return error;
}