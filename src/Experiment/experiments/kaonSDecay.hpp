#ifndef EXPERIMENT_KAONSDECAY_HPP
#define EXPERIMENT_KAONSDECAY_HPP

#include "experiment.hpp"
#include "entity-variants.hpp"

#include <string>
#include <vector>
#include <memory>
#include <TH1.h>
#include <TFile.h>
#include <TRandom3.h>

namespace sim {

class KaonSDecay : public Experiment {
  using EntityPtr         = std::unique_ptr<Entity>;  // fixme this makes for very funny syntax. Review it
  using EntityList        = std::vector<EntityPtr>;
  using EntityPtrIterator = EntityList::iterator;
  using TH1Ptr            = std::unique_ptr<TH1>;

  // Graphs that will be generated by this experiment
  enum Graph
  {
    ParticleDist,          // Distribution of generated particles
    AzimuthAngleDist,      // Distribution of phi angle of generated particles
    PolarAngleDist,        // Distribution of theta angle of generated particles
    MomentumDist,          // Distribution of momentum of generated particles
    TraverseMomentumDist,  // Distribution of traverse (xy plane) momentum of generated particles
    EnergyDist,            // Distribution of particles' total energy
    InvMass,               // Distribution of invariant mass of every pair of particles in an event
    InvMassOppCharge,      // Distribution of invariant mass of every pair of oppositely charged particles
    InvMassSameCharge,     // Distribution of invariant mass of every pair of same charged particles
    InvMassPKOppCharge,    // distribution of invariant mass between every oppositely charged pion-kaon couple
    InvMassPKSameCharge,   // distribution of invariant mass between every same charged pion-kaon couple
    InvMassPKCouple        // distribution of invariant mass between every decay-generated pion-kaon couple
  };

  // Root handlers /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Histogram handlers. Stored as pointers, since it's recommended. I think this is mandatory, since
  // we will use the Write() function.
  TH1Ptr   hists_[12];

  // Helper methods ////////////////////////////////////////////////////////////////////////////////////////////////////
  // Fill histograms with entities
  inline void fillHistograms(EntityList& entities) {
    // Loop through each entity
    for (auto entity = entities.begin(); entity != entities.end(); ++entity) {
      // Handler needed a lot in this for.
      Entity* entityPtr = entity->get();

      // Compute invariant mass histograms
      for (auto entity2 = entity + 1; entity2 != entities.end(); ++entity2) {
        Entity* entity2Ptr = entity2->get();

        // We don't want to consider K* in invariant mass. Only decay products are considered.
        if (entityPtr->is(kaonS)) {
          break;
        }
        if (entity2Ptr->is(kaonS)) {
          continue;
        }

        // Compute now invariant mass, since we will need it a lot later.
        const double invMass = Entity::invariantMass(*entityPtr, *entity2Ptr);

        // Plot inv mass of all particles
        hists_[InvMass]->Fill(invMass);

        // Plot inv mass of opposite/same charged particles
        if (entityPtr->charge() * entity2Ptr->charge() < 0) {
          hists_[InvMassOppCharge]->Fill(invMass);
        } else {  // Note that we don't have to check if charge is zero. since kaonS particles are already skipped.
          hists_[InvMassSameCharge]->Fill(invMass);
        }

        // Plot inv mass of opposite-charged P-K couples
        if ((entityPtr->is(pionP) && entity2Ptr->is(kaonM))
            || (entityPtr->is(pionM) && entity2Ptr->is(kaonP))) {
          hists_[InvMassPKOppCharge]->Fill(invMass);
        }

        // Plot inv mass of same-charged P-K couples
        if ((entityPtr->is(pionP) && entity2Ptr->is(kaonP))
            || (entityPtr->is(pionM) && entity2Ptr->is(kaonM))) {
          hists_[InvMassPKSameCharge]->Fill(invMass);
        }
      }

      if (!entityPtr->isDecayProduct()) {
        // Every particle _except decay products_ needs to appear in these histograms.
        hists_[ParticleDist]->Fill(entityPtr->type());
        hists_[AzimuthAngleDist]->Fill(entityPtr->phi());
        hists_[PolarAngleDist]->Fill(entityPtr->theta());
        hists_[MomentumDist]->Fill(entityPtr->p());
        hists_[TraverseMomentumDist]->Fill(entityPtr->traverseP());
        hists_[EnergyDist]->Fill(entityPtr->energy()); // Note that k* is considered here, so 4 peaks are expected.
      }

      // Plot inv mass of decay-generated P-K couples
      if (entityPtr->is(kaonS)) {
        // the two particles right after a kaon* are guaranteed to be its children
        hists_[InvMassPKCouple]->Fill(Entity::invariantMass(**(entity + 1), **(entity + 2)));
      }
    }
  }

  // Generate a random entity in the first available place of entities array, and return an iterator to it.
  static inline EntityPtrIterator generateRandomEntity(EntityList& entities) {
    // Generate polar components for current particle
    const double p     = gRandom->Exp(1.);
    const double phi   = gRandom->Uniform(0., 2. * M_PI);
    const double theta = gRandom->Uniform(0., M_PI);

    // This was made in order to avoid else blocks. I don't really like this syntax, I might change this
    // with a goto or simply add back the else-if.
    [&]() {
      const double chance = gRandom->Rndm();

      // Note that root Uniform generation appears to be slightly more likely to return lower numbers (based purely
      // on my empirical observations). Anyways, even if this were true, it would probably be negligible for large
      // numbers. (This is not a problem anymore, since i switched to using Rndm().
      if (chance < .40) {
        entities.push_back(std::make_unique<PionP>());
        return;
      }
      if (chance < .80) {
        entities.push_back(std::make_unique<PionM>());
        return;
      }
      if (chance < .85) {
        entities.push_back(std::make_unique<KaonP>());
        return;
      }
      if (chance < .90) {
        entities.push_back(std::make_unique<KaonM>());
        return;
      }
      if (chance < .945) {
        entities.push_back(std::make_unique<ProtonP>());
        return;
      }
      if (chance < .99) {
        entities.push_back(std::make_unique<ProtonM>());
        return;
      }
      entities.push_back(std::make_unique<KaonS>());
    }();

    // Set momentum components
    (entities.end() - 1)->get()->pPolar(p, phi, theta);

    return entities.end() - 1;
  }

  // Generate decay particles and boost them. This function guarantees that the decay particles are generated right
  // after entity.
  // Note that we need to have entity passed as iterator (not Entity*), since we need to access entity + 1 and + 2.
  static inline void handleDecay(EntityPtrIterator entity, EntityList& entities) {
    // We need to guarantee that entities has the space for the child particles
    entities.push_back(EntityPtr{});
    entities.push_back(EntityPtr{});

    assert(entity->get()->is(kaonS));

    // Then we chose one of two possible outcomes
    if (gRandom->Rndm(0) < .5) {
      (*(entity + 1)) = std::make_unique<PionM>(true);
      (*(entity + 2)) = std::make_unique<KaonP>(true);
    } else {
      (*(entity + 1)) = std::make_unique<PionP>(true);
      (*(entity + 2)) = std::make_unique<KaonM>(true);
    }

    // The code here:           vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv is just a reference to the entity
    // pointed.
    entity->get()->decayTo(*((entity + 1)->get()), *((entity + 2)->get()));
  }

  inline void handleEvent(int particleCount) {
    // Allocate space for new entities
    EntityList entities;
    entities.reserve(particleCount * 1.2);

    while (particleCount --> 0) {
      // Get iterator to randomly generated entity
      auto entity = generateRandomEntity(entities);

      // If entity is not K*, we don't have to worry about decay...
      if (!entity->get()->is(kaonS)) {
        continue;
      }

      // Otherwise, we must handle K* decay.
      handleDecay(entity, entities);
    }

    // Fill histograms with data for this event
    fillHistograms(entities);
  }

  // Public ////////////////////////////////////////////////////////////////////////////////////////////////////////////
 public:
  inline KaonSDecay() {
    gRandom->SetSeed();

    // Setup root histograms
    hists_[ParticleDist]         = std::make_unique<TH1I>("ParticleDist", "Particle types", 7, 0, 7);
    hists_[AzimuthAngleDist]     = std::make_unique<TH1F>("AzimuthAngleDist", "Azimuth angles", 360, 0, 2 * M_PI);
    hists_[PolarAngleDist]       = std::make_unique<TH1F>("PolarAngleDist", "Polar angles", 360, 0, M_PI);
    hists_[MomentumDist]         = std::make_unique<TH1F>("MomentumDist", "Momentum", 500, 0, 5);
    hists_[TraverseMomentumDist] = std::make_unique<TH1F>("TraverseMomentumDist", "Traverse momentum", 500, 0, 4); // rebin?
    hists_[EnergyDist]           = std::make_unique<TH1F>("EnergyDist", "Energy", 500, 0, 5); // rebin?
    hists_[InvMass]              = std::make_unique<TH1F>("InvMass", "Invariant mass", 600, 0, 6); // rebin?
    hists_[InvMassOppCharge]     = std::make_unique<TH1F>("InvMassOppCharge", "Invariant mass with opposite charge", 600, 0, 6);
    hists_[InvMassSameCharge]    = std::make_unique<TH1F>("InvMassSameCharge", "Invariant mass with same charge", 600, 0, 6);
    hists_[InvMassPKOppCharge]   = std::make_unique<TH1F>("InvMassPKOppCharge", "InvMassPKOppCharge", 600, 0, 6);
    hists_[InvMassPKSameCharge]  = std::make_unique<TH1F>("InvMassPKSameCharge", "InvMassPKSameCharge", 600, 0, 6);
    hists_[InvMassPKCouple]      = std::make_unique<TH1F>("InvMassPKCouple", "InvMassPKCouple", 500, 0.4, 1.4);

    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + pionP, "pion+");
    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + pionM, "pion-");
    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + kaonP, "kaon+");
    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + kaonM, "kaon-");
    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + protonP, "proton+");
    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + protonM, "proton-");
    hists_[ParticleDist]->GetXaxis()->SetBinLabel(1 + kaonS , "kaon*");

    // Needed for correct error handling when saving and subtracting histograms
    hists_[InvMassOppCharge]->Sumw2();
    hists_[InvMassSameCharge]->Sumw2();
    hists_[InvMassPKOppCharge]->Sumw2();
    hists_[InvMassPKSameCharge]->Sumw2();

    // Todo make histos pretty
  }

  inline void run(int eventCount, int particlesPerEvent) override {
    while (eventCount --> 0) {
      handleEvent(particlesPerEvent);
    }
  }

  inline void save(std::string fileName) override {
    // Open root file for writing. Clear and recreate file if already present.
    // ((use mutex to lock possible multi thread jank with root TFile?? very overkill for the scope of this project))
    TFile file(fileName.c_str(), "recreate");

    // Write every histogram to file.
    for (auto & histogram : hists_) {
      histogram->Write();
    }

    // Close file.
    file.Close();
  }
};

}  // namespace sim

#endif  // define EXPERIMENT_KAONSDECAY_HPP
