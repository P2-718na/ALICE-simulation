#include "ResonanceType.hpp"

#include <iostream>

using std::endl;

namespace sim {
// Constructor /////////////////////////////////////////////////////////////////
ResonanceType::ResonanceType(const char* Name, double Mass, int Charge, double Width)
  : ParticleType(Name, Mass, Charge)
  , Width_{Width}
{}

// Methods /////////////////////////////////////////////////////////////////////
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Resonance width: " << Width_ << endl;
}

// Getters /////////////////////////////////////////////////////////////////////
double ResonanceType::GetWidth() const {
  return Width_;
}

}
