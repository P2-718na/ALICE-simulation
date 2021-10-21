#ifndef ENTITY_PROTONM_HPP
#define ENTITY_PROTONM_HPP

#include "entity.hpp"

namespace sim {

class ProtonM : public Entity {
  static constexpr EntityType type_{ protonM };
  static constexpr double     mass_{ 0.93827 };
  static constexpr int        charge_{ -1 };

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

#endif  // define ENTITY_PROTONM_HPP
