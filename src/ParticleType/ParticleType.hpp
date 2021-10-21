#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

namespace sim {

class ParticleType {
 public:
  // Constructor ///////////////////////////////////////////////////////////////
  ParticleType(const char* Name, double Mass, int Charge);

  // Methods ///////////////////////////////////////////////////////////////////
  // Print all particle attributes to stdout
  virtual void Print() const;

  // Getters ///////////////////////////////////////////////////////////////////
  const char* GetName() const;
  double GetMass() const;
  int GetCharge() const;

  // This is needed for inheritance. Returns zero.
  virtual double GetWidth() const;

 private:
  // Name of the particle
  const char* Name_;

  // Mass of the particle
  const double Mass_;

  // Charge of the particle
  const int Charge_;
};

} // namespace sim
#endif // define PARTICLETYPE_HPP
