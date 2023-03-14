/**
 * 
*/

#pragma once

#include "param.hpp"
#include "vec.hpp"
#include <string>

namespace fizx
{

template<typename T, size_t MRows, size_t NCols>
class Matrix;

// Macro
#define MATRIX Matrix<T, MRows, NCols>
#define ROW_VEC Vector<T, NCols>
#define COL_VEC Vector<T, MRows>

// Alias //----------------------------------------------------------------------------------------
using mat2f = Matrix<real, 2, 2>;
using mat3f = Matrix<real, 3, 3>;
using mat4f = Matrix<real, 4, 4>;

using mat2x3f = Matrix<real, 2, 3>;
using mat3x2f = Matrix<real, 3, 2>;
using mat2x4f = Matrix<real, 2, 4>;
using mat4x2f = Matrix<real, 4, 2>;
using mat3x4f = Matrix<real, 3, 4>;
using mat4x3f = Matrix<real, 4, 3>;

template<typename T, size_t MRows, size_t NCols>
class Matrix
{
// Variables //------------------------------------------------------------------------------------
private:
    // Row Major order
    Vector<T, NCols> values[MRows];

// CONSTRUCTORS //---------------------------------------------------------------------------------
public:

    Matrix() : values{{/*Empty*/}} {};

    /**
     * Constructor for a matrix with MRows rows and NCols columns.
     * Takes a total of {MRows} * {NCols} arguments.
     * @param head - first argument.
     * @param tail - rest of the argument list.
    */
    template <typename... Tail>
    Matrix(std::enable_if_t<sizeof...(Tail) + 1 == MRows * NCols, const T> head, const Tail... tail)
    {
        T temp[MRows * NCols] = {head, static_cast<T>(tail)...};
        for (size_t m = 0; m < MRows; ++m)
        {
            for (size_t n = 0; n < NCols; ++n)
            {
                values[m][n] = temp[(NCols * m) + n];
            }
        }

    };


    /**
     * Constructor for a matrix with MRows rows and NCols columns.
     * Takes a total of {MRows} vectors of size {NCols}.
     * @param head - first vector.
     * @param tail - rest of the vectors.
    */
    template <typename... Tail>
    Matrix(std::enable_if_t<sizeof...(Tail) + 1 == MRows, ROW_VEC> head, Tail... tail)
    : values{head, static_cast<ROW_VEC>(tail)...} {};

// OPERATORS //------------------------------------------------------------------------------------
public:

    // Assignment op:

    /**
     * Row Assignment operator.
     * @param index - which row to assign.
    */
    ROW_VEC& operator[](size_t index)
    {
        if (index >= MRows)
            throw std::runtime_error("Index Out of Bounds");
        return values[index];
    };

    // Access op:

    /**
     * Access copy operator.
     * @param index - which row to copy.
    */
    ROW_VEC operator[](size_t index) const
    {
        if (index >= MRows)
            throw std::runtime_error("Index Out of Bounds");
        return values[index];
    };


    // Comparison op:

    bool operator==(const MATRIX& other)
    {
        return std::equal(&values[0], &values[MRows], &other.values[0]);
    }

    bool operator!=(const MATRIX& other)
    {
        return !(*this == other);
    }

    // Matrix Scaling op:

    /**
     * @returns A copy of the matrix, scaled by a real constant.
    */
    MATRIX operator*(real scalar) const
    {
        MATRIX temp;
        for (size_t m = 0; m < MRows; ++m)
        {
            for (size_t n = 0; n < NCols; ++n)
            {
                temp[m][n] = values[m][n] * scalar;
            }
        }
        return temp;
    }

    /**
     * Scales each element by a constant real value.
    */
    void operator*=(real scalar)
    {
        for (size_t m = 0; m < MRows; ++m)
        {
            for (size_t n = 0; n < NCols; ++n)
            {
                values[m][n] *= scalar;
            }
        }
    }

    // Matrix Addition op:
    
    /**
     * Standard matrix addition, element wise.
     * @returns a copy of this matrix added with another matrix of the same dimensions.
    */
    MATRIX operator+(const MATRIX& other) const
    {
        MATRIX temp;
        for (size_t m = 0; m < MRows; ++m) {
            for (size_t n = 0; n < NCols; ++n) {
                temp[m][n] = values[m][n] + other[m][n];
            }
        }
        return temp;
    };

    /**
     * Adds the values of another matrix, element wise.
    */
    void operator+=(const MATRIX& other)
    {
        for (size_t m = 0; m < MRows; ++m) {
            for (size_t n = 0; n < NCols; ++n) {
                values[m][n] += other[m][n];
            }
        }
    };
    
    // Matrix Multiplication op:

    /**
     * Matrix Multiply an MRows by NCols matrix (this) with an NCols by L_ELEMS matrix (other)
     * O(MRows*NCols*L_ELEMS) runtime.
     * @return An MRows by L_ELEMS Matrix.
    */
    template<typename T, size_t LElems>
    Matrix<T, MRows, LElems> operator*(const Matrix<T, NCols, LElems>& other) const
    {
        Matrix<T, MRows, LElems> temp;

        for (size_t m = 0; m < MRows; ++m)
        {
            for (size_t l = 0; l < LElems; ++l)
            {
                T sum = 0;
                for (size_t n = 0; n < NCols; ++n)
                {
                    sum += values[m][n] * other[n][l];
                }
                temp[m][l] = sum;
            }
        }
        return temp;
    }

    /**
     * Multiply a matrix with a vector with dimensions NCols
    */
    ROW_VEC operator*(const COL_VEC& vector) const
    {
        ROW_VEC temp;
        for (size_t m = 0; m < MRows; ++m)
        {
            temp[m] = values[m] * vector;
        }
        return temp;
    }


// METHODS //--------------------------------------------------------------------------------------
public:

    /**
     * Convers the matrix to a string representation.
     * @return A string representation of the matrix.
    */
    std::string to_string() const
    {
        std::string s = "";
        for (size_t m = 0; m < MRows; ++m)
        {
            for (size_t n = 0; n < NCols; ++n)
            {
                s += " " + std::to_string(values[m][n]);
            }
            s += "\n";
        }
        return s;
    }

    /**
     * Gets a row of the matrix (0 indexed)
     * @param index - the index of the row.
    */
    ROW_VEC get_row(size_t index)
    {
        if (index < MRows)
            throw std::runtime_error("Index Out Of Bounds");
        return values[index]
    }

    /**
     * Gets a column of the matrix (0 indexed)
     * @param index - the index of the column.
    */
    COL_VEC get_col(size_t index)
    {
        if (index < NCols)
            throw std::runtime_error("Index Out Of Bounds");
        COL_VEC temp;
        for (size_t m = 0; m < MRows; ++m)
        {
            temp[m] = values[m][index]
        }
        return temp;
    }

    /**
     * Transposes this matrix.
    */
    void transpose()
    {
        *this = get_transpose();
    }

    /**
     * Gets the transpose of the matrix
    */
    Matrix<T, NCols, MRows> get_transpose() const
    {
        Matrix<T, NCols, MRows> temp;
        for (size_t n = 0; n < NCols; ++n)
        {
            temp[n] = get_col(n);
        }
        return temp;
    }

    // COMMON MATRICES //-------------------------------------------------------------------------
    
    MATRIX diagonal(T val)
    {
        MATRIX temp;
        for (size_t i = 0; i < MRows && i < NCols; ++i)
        {
            values[i][i] = val;
        }
        return temp;
    }
    
};

// COMMUTATIVE OPERATORS //-----------------------------------------------------------------------

/**
 * Delegates to the matrix scaling member function.
*/
template <typename T, size_t MRows, size_t NCols>
MATRIX operator*(real scalar, const MATRIX& matrix)
{
    return matrix * scalar;
}

/**
 * Insert matrix representation to a stream.
*/
template <typename T, size_t MRows, size_t NCols>
std::ostream& operator<<(std::ostream& os, const MATRIX& matrix)
{
    os << matrix.to_string();
    return os;
}

static inline void print (void)
{}

template <typename Head, typename... Tail>
static inline void print (Head h, Tail... t)
{
  std::cout << h << std::endl;
  print(t...);
}

// REMOVE TEMPORARY MACROS
#undef MATRIX
#undef ROW_VEC
#undef COL_VEC

} // namespace fizx