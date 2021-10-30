#include <lyra/lyra.hpp>
#include <cmath>

#include "experiments/kaonSDecay.hpp"

int main(int argc, char** argv) {
  // Order of magnitude of number of generated events;
  int events = 4;
  auto cli = lyra::cli()
             | lyra::opt( events, "events" )
             ["-e"]
               ("Order of magnitude of generated events.");

  // Create a new Kaon* decay experiment
  sim::Experiment* experiment = new sim::KaonSDecay();

  // Run the experiments. 100 particles for each event.
  experiment->run(std::pow(10, events), 100);

  // Write event data to root file
  experiment->save("histograms.root");
}
