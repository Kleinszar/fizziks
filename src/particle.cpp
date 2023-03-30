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
    if (inverseMass_ <= 0.0f) return;

    assert(duration > 0.0);

    // Update linear position.
    position_.addScaledVector(velocity_, duration);


    // Work out the acceleration from the force.
    vec3f resultingAcc = acceleration_;
    // Acceleration = Force * mass^-1
    resultingAcc.addScaledVector(forceAccum_, inverseMass_);


    // Update linear velocity from the acceleration.
    velocity_.addScaledVector(resultingAcc, duration);

    // Impose drag.
    velocity_ *= pow(damping_, duration);

    // Clear the forces
    clearAccum();
}

void Particle::setMass(real mass)
{
    if (mass == 0) throw std::domain_error("Mass cannot be zero");
    if (mass < 0.0f) inverseMass_ = 0.0f;
    else inverseMass_ = 1.0f / mass;
}

void Particle::setPosition(vec3f pos)
{
    position_ = pos;
}

void Particle::setVelocity(vec3f vel)
{
    velocity_ = vel;
}

void Particle::setAcceleration(vec3f acc)
{
    acceleration_ = acc;
}

void Particle::addForce(vec3f force)
{
    forceAccum_ += force;
}

void Particle::clearAccum()
{
    forceAccum_ = vec3f(0.0, 0.0, 0.0);
}

vec3f Particle::position() const
{
    return position_;
}

vec3f Particle::velocity() const
{
    return velocity_;
}

vec3f Particle::acceleration() const
{
    return acceleration_;
}

} // namespace fizx