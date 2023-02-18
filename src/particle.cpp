#include <assert.h>
#include <FIZX/particle.hpp>

void fizx::Particle::integrate(real duration)
{
    // We don't integreate things with infinite mass.
    if (inverseMass <= 0.0f) return;

    assert(duration > 0.0);

    // Update linear position.
    position.add_scaled_vector(velocity, duration);

    // Work out the acceleration from the force.
    Vector3 resultingAcc = acceleration;

    // Update linear velocity from the acceleration.
    velocity.add_scaled_vector(resultingAcc, duration);

    // Impose drag.
    velocity *= pow(damping, duration);

    // Clear the forces
    clear_forces();
}

void fizx::Particle::set_mass(real mass)
{
    if (mass == 0) throw std::domain_error("Mass cannot be zero");
    if (mass < 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
}

void fizx::Particle::set_position(Vector3 pos)
{
    position = pos;
}

void fizx::Particle::set_velocity(Vector3 vel)
{
    velocity = vel;
}

void fizx::Particle::set_acceleration(Vector3 acc)
{
    acceleration = acc;
}

void fizx::Particle::add_force(Vector3 force)
{
    net_force += force;
}

void fizx::Particle::clear_forces()
{
    net_force = Vector3(0, 0, 0);
}

fizx::Vector3 fizx::Particle::get_position() const
{
    return position;
}

fizx::Vector3 fizx::Particle::get_velocity() const
{
    return velocity;
}

fizx::Vector3 fizx::Particle::get_acceleration() const
{
    return acceleration;
}