#ifndef ENTITY_KAONS_HPP
#define ENTITY_KAONS_HPP

#include "entity.hpp"

namespace sim {

class KaonS : public Entity {
  static constexpr EntityType type_{ kaonS };
  static constexpr double     mass_{ 0.89166 };
  static constexpr int        charge_{ 0 };
  static constexpr double     width_{ 0.05 };

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
  inline double width() const override {
    return width_;
  }
};

}  // namespace sim

#endif  // define ENTITY_KAONS_HPP
