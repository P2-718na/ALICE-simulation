#include "entity.hpp"

#include <iostream>

namespace sim {

// Constructor /////////////////////////////////////////////////////////////////////////////////////////////////////////
Entity::Entity() = default;
Entity::Entity(bool isDecayProduct) :isDecayProduct_{isDecayProduct} {}
Entity::Entity(double px, double py, double pz)
  : px_{ px }
  , py_{ py }
  , pz_{ pz } {}

double Entity::width() const {
  // Most particles don't have a resonance width, and width() is not supposed to be called for them.
  // Defining this function here allows me to write less code, since I will need to override this function
  // only for resonance types.
  assert(false);

  return 0;
}

bool Entity::is(EntityType type) const {
  return this->type() == type;
}

void Entity::printAttributes() const {
  std::cout << "Type: " << type() << ", Mass: " << mass() << ", Charge: " << charge();
}

double Entity::energy() const {
  return std::sqrt(mass() * mass() + p2());
}

double Entity::traverseP() const {
  return std::sqrt((px() * px()) + (py() * py()));
}

void Entity::boost(double betaX, double betaY, double betaZ) {
  // fixme i have no idea what this does
  double energy = this->energy();

  // Boost this Lorentz vector
  double b2     = (betaX * betaX) + (betaY * betaY) + (betaZ * betaZ);
  double gamma  = 1.0 / sqrt(1.0 - b2);
  double bp     = betaX * px() + betaY * py() + betaZ * pz(); // <-- This made me waste a good ~20 hours.
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  // fixme this should be changed
  px_ += gamma2 * bp * betaX + gamma * betaX * energy;
  py_ += gamma2 * bp * betaY + gamma * betaY * energy;
  pz_ += gamma2 * bp * betaZ + gamma * betaZ * energy;
}

double Entity::invariantMass(Entity& entity1, Entity& entity2) {
  const double energySumSquare   = std::pow(entity1.energy() + entity2.energy(), 2);
  const double momentumSumSquare = std::pow(entity1.px() + entity2.px(), 2)
                                 + std::pow(entity1.py() + entity2.py(), 2)
                                 + std::pow(entity1.pz() + entity2.pz(), 2);

  return std::sqrt(energySumSquare - momentumSumSquare);
}

}  // namespace sim
