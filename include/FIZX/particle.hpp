#ifndef FIZX_PARTICLE
#define FIZX_PARTICLE

#include <FIZX/param.hpp>
#include <FIZX/core.hpp>
#include <stdexcept>
#include <math.h>

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
        Vector3 position;

        /**
         * Holds the linear velocity of the particle in world space.
        */
        Vector3 velocity;

        /**
         * Holds the acceleration of the particle.
         * This value can be used to set acceleration due to gravity.
         * Or any other constant acceleration.
        */
        Vector3 acceleration;

        /**
        * Holds the amount of damping applied to linear
        * motion. Damping is required to remove energy added
        * through numerical instability in the integrator.
        */
        real damping;
        
        /**
        * Holds the inverse of the mass of the particle. It
        * is more useful to hold the inverse mass because
        * integration is simpler, and because in real-time
        * simulation it is more useful to have objects with
        * infinite mass (immovable) than zero mass
        * (completely unstable in numerical simulation).
        */
        real inverseMass;

        /**
        * Holds the accumulated forces on the particle.
        * Forces acting on a mass will result in acceleration.
        */
        Vector3 net_force;

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
        void set_mass(real mass);

        /**
         * Setter for the position (m).
         * @param pos 3D vector of the position of a particle in the world frame.
        */
        void set_position(Vector3 position);

        /**
         * Setter for the velocity (m/s).
         * @param vel 3D vector of the relative velocity in the world frame.
        */
        void set_velocity(Vector3 velocity);

        /**
         * Setter for the acceleration (m/s^2)
         * @param acc 3D vector of the relative acceleration in the world frame.
        */
        void set_acceleration(Vector3 acceleration);

        /**
         * Adds a force to the particle for the next integration step.
         * @param force 3D force vector
        */
        void add_force(Vector3 force);

        /**
         * Sets the net force to the zero vector.
        */
        void clear_forces();

        /**
         * Gets the position of the vector;
         * @return A copy of the position vector.
        */
        Vector3 get_position() const;

        /**
         * Get the velocity of the vector;
         * @return A copy of the velocity vector.
        */
        Vector3 get_velocity() const;

        /**
         * Get the acceleration of the vector;
         * @return A copy of the acceleration vector.
        */
        Vector3 get_acceleration() const;

    };

}

#endif