#include <string>
#include <iostream>

#include <assert.h>
#include <FIZX/core.h>

using namespace fizx;
using namespace std;

void display_vector3(string prefix, Vector3 v)
{
    cout << prefix << v.x << ", " << v.y << ", " << v.z << "\n";
}


int main(void)
{
    Vector3 a(1, 2, 3);
    Vector3 b = Vector3(2, 4, 6);
    Vector3 c = a + b;
    Vector3 expected(10, 0, 1);
    expected = Vector3(3, 6, 9);
    display_vector3("Expected: ", expected);
    display_vector3("Got: ", c);
    if (c != expected) return 1;
    assert(c.x == expected.x && c.y == expected.y && c.z == expected.z);
    return 0;

    



}