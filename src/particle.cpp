#include <assert.h>
#include <FIZX/particle.hpp>

void fizx::Particle::integrate(real duration)
{
    // We don't integreate things with infinite mass.
    if (inverse_mass <= 0.0f) return;

    assert(duration > 0.0);

    // Update linear position.
    position.add_scaled_vector(velocity, duration);

    // Work out the acceleration from the force.
    vec3f resulting_acc = acceleration;

    // Update linear velocity from the acceleration.
    velocity.add_scaled_vector(resulting_acc, duration);

    // Impose drag.
    velocity *= pow(damping, duration);

    // Clear the forces
    clear_forces();
}

void fizx::Particle::set_mass(real mass)
{
    if (mass == 0) throw std::domain_error("Mass cannot be zero");
    if (mass < 0.0f) inverse_mass = 0.0f;
    else inverse_mass = 1.0f / mass;
}

void fizx::Particle::set_position(vec3f pos)
{
    position = pos;
}

void fizx::Particle::set_velocity(vec3f vel)
{
    velocity = vel;
}

void fizx::Particle::set_acceleration(vec3f acc)
{
    acceleration = acc;
}

void fizx::Particle::add_force(vec3f force)
{
    net_force += force;
}

void fizx::Particle::clear_forces()
{
    net_force = vec3f(0, 0, 0);
}

fizx::vec3f fizx::Particle::get_position() const
{
    return position;
}

fizx::vec3f fizx::Particle::get_velocity() const
{
    return velocity;
}

fizx::vec3f fizx::Particle::get_acceleration() const
{
    return acceleration;
}