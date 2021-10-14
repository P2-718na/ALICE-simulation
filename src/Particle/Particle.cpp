#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include <cstring>
#include <cmath>
#include <exception>
#include <iostream>

using std::endl;

namespace sim {

ParticleType* Particle::ParticleTypes_[MAX_NUM_PARTICLES];
int Particle::NParticleTypes_{0};

// Constructors ////////////////////////////////////////////////////////////////
Particle::Particle(const char* Name, double Px, double Py, double Pz)
  : Px_{Px}
  , Py_{Py}
  , Pz_{Pz}
{
  // Try to find particle named Name in ParticleTypes_ array, assign index based on that.
  const int Index = FindParticle(Name);
  if (Index == -1) {
    std::cout << "Error: No particle with name " << Name << " found." << endl;
  }

  Index_ = Index;
}

// Methods /////////////////////////////////////////////////////////////////////
void Particle::Print() const {
  std::cout << "Particle type index: " << Index_                                   << endl
            << "Particle name: "       << ParticleTypes_[Index_]->GetName()        << endl
            << "Particle momentum: ("  << Px_ << ", " << Py_ << ", " << Pz_ << ")" << endl;
}

double Particle::Mass() const {
  return ParticleTypes_[Index_]->GetMass();
}

double Particle::Momentum2() const {
  return Px_ * Px_ + Py_ * Py_ + Pz_ * Pz_;
}

double Particle::Momentum() const {
  return sqrt(Momentum2());
}

double Particle::TotalEnergy() const {
  return sqrt(Mass() * Mass() + Momentum2());
}

double Particle::InvariantMass(Particle &Particle) const {
  const double EnergySumSquared = pow(TotalEnergy() + Particle.TotalEnergy(), 2);
  const double MomentumSumSquared = pow(Momentum() + Particle.Momentum(), 2);

  return sqrt(EnergySumSquared + MomentumSumSquared);
}

int Particle::FindParticle(const char* Name) {
  for (int i = 0; i < NParticleTypes_; ++i) {
    // Check if Name matches any name in ParticleTypes_ array...
    if (strcmp(ParticleTypes_[i]->GetName(), Name) == 0) {
      // And return current index.
      return i;
    }
  }

  // Return -1 if no match.
  return -1;
}

bool Particle::AddParticleType(const char* Name, double Mass, int Charge, double Width) {
  if (FindParticle(Name) != -1) {
    std::cout << "Warning: particle name already in Particles array." << endl;
    return false;
  }
  if (NParticleTypes_ == 10) {
    std::cout << "Warning: Particles array full." << endl;
    return false;
  }

  if (Width == 0) {
    ParticleTypes_[NParticleTypes_++] = new ParticleType(Name, Mass, Charge);
    return true;
  }

  // todo ask if this is correct (the if width == 0)
  ParticleTypes_[NParticleTypes_++] = new ResonanceType(Name, Mass, Charge, Width);
  return true;
}

void Particle::PrintParticleTypes() {
  for (int i = 0; i < NParticleTypes_; ++i) {
    ParticleTypes_[i]->Print();
  }
}

// Getters /////////////////////////////////////////////////////////////////////
int Particle::GetIndex() const {
  return Index_;
}

double Particle::GetPx() const {
  return Px_;
}
double Particle::GetPy() const {
  return Py_;
}
double Particle::GetPz() const {
  return Pz_;
}


// Setters /////////////////////////////////////////////////////////////////////
bool Particle::SetIndex(int Index) {
  if (Index < 0 || Index >= MAX_NUM_PARTICLES || Index >= NParticleTypes_) {
    std::cout << "Invalid particle index" << endl;
    return false;
  }

  Index_ = Index;
  return true;
}
bool Particle::SetIndex(const char* Name) {
  return SetIndex(FindParticle(Name));
}

void Particle::SetP(double Px, double Py, double Pz) {
  Px_ = Px;
  Py_ = Py;
  Pz_ = Pz;
}

} // namespace sim
