#include "ParticleType.hpp"

#include <iostream>

using std::endl;

namespace sim {
// Constructor /////////////////////////////////////////////////////////////////
ParticleType::ParticleType(const char* Name, double Mass, int Charge)
  : Name_{Name}
  , Mass_{Mass}
  , Charge_{Charge}
{}

// Methods /////////////////////////////////////////////////////////////////////
void ParticleType::Print()  const {
  std::cout << "Particle name: "   << Name_   << endl
            << "Particle mass: "   << Mass_   << endl
            << "Particle charge: " << Charge_ << endl;
}

// Getters /////////////////////////////////////////////////////////////////////
const char* ParticleType::GetName() const {
  return Name_;
}

double ParticleType::GetMass() const {
  return Mass_;
}

int ParticleType::GetCharge() const {
  return Charge_;
}
double ParticleType::GetWidth() const {
  return 0;
}

} // namespace sim
