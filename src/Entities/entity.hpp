#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cmath>
#include <cassert>

namespace sim {

enum EntityType
{
  kaonP,
  kaonM,
  pionP,
  pionM,
  protonP,
  protonM,
  kaonS
};

class Entity {
  double px_{ 0 };
  double py_{ 0 };
  double pz_{ 0 };

 public:
  // Constructor (initialize individual particle information) //////////////////////////////////////////////////////////
  Entity();
  Entity(double px, double py, double pz);

  // Particle type information (static) ////////////////////////////////////////////////////////////////////////////////
  // Derived classes must make these values static constexpr.
  virtual EntityType type() const   = 0;
  virtual double     mass() const   = 0;
  virtual int        charge() const = 0;
  virtual double     width() const;

  // Check if this entity is of "type"
  bool is(EntityType type) const;

  // Print entity attributes
  void printAttributes() const;

  // individual particle information ///////////////////////////////////////////////////////////////////////////////////
  // Get individual momentum components
  inline double px() const {
    return px_;
  };
  inline double py() const {
    return py_;
  }
  inline double pz() const {
    return pz_;
  }

  // Get momentum (squared/norm)
  inline double p2() const {
    return (px() * px()) + (py() * py()) + (pz() * pz());
  }
  inline double p() const {
    return std::sqrt(p2());
  }

  // Set individual momentum components
  inline double px(double px) {
    return px_ = px;
  };
  inline double py(double py) {
    return py_ = py;
  }
  inline double pz(double pz) {
    return pz_ = pz;
  }

  // Set all momentum components
  inline void p(double px, double py, double pz) {
    this->px(px);
    this->py(py);
    this->pz(pz);
  }

  // Get total energy of the particle
  double energy() const;

  // Boost particle using lorentz vector transform.
  void boost(double betaX, double betaY, double betaZ);

  // Get invariant mass of two particles
  static double invariantMass(Entity& entity1, Entity& entity2);

  inline virtual int decayTwoEntities(Entity& entity1, Entity& entity2) {
    // Same considerations as width()
    assert(false);
    return -1;
  }

  // Destructor ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // We need a virtual destructor since we will be explicitly deleting derived pointers
  inline virtual ~Entity() = default;

  // And we need to obey to the 3/5/0 rule. These are deleted, since I am not using them.
  Entity(const Entity& copyFrom) = delete;
  Entity& operator=(const Entity& copyFrom) = delete;
  Entity(Entity &&) = delete;
  Entity& operator=(Entity &&) = delete;


};

}  // namespace sim

#endif  // define ENTITY_HPP
