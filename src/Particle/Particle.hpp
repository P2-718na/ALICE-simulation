#ifndef PARTICLE_HPP
#define PARTICLE_HPP

namespace sim {

enum DecayResult {
  DecaySuccessful,
  MassIsZero,
  MassTooLow,
};

class ParticleType;

class Particle {
 public:
  // Check if ParticleType with Name exists in ParticleTypes_ array.
  // Assign Index_ based on that.
  // If no ParticleType with Name is found, throw.
  explicit Particle(const char* Name, double Px = 0, double Py = 0, double Pz = 0);

  // Maximum number of active particles
  static constexpr int MAX_NUM_PARTICLES = 10;

  // Methods ///////////////////////////////////////////////////////////////////
  // Call Print() method on  all particle types in ParticleTypes_ array.
  static void PrintParticleTypes();

  // Print information of this particle
  void Print() const;

  // Get mass of current particle's particle type
  double Mass() const;

  // Get momentum (squared) of this particle.
  double Momentum2() const;
  double Momentum() const;

  // Get total energy of this particle
  double TotalEnergy() const;

  // Get invariant mass between this and another particle
  double InvariantMass(Particle& Particle) const;

  // Add a particle type to ParticleTypes_.
  // Returns false if a particle with same name already exists, or if
  // the array is full.
  static bool AddParticleType(const char* Name, double Mass, int Charge, double Width = 0);

  // Decay one particle into two other particles.
  // Decayment will fail if either mass of this particle is
  // zero or if it's too low.
  DecayResult Decay2body(Particle& dau1, Particle& dau2) const;

  // Getters ///////////////////////////////////////////////////////////////////
  int GetIndex() const;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;

  // Setters ///////////////////////////////////////////////////////////////////
  // Manually set this particle index.
  // If these two fail, they will print an error.
  // Returns false if this index in ParticleTypes_ does not yet exist.
  bool SetIndex(int Index);
  // Returns false if this name in ParticleTypes_ does not yet exist.
  bool SetIndex(const char* Name);

  // Set momentum components
  void SetP(double Px, double Py, double Pz);

 private:
  // Array containing all active particle types
  static ParticleType* ParticleTypes_[MAX_NUM_PARTICLES];

  // Number of types in ParticleTypes_ array
  static int NParticleTypes_;

  // Index of this particle in ParticleTypes_ array
  int Index_;

  // Momentum components
  double Px_{0};
  double Py_{0};
  double Pz_{0};

  // Methods ///////////////////////////////////////////////////////////////////
  // Find a particle type in ParticleTypes_ array by name, return its index.
  // Returns -1 if not found.
  static int FindParticle(const char* Name);

  // Used by Decay2Body to split momentum components
  // todo comment variable names
  void Boost(double bx, double by, double bz);
};

} // namespace sim

#endif // define PARTICLE_HPP
