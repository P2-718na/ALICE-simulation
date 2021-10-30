#ifndef ENTITY_PIONP_HPP
#define ENTITY_PIONP_HPP

#include "entity.hpp"

namespace sim {

class PionP : public Entity {
  static constexpr EntityType type_{ pionP };
  static constexpr double     mass_{ 0.13957 };
  static constexpr int        charge_{ +1 };

 public:
  inline explicit PionP(bool isDecayProduct = false) : Entity(isDecayProduct) {}

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

#endif  // define ENTITY_PIONP_HPP
