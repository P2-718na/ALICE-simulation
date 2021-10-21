#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdlib>

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

bool Particle::AddParticleType(const char* Name, double Mass, int Charge, double Width) {
  if (FindParticle(Name) != -1) {
    std::cout << "Warning: particle name already in Particles array." << endl;
    return false;
  }
  if (NParticleTypes_ == 10) {
    std::cout << "Warning: Particles array full." << endl;
    return false;
  }

  // todo fix float == comparison
  if (Width == 0) {
    ParticleTypes_[NParticleTypes_++] = new ParticleType(Name, Mass, Charge);
    return true;
  }

  ParticleTypes_[NParticleTypes_++] = new ResonanceType(Name, Mass, Charge, Width);
  return true;
}

DecayResult Particle::Decay2body(Particle& dau1, Particle& dau2) const {
  // todo fix float == comparison
  if(Mass() == 0.0){
    std::cout << "Decayment cannot be preformed if mass is zero" << endl;
    return MassIsZero;
  }

  // todo fix naming
  double massMot = Mass();

  // add width effect
  // todo comment this
  if(Index_ != -1) {
    // gaussian random numbers
    // todo change with root gauss

    float x1;
    float x2;
    float w;
    float y1;
    float y2;

    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );

    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += ParticleTypes_[Index_]->GetWidth() * y1;

  }

  const double massDau1 = dau1.Mass();
  const double massDau2 = dau2.Mass();

  if(massMot < massDau1 + massDau2){
    std::cout << "Decayment cannot be preformed because mass is too low in this channel" << endl;
    return MassTooLow;
  }

  // todo idk what this is please explain
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  //todo add a method square()
  double energy = sqrt( Px_*Px_ + Py_*Py_ + Pz_*Pz_ + massMot*massMot);

  double bx = Px_/energy;
  double by = Py_/energy;
  double bz = Pz_/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return DecaySuccessful;
}

void Particle::PrintParticleTypes() {
  for (int i = 0; i < NParticleTypes_; ++i) {
    ParticleTypes_[i]->Print();
  }
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

void Particle::Boost(double bx, double by, double bz)
{
  const double energy = TotalEnergy();

  // Boost this Lorentz vector
  const double b2 = bx*bx + by*by + bz*bz;
  const double gamma = 1. / sqrt(1. - b2);
  double bp = (bx * Px_) + (by * Py_) + (bz * Pz_);

  // Gamma2 shouldn't be == 0, but we add this check just in case.
  double gamma2 = b2 != 0 ? (gamma - 1.) / b2 : 0.;

  Px_ += gamma2 * bp * bx + gamma * bx * energy;
  Py_ += gamma2 * bp * by + gamma * by * energy;
  Pz_ += gamma2 * bp * bz + gamma * bz * energy;
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
