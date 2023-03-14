/**
 * 
*/

#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>

#include "param.hpp"
#include "common.hpp"
#include <array>


namespace fizx
{

template<typename T, size_t NElems>
class Vector;

// Macro
#define VECTOR Vector<T, NElems>

// Alias
using vec4f = Vector<real, 4>;
using vec3f = Vector<real, 3>;
using vec2f = Vector<real, 2>;

template<typename T, size_t NElems>
class Vector
{
// Variables //------------------------------------------------------------------------------------
private:
    // Array of elements
    //T values [NElems];
    std::array<T, NElems> values;

// CONSTRUCTORS //----------------------------------------------------------------------------
public:
    Vector() : values{{/*Empty*/}} {};

    /**
     * Constructor for a vector of dimension NElems.
     * @param head - first argument.
     * @param tail - rest of the argument list.
    */
    template <typename... Tail>
    Vector(std::enable_if_t<sizeof...(Tail) + 1 == NElems, T> head, Tail... tail)
    : values{head, static_cast<T>(tail)...} {};

// OPERATORS //-------------------------------------------------------------------------------
public:

    // Assignment:

    /**
     * Element Assignment operator.
     * @param index - which element to change.
    */
    real& operator[](size_t index)
    {
        if (index >= NElems)
            throw std::runtime_error("Index Out of Bounds");
        return values[index];
    }

    // Access:

    /**
     * Gets the element at the specified index.
     * @returns the element at the index.
    */
    real operator[](size_t index) const
    {
        if (index >= NElems)
            throw std::runtime_error("Index Out of Bounds");
        return values[index];
    };


    // Comparison:

    /**
     * Compares element by element if two vectors are equal.
    */
    bool operator==(const VECTOR& other)
    {
        for (size_t n = 0; n < NElems; ++n)
        {
            if (!compare_real_equal(values[n], other[n]))
                return false;
        }
        return true;
    }

    /**
     * Gives the negation of the equality operator.
    */
    bool operator!=(const VECTOR& other)
    {
        return !(*this == other);
    }


    // Vector Scaling:

    /**
     * @returns A copy of the vector, scaled by a real constant.
    */
    VECTOR operator*(real scalar) const
    {
        VECTOR temp;
        for (size_t n = 0; n < NElems; ++n) {

            temp[n] = values[n] * scalar;
        }
        return temp;
    };

    /**
     * Scales each element by a constant real value.
    */
    void operator*=(real scalar)
    {
        for (size_t n = 0; n < NElems; ++n) {
            values[n] *= scalar;
        }
    };


    // Vector Addition:

    /**
     * @returns a copy of this vector added with another vector of the same dimensions.
    */
    VECTOR operator+(const VECTOR& other) const
    {
        VECTOR temp;
        for (size_t n = 0; n < NElems; ++n) {
            temp[n] = values[n] + other[n];
        }
        return temp;
    };

    /**
     * Adds the values of another vector, element wise.
    */
    void operator+=(const VECTOR& other)
    {
        for (size_t n = 0; n < NElems; ++n) {
            values[n] += other[n];
        }
    };

    /**
     * @returns a copy of this vector added with another vector of the same dimensions.
    */
    VECTOR operator-(const VECTOR& other) const
    {
        VECTOR temp;
        for (size_t n = 0; n < NElems; ++n) {
            temp[n] = values[n] - other[n];
        }
        return temp;
    };

    /**
     * Adds the values of another vector, element wise.
    */
    void operator-=(const VECTOR& other)
    {
        for (size_t n = 0; n < NElems; ++n) {
            values[n] -= other[n];
        }
    };

    // Vector Multiplication:

    /**
     * @returns the vector's dot product with another vector.
    */
    real operator*(const VECTOR& other) const
    {
        T dot_product = 0;
        for (size_t n = 0; n < NElems; ++n) {
            dot_product += values[n] * other[n];
        }
        return dot_product;
    };

    /**
     * Scales each element with the corresponding value (index wise) of another vector.
    */
    void operator*=(const VECTOR& other)
    {
        for (size_t n = 0; n < NElems; ++n) {
            values[n] *= other[n];
        }
    };

// PROPERTIES //-----------------------------------------------------------------------------------
public:
    /**
     * Dimension of the vector
     * @return the number of elements
    */
    size_t size()
    {
        return NElems;
    }

    /**
     * Convers the vector to a string representation.
     * @return A string representation of the vector.
    */
    std::string to_string() const
    {
        std::string s = "";
        for (size_t n = 0; n < NElems; ++n)
        {
            s += " " + std::to_string(values[n]);
        }
        return s;
    }

    /**
     * Gets the first element of the vector
     * @return the first element
    */
    template <typename Q = T>
    std::enable_if_t<(NElems > 0), Q> x() const
    {
        return values[0];
    }

    /**
     * Gets the second element of the vector
     * @return the second element
    */
    template <typename Q = T>
    std::enable_if_t<(NElems > 1), Q> y() const
    {
        return values[1];
    }

    /**
     * Gets the third element of the vector
     * @return the third element
    */
    template <typename Q = T>
    std::enable_if_t<(NElems > 2), Q> z() const
    {
        return values[2];
    }

    /**
     * Gets the fourth element of the vector
     * @return the fourth element
    */
    template <typename Q = T>
    std::enable_if_t<(NElems > 3), Q> w() const
    {
        return values[3];
    }


// METHODS //---------------------------------------------------------------------------------
public:
    /**
     * Add a scaled other vector to this vector.
     * @param other - the other vector to add.
     * @param scalar - the value to scale the other vector by.
    */
    void add_scaled_vector(VECTOR& other, real scalar)
    {
        for (size_t n = 0; n < NElems; ++n) {
            values[n] +=  other[n] *scalar;
        }
    }

    /**
     * Initialize all elements to one value.
     * @param val - the value to set for every element.
    */
    VECTOR init(T val)
    {
        for (size_t n = 0; n < NElems; ++n)
        {
            values[n] = val;
        }
    }

};

// COMMOM OPERATORS //-----------------------------------------------------------------------

/**
 * Delegates to the vector scaling member function.
*/
template <typename T, size_t NElems>
VECTOR operator*(real scalar, const VECTOR& vector)
{
    return vector * scalar;
}

/**
 * Insert vector representation to a stream.
*/
template <typename T, size_t NElems>
std::ostream& operator<<(std::ostream& os, const VECTOR& vector)
{
    os << vector.to_string();
    return os;
}

// REMOVE TEMPORARY MACROS
#undef VECTOR

} // namespace fizx