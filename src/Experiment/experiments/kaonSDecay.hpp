#ifndef EXPERIMENT_KAONSDECAY_HPP
#define EXPERIMENT_KAONSDECAY_HPP

#include "experiment.hpp"
#include "entity-variants.hpp"

#include <string>
#include <vector>
#include <memory>
#include <TRandom3.h>

namespace sim {

using EntityPtr      = std::unique_ptr<Entity>;
using EntityList     = std::vector<EntityPtr>;
using EntityIterator = EntityList::iterator;

class KaonSDecay : public Experiment {
  // Generate a random entity in the first available place of entities array, and return an iterator to it.
  inline EntityIterator generateRandomEntity(EntityList& entities) {
    // This was made in order to avoid else blocks. I don't really like this syntax, I might change this
    // with a goto or simply add back the else-if.
    [&]() {
      const double chance = gRandom->Uniform(0, 100);

      // todo generate angle and momentum components

      if (chance < 40) {
        entities.push_back(std::make_unique<PionP>());
        return;
      }
      if (chance < 80) {
        entities.push_back(std::make_unique<PionM>());
        return;
      }
      if (chance < 85) {
        entities.push_back(std::make_unique<KaonP>());
        return;
      }
      if (chance < 90) {
        entities.push_back(std::make_unique<KaonM>());
        return;
      }
      if (chance < 94.5) {
        entities.push_back(std::make_unique<ProtonP>());
        return;
      }
      if (chance < 99) {
        entities.push_back(std::make_unique<ProtonM>());
        return;
      }
      entities.push_back(std::make_unique<KaonS>());
    }();

    return entities.end() - 1;
  }

  // Generate decay particles and boost them. This function guarantees that the decay particles are generated right
  // after entity.
  static inline void handleDecay(EntityIterator entity, EntityList& entities) {
    // We need to guarantee that entities has the space for the child particles
    entities.push_back(EntityPtr{});
    entities.push_back(EntityPtr{});

    // Then we chose one of two possible outcomes
    // gRandom->Uniform generates doubles in range (a, b)
    if (gRandom->Uniform(0, 2) <= 1) {
      (*(entity + 1)) = std::make_unique<PionM>();
      (*(entity + 2)) = std::make_unique<KaonP>();
    } else {
      (*(entity + 1)) = std::make_unique<PionP>();
      (*(entity + 2)) = std::make_unique<KaonM>();
    }

    // The code here:           vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv is just a reference to the entity
    // pointed.
    (*entity)->decayTwoEntities(*((entity + 1)->get()), *((entity + 2)->get()));
  }

  inline void handleEvent(int particleCount) {
    // Allocate space for new entities
    EntityList entities;
    entities.reserve(particleCount * 1.2);

    while (particleCount --> 0) {
      // Get iterator to randomly generated entity
      auto entity = generateRandomEntity(entities);

      // If entity is not K*, we don't have to worry about decay...
      if (!(entity->get())->is(kaonS)) {
        continue;
      }

      // Otherwise, we must handle K* decay.
      handleDecay(entity, entities);
    }
  }

 public:
  inline void run(int eventCount, int particlesPerEvent) override {
    while (eventCount --> 0) {
      handleEvent(particlesPerEvent);
    }
  }

  inline void save(std::string fileName) override {}
};

}  // namespace sim

#endif  // define EXPERIMENT_KAONSDECAY_HPP
