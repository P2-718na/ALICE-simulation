#ifndef ENTITY_KAONP_HPP
#define ENTITY_KAONP_HPP

#include "entity.hpp"

namespace sim {

class KaonP : public Entity {
  static constexpr EntityType type_{ kaonP };
  static constexpr double     mass_{ 0.49367 };
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

#endif  // define ENTITY_KAONP_HPP
