#include <lyra/lyra.hpp>
#include <cmath>

#include "experiments/kaonSDecay.hpp"

int main(int argc, char** argv) {
  // Order of magnitude of number of generated events;
  int events = 4;

  auto cli = lyra::cli()
           | lyra::opt( events, "1-5" )
             ["-e"]("Order of magnitude of generated events.")
             .choices([](int value) -> bool { return 1 <= value && value <= 5; });

  // Parse cli arguments
  auto result = cli.parse({ argc, argv });

  // And terminate if there is an error:
  if (!result) {
    std::cerr << result.errorMessage() << std::endl;
    exit(1);
  }

  // Create a new Kaon* decay experiment
  sim::Experiment* experiment = new sim::KaonSDecay();

  // Run the experiments. 100 particles for each event.
  experiment->run(std::pow(10, events), 100);

  // Write event data to root file
  experiment->save("kaon-s-decay-hist.root");
}
