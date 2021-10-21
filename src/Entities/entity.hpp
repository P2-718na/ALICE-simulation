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
};

}  // namespace sim

#endif  // define ENTITY_HPP
