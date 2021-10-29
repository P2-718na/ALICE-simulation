#ifndef EXPERIMENT_KAONSDECAY_HPP
#define EXPERIMENT_KAONSDECAY_HPP

#include "experiment.hpp"
#include "entity-variants.hpp"

#include <string>

namespace sim {

class KaonSDecay : public Experiment {
 public:
  inline KaonSDecay() {
    static Entity* entities[2];
    entities[0] = new KaonM;
    entities[1] = new KaonP;

    entities[0]->printAttributes();
    entities[1]->printAttributes();
  }

  inline void run(int eventCount, int particlePerEvent) override {}
  inline void save(std::string fileName) override {}
};

}  // namespace sim

#endif  // define EXPERIMENT_KAONSDECAY_HPP
