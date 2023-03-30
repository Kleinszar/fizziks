#include <assert.h>
#include <FIZX/particle.hpp>

namespace fizx
{

///////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS Particle //-------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////

void Particle::integrate(real duration)
{
    // We don't integreate things with infinite mass.
    if (inverseMass <= 0.0f) return;

    assert(duration > 0.0);

    // Update linear position.
    position.addScaledVector(velocity, duration);


    // Work out the acceleration from the force.
    vec3f resultingAcc = acceleration;
    // Acceleration = Force * mass^-1
    resultingAcc.addScaledVector(forceAccum, inverseMass);


    // Update linear velocity from the acceleration.
    velocity.addScaledVector(resultingAcc, duration);

    // Impose drag.
    velocity *= pow(damping, duration);

    // Clear the forces
    clearAccum();
}

void Particle::setMass(real mass)
{
    if (mass == 0) throw std::domain_error("Mass cannot be zero");
    if (mass < 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
}

void Particle::setPosition(vec3f pos)
{
    position = pos;
}

void Particle::setVelocity(vec3f vel)
{
    velocity = vel;
}

void Particle::setAcceleration(vec3f acc)
{
    acceleration = acc;
}

void Particle::addForce(vec3f force)
{
    forceAccum += force;
}

void Particle::clearAccum()
{
    forceAccum = vec3f(0.0, 0.0, 0.0);
}

vec3f Particle::getPosition() const
{
    return position;
}

vec3f Particle::getVelocity() const
{
    return velocity;
}

vec3f Particle::getAcceleration() const
{
    return acceleration;
}

} // namespace fizx