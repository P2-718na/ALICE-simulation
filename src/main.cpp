#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
  sim::ParticleType* Particles[2];

  Particles[0] = new sim::ParticleType{"Nome", 1, 1};
  Particles[1] = new sim::ResonanceType{"Nome2", 2, -1, 0.5};

  Particles[0]->Print();
  Particles[1]->Print();
}
