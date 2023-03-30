
#include <FIZX/param.hpp>
#include <FIZX/pfgen.hpp>


namespace fizx
{

///////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS ParticleForceRegistry //------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////

void ParticleForceRegistry::updateForces(real duration)
{
    for (auto i = registrations.begin(); i != registrations.end(); ++i)
    {
        i->fg->updateForce(i->particle, duration);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS ParticleGravity //------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////

void ParticleGravity::updateForce(Particle* particle, real duration)
{
    // CHeck that we do not have infinite mass.
    
    // Apply the mass-scaled force to the particle.
}

} // namespace fizx