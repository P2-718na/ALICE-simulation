#include "entity.hpp"

#include <iostream>

namespace sim {

// Constructor /////////////////////////////////////////////////////////////////////////////////////////////////////////
Entity::Entity() = default;
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
}  // namespace sim
