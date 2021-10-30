#ifndef ENTITY_KAONM_HPP
#define ENTITY_KAONM_HPP

#include "entity.hpp"

namespace sim {

class KaonM : public Entity {
  static constexpr EntityType type_{ kaonM };
  static constexpr double     mass_{ 0.49367 };
  static constexpr int        charge_{ -1 };

 public:
  inline explicit KaonM(bool isDecayProduct = false) : Entity(isDecayProduct) {}

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

#endif  // define ENTITY_KAONM_HPP
