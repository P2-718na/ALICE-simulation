#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "ParticleType.hpp"

namespace sim {

class ResonanceType : public ParticleType {
 public:
  // Constructor ///////////////////////////////////////////////////////////////
  ResonanceType(const char* Name, double Mass, int Charge, double Width);

  // Methods ///////////////////////////////////////////////////////////////////
  // Print resonance info. Calls ParticleType::Print
  void Print() const;

  // Getters ///////////////////////////////////////////////////////////////////
  double GetWidth() const;

 private:
  // Width of resonance
  const double Width_;
};

} // namespace sim

#endif // define RESONANCETYPE_HPP
