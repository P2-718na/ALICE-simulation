// Doctest requires this define to be specified only once.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

using sim::Particle;

// Stuff is static, so there is no real good way to do unit testing.
TEST_CASE("General tests") {
  SUBCASE("Adding particle types") {
    CHECK(Particle::AddParticleType("pion", 134.9, 0));
    CHECK(Particle::AddParticleType("positron", 0.5109, 1));

    // Can't add same particle two times
    CHECK_FALSE(Particle::AddParticleType("positron", 0.5109, 1));

    // If the max number of particles is 10...
    CHECK(Particle::AddParticleType("2", 1, 1));
    CHECK(Particle::AddParticleType("3", 1, 1));
    CHECK(Particle::AddParticleType("4", 1, 1));
    CHECK(Particle::AddParticleType("5", 1, 1));
    CHECK(Particle::AddParticleType("6", 1, 1));
    CHECK(Particle::AddParticleType("7", 1, 1));
    CHECK(Particle::AddParticleType("8", 1, 1));
    CHECK(Particle::AddParticleType("9", 1, 1));

    // This should be false
    CHECK_FALSE(Particle::AddParticleType("10", 1, 1));

    // Now, try to create some particles
    Particle particle("positron", 0, 0, 0);
    Particle particle2("positron", 1, 0, 0);
    Particle particle3("_", 0, 0, 0);

    CHECK(particle.GetIndex() == 1);
    CHECK(particle2.GetIndex() == 1);
    CHECK(particle3.GetIndex() == -1);

    CHECK(particle3.SetIndex("3"));
    CHECK_FALSE(particle3.GetIndex() == 30);
    CHECK(particle3.GetIndex() == 3);
  }
}
