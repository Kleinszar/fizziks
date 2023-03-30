/**
 * 
*/

#pragma once

#include <stdexcept>
#include <math.h>
#include "param.hpp"
#include "core.hpp"
#include "vec.hpp"

namespace fizx
{
/**
 * A simple point.
*/
class Particle
{
protected:
    /**
     * Holds the linear position of the particle in world space.
    */
    vec3f position_;

    /**
     * Holds the linear velocity of the particle in world space.
    */
    vec3f velocity_;

    /**
     * Holds the acceleration of the particle.
     * This value can be used to set acceleration due to gravity.
     * Or any other constant acceleration.
    */
    vec3f acceleration_;

    /**
    * Holds the amount of damping applied to linear
    * motion. Damping is required to remove energy added
    * through numerical instability in the integrator.
    */
    real damping_;
    
    /**
    * Holds the inverse of the mass of the particle. It
    * is more useful to hold the inverse mass because
    * integration is simpler, and because in real-time
    * simulation it is more useful to have objects with
    * infinite mass (immovable) than zero mass
    * (completely unstable in numerical simulation).
    */
    real inverseMass_;

    /**
    * Holds the accumulated forces on the particle.
    * Forces acting on a mass will result in acceleration.
    */
    vec3f forceAccum_;

public:
    /**
    * Integrates the particle forward in time by the given amount.
    * This function uses a Newton-Euler integration method, which is a
    * linear approximation to the correct integral. For this reason it
    * may be inaccurate in some cases.
    */
    void integrate(real duration);
    
    /**
     * Setter for the mass (kg)
     * @param mass The mass in (kg), use a negative real number to set an infinite mass. Cannot be zero.
    */
    void setMass(real mass);

    /**
     * Setter for the position (m).
     * @param pos 3D vector of the position of a particle in the world frame.
    */
    void setPosition(vec3f position);

    /**
     * Setter for the velocity (m/s).
     * @param vel 3D vector of the relative velocity in the world frame.
    */
    void setVelocity(vec3f velocity);

    /**
     * Setter for the acceleration (m/s^2)
     * @param acc 3D vector of the relative acceleration in the world frame.
    */
    void setAcceleration(vec3f acceleration);

    /**
     * Adds a force to the particle for the next integration step.
     * @param force 3D force vector
    */
    void addForce(vec3f force);

    /**
     * Sets the net force to the zero vector.
    */
    void clearAccum();
    
    /**
     * Gets the position of the vector;
     * @return A copy of the position vector.
    */
    vec3f position() const;

    /**
     * Get the velocity of the vector;
     * @return A copy of the velocity vector.
    */
    vec3f velocity() const;

    /**
     * Get the acceleration of the vector;
     * @return A copy of the acceleration vector.
    */
    vec3f acceleration() const;

    /**
     * Checks if the particle has infinite mass.
    */
    bool hasInfiniteMass() const;
};

} // namespace fizx