#ifndef FIZX_CORE
#define FIZX_CORE

#include <FIZX/param.hpp>
#include <stdexcept>
#include <math.h>

namespace fizx {

    /**
     * 3D vector. 4 real data members are allocated for alignment.
    */
    class Vector3
    {
    public:
        real x; // Coordinate along x-axis (Usually left)
        real y; // Coordinate along y-axis (Usually upward)
        real z; // Coordinate along z-axis (Usually away into the screen)

    private:
        // Pad to make the vector a set of 4 floating point values in memory. Purely for performance.
        real pad;

    public:
        // CONSTRUCTORS //----------------------------------------------------------------------------
        /**
         * Default constructor creates the zero vector.
        */
        Vector3() : x(0), y(0), z(0) {}

        /**
         * Creates a vector with the given components.
        */
        Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}


        // OPERATORS //-------------------------------------------------------------------------------
        
        // Assignment
        /**
         * Assignment this vector's parameters to equal the given vector's.
        */
        void operator=(const Vector3& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }


        // Comparison
        /**
         * All components equal check.
        */
        bool operator==(const Vector3& v) const
        {
            return (x == v.x) && (y == v.y) && (z == v.z);
        }

        /**
         * Not all components equal check
        */
        bool operator!=(const Vector3& v) const
        {
            return !((*this) == v);
        }


        // Vector Scaling
        /**
         * Returns a copy of this vector scaled by the given value.
        */
        Vector3 operator*(const real s) const
        {
            return Vector3(x*s, y*s, z*s);
        }

        /**
         * Multiplying a vector by a scalar.
        */
        void operator*=(const real s)
        {
            x *= s;
            y *= s;
            z *= s;
        }


        // Vector Addition
        /**
         * Returns a copy of this vector added with another vector.
        */
        Vector3 operator+(const Vector3& v) const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        /**
         * Vector addition.
        */
        void operator+=(const Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        /**
         * Returns a copy of this vector subtracted by another vector.
        */
        Vector3 operator-(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        /**
         * Vector subtraction.
        */
        void operator-=(const Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }


        // Vector Multiplication
        /**
         * Dot product with another vector.
        */
        real dot_product(const Vector3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        /**
         * Cross product with another vector.
        */
        Vector3 cross_product(const Vector3& v) const
        {
            return Vector3(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            );
        }

        /**
        * Calculates and returns the cross product of this vector
        * with the given vector.
        */
        Vector3 operator%(const Vector3 &v) const
        {
            return this->cross_product(v);
        }

        /**
        * Updates this vector to be the cross product of its current
        * value and the given vector.
        */
        void operator %=(const Vector3 &v)
        {
            *this = cross_product(v);
        }

        /**
        * Calculates and returns a component-wise product of this
        * vector with the given vector.
        */
        Vector3 component_product(const Vector3 &v) const
        {
            return Vector3(x * v.x, y * v.y, z * v.z);
        }

        /**
        * Performs a component-wise product with the given vector and
        * sets this vector to its result.
        */
        void component_product_update(const Vector3 &v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
        }


        // Compound Operations
        /**
        * Adds a scaled vector to this vector.
        * @param v vector to scale then add.
        * @param s scaling factor.
        */
        void add_scaled_vector(const Vector3& v, real s)
        {
            x += v.x * s;
            y += v.y * s;
            z += v.z * s;
        }


        // METHODS //---------------------------------------------------------------------------------
        
        // Properties
        /**
         * @return The magnitude of this vector.
        */
        real magnitude() const
        {
            return sqrt(x*x + y*y + z*z);
        }

        /**
         * @return The squared of the magnitude of this vector.
        */
        real square_magnitude() const
        {
            return x*x + y*y + z*z;
        }


        // Mutative
        /**
         * Swaps the sign of every component in the vector.
        */
        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        /**
         * Convert the vector into a unit vector.
        */
        void normalize()
        {
            real l = magnitude();
            if (l > 0)
            {
                (*this) *= ((real)l)/l;
            }
        }

        /**
         * Constructs an orthonormal basis from two non parallel vectors.
         * Changes the components of the 3 given vectors to form an orthonormal basis.
         * @param a Any non-zero vector.
         * @param b Any non-zero vector NOT parallel to a.
         * @param c Any vector.
         * @throw Domain error when a and b are parallel.
        */
        void make_orthonormal_basis(Vector3 *a, Vector3 *b, Vector3 *c)
        {
            a->normalize();
            (*c) = (*a) % (*b);
            if (c->square_magnitude() == 0.0) throw std::domain_error("First two vectors are parallel");
            c->normalize();
            (*b) = (*c) % (*a);
        }

    };
}

#endif