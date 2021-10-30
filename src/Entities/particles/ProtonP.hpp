#ifndef ENTITY_PROTONP_HPP
#define ENTITY_PROTONP_HPP

#include "entity.hpp"

namespace sim {

class ProtonP : public Entity {
  static constexpr EntityType type_{ protonP };
  static constexpr double     mass_{ 0.93827 };
  static constexpr int        charge_{ +1 };

 public:
  inline EntityType type() const override {
    return type_;
  }
  inline double mass() const override {
    return mass_;
  }
  inline int charge() const override {
    return charge_;
  }
};

}  // namespace sim

#endif  // define ENTITY_PROTONP_HPP
