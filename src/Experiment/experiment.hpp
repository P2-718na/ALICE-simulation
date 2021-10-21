#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

#include <string>

namespace sim {

class Experiment {
 public:
  // Run experiment. The experiment will have eventCount events, and particlePerEvent particles for each event.
  virtual void run(int eventCount, int particlePerEvent) = 0;

  // Write experiment data to file.
  virtual void save(std::string fileName) = 0;
};

}  // namespace sim

#endif  // define EXPERIMENT_HPP
