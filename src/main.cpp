#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "Particle.hpp"

int main() {
  sim::Particle::AddParticleType("pion", 134.9, 0);
  sim::Particle::AddParticleType("positron", 0.5109, 1);

  sim::Particle::PrintParticleTypes();

  sim::Particle particle("pion", 0, 0, 0);

  particle.SetIndex("positron");
}
