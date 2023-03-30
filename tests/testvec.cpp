#include <string>
#include <iostream>
#include <assert.h>

#include <FIZX/vec.hpp>
#include "testlib.hpp"

using namespace fizx;
using namespace std;

int main(void)
{
    cout << "TEST VECTOR" << endl;
    bool error = false;

    cout << "Floating point comparison test" << endl;
    T_Assert(compareRealEqual(0.13, 0.13), "Floating point comparision");
    T_Assert(compareRealEqual(-135.7, -135.7), "Floating point comparision");
    T_Assert(compareRealEqual(1'000'000'000.1, 999'999'999.1 + 1.0), "Floating point comparision");
    T_Assert(compareRealEqual(333'000.47859, 333'000.47000 + 0.00859), "Floating point comparision");

    cout << "Creation and assignment test" << endl;
    vec2f a(1.4, 2.4), b(-2.1, 4.9), c;

    if (c[0] != 0 || c[1] != 0)
    {
        cout << "Fail: Vec init non zero: " << c.toString() << endl;
        error = true;
    }

    cout << "Addition test" << endl;
    c = a + b;
    if (T_Fail(compareRealEqual(c[0], -0.7), "Vec addition")) error = true;
    if (T_Fail(compareRealEqual(c[1], 7.3), "Vec addition")) error = true;

    cout << "Equality test" << endl;
    if (T_Fail(c == vec2f(-0.7, 7.3), "Equality operator")) error = true;
    if (T_Fail(c != vec2f(0.123, -456), "Inequality operator")) error = true;

    cout << "Template test" << endl;
    vec3f x, y, z;
    vec4f u, v, w;


    cout << "Scaling test" << endl;
    x = vec3f(0.00001, 0.00001, 0.00001);
    y = x * 3;
    z = 3 * x;

    if (T_Fail(y == z, "Commutative scalar multiplication")) error = true;
    if (T_Fail(y == vec3f(0.00003, 0.00003, 0.00003), "Vec scaling")) error = true;
    x *= vec3f(10, 100, 1000);
    if (T_Fail(x == vec3f(0.0001, 0.001, 0.01), "Vec scaling element wise")) error = true;

    cout << "Additional functionality test" << endl;
    u = vec4f(0.3, 0.3, 0.3, 0.3);
    v = vec4f(5, 5, 5, 5);
    w = vec4f(0, 0, 0, 0);
    u.addScaledVector(v, 0.2);
    w.addScaledVector(vec4f(7.4, 7.4, 7.4, 7.4), 0.5);
    v -= u;

    if (T_Fail(w == vec4f(3.7, 3.7, 3.7, 3.7), "Add scaled vector")) error = true;
    if (T_Fail(v == w, "Add scaled vector")) error = true;

    cout << "Property test" << endl;
    if (T_Fail(v.size() == 4, "Size property")) error = true;
    v = vec4f(u.x(), u.y(), u.z(), u.w());
    if (T_Fail(v == u, "Element alias property")) error = true;
    
    cout << "Dot product test" << endl;
    u = vec4f(1, 2, -3, -2);
    v = vec4f(-1, 2, 4, 0.5);
    if (T_Fail(u * v == -10, "Dot product")) error = true;


    cout << "Copy and Move semantic test" << endl;
    vec2f o_vec(2, 3);

    vec2f c_vec(o_vec);
    c_vec[0] = 0;
    if (T_Fail(o_vec[0] == 2, "Copy constructor")) error = true;

    c_vec = o_vec;
    c_vec[0] = 0;
    if (T_Fail(o_vec[0] == 2, "Copy assignment")) error = true;

    vec2f m_vec(vec2f(0, 1));
    if (T_Fail(m_vec == vec2f(0, 1), "Move constructor")) error = true;
    
    m_vec = vec2f(2, 3);
    if (T_Fail(m_vec == vec2f(2, 3), "Move assignment")) error = true;



    if (error)
    {
        cout << "TEST VECTOR Ended with errors" << endl;
    }   
    else
    {
        cout << "TEST VECTOR PASSED" << endl;
    }

    return error;
}