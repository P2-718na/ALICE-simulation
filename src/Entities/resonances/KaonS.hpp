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

  // Make this resonance decay into two entities. The entities need to be already generated with momentum = 0.
  // This function will set their momentum appropriately.
  inline int decayTo(Entity& entity1, Entity& entity2) override {
    if(mass() == 0.) {
      std::cout << "Decayment cannot be preformed if mass is zero" << std::endl;
      return 1;
    }

    double massMot = mass();
    double massDau1 = entity1.mass();
    double massDau2 = entity2.mass();

    assert(massDau1 != 0);
    assert(massDau2 != 0);

    // add width effect////////////////////////////////////

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );

    w = std::sqrt( (-2.0 * std::log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += width() * y1;
    //////////////////////////////////////////////////////

    if(massMot < massDau1 + massDau2){
      printf("Decayment cannot be preformed because mass is too low in this channel\n");
      return 2;
    }

    double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

    double norm = 2*M_PI/RAND_MAX;

    double phi = rand()*norm;
    double theta = rand()*norm*0.5 - M_PI/2.;
    entity1.p(pout*std::sin(theta)*std::cos(phi),pout*std::sin(theta)*std::sin(phi),pout*std::cos(theta));
    entity2.p(-pout*std::sin(theta)*std::cos(phi),-pout*std::sin(theta)*std::sin(phi),-pout*std::cos(theta));

    double energy = sqrt(px()*px() + py()*py() + pz()*pz() + massMot*massMot);

    double bx = px() / energy;
    double by = py() / energy;
    double bz = pz() / energy;

    entity1.boost(bx, by, bz);
    entity2.boost(bx, by, bz);

    return 0;
  };
};

}  // namespace sim

#endif  // define ENTITY_KAONS_HPP
