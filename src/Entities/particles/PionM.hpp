#ifndef ENTITY_PIONM_HPP
#define ENTITY_PIONM_HPP

#include "entity.hpp"

namespace sim {

class PionM : public Entity {
  static constexpr EntityType type_{ pionM };
  static constexpr double     mass_{ 0.13957 };
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

#endif  // define ENTITY_PIONM_HPP
