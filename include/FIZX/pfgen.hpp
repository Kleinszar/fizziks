
#pragma once

#include <vector>
#include <memory>

#include "param.hpp"
#include "particle.hpp"
#include "vec.hpp"


namespace fizx
{

/**
 * Abstract class to add a force to a particle.
*/
class ParticleForceGenerator
{
public:
    /**
     * Overload this in implentations of the interface to
     * calculate and update the force applied to the given partcle.
    */
    virtual void updateForce(Particle* particle, real duration) = 0;
};

class ParticleForceRegistry
{
protected:

    struct ParticleForceRegistration
    {
        Particle* particle;
        ParticleForceGenerator* fg;
    };

    typedef std::vector<ParticleForceRegistration> Registry;
    Registry registrations_;

public:

    /**
     * Registers the given force generator to apply to the given particle.
    */
    void add(Particle* particle, const ParticleForceGenerator* fg);

    /**
     * Removes the given registeted pair from the registry.
     * If the pair is not registered, this method will have no effect.
    */
    void remove(const Particle* particle, const ParticleForceGenerator* fg);

    /**
     * Clears all the registrations from the registry.
     * This will not delete the particles or the force generators.
     * Only the connections are cleared.
    */
    void clear();

    /**
     * Calls all the force generators to update the forces of
     * their corresponding particles.
    */
    void updateForces(real duration);
};


class ParticleGravity : public ParticleForceGenerator
{
private:
    /** Holds the acceleration due to gravity. */
    vec3f gravity_;

public:

    /** Creates the generator with the given acceleration. */
    ParticleGravity(const vec3f& gravity);

    /** Applies the gravitational force to the given particle */
    virtual void updateForce(Particle* particle, real duration);
};


class ParticleDrag : public ParticleForceGenerator
{
private:
    /** Holds the velocity drag coefficient */
    real k1_;

    /** Holds the velocity squared drag coefficient */
    real k2_;

public:

    /** Creates the generator with the given coefficients. */
    ParticleDrag(real k1, real k2);

    /** Applies the gravitational force to the given particle */
    virtual void updateForce(Particle* particle, real duration);
};


} // namespace fixz