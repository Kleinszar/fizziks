/**
 * 
*/

#pragma once

#include <stdexcept>
#include <math.h>

#include "param.hpp"

namespace fizx
{

#define EPSILON_TOLERANCE 0.000'000'1

/**
 * Compares two floating point values with a tolarance of EPSILON_TOLERANCE
*/
bool compareRealEqual(real a, real b) {
    return std::abs(a - b) < EPSILON_TOLERANCE;
}

// REMOVE TEMPORARY MACROS
#undef EPSILON_TOLERANCE

} // namespace fizx