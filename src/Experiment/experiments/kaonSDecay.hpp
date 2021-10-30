#ifndef EXPERIMENT_KAONSDECAY_HPP
#define EXPERIMENT_KAONSDECAY_HPP

#include "experiment.hpp"
#include "entity-variants.hpp"

#include <string>

namespace sim {

class KaonSDecay : public Experiment {
 public:
  inline KaonSDecay() {}

  inline void run(int eventCount, int particlePerEvent) override {}
  inline void save(std::string fileName) override {}
};

}  // namespace sim

#endif  // define EXPERIMENT_KAONSDECAY_HPP
