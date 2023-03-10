#include <FIZX/param.hpp>
#include <FIZX/core.hpp>
#include <FIZX/mat.hpp>
#include <iostream>
#include <chrono>

#include "test_lib.hpp"

using namespace fizx;

int main(void)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    vec3f x(1, 0, 0);
    vec3f y(0, 1, 0);
    vec3f z(0, 0, 1);

    mat3f a(x, y, z);

    mat3f b(
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    );

    mat3f c;
    mat3f d;

    for (int i = 0; i < 1'000'000; ++i)
    {
        b = b * a;
    }

    b[0].x();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "a:\n" << a.to_string() << std::endl;
    std::cout << "b:\n" << b.to_string() << std::endl;
    std::cout << "c:\n" << c.to_string() << std::endl;
    std::cout << "d:\n" << d.to_string() << std::endl;

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    return 0;
}