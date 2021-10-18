#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "Particle.hpp"

#include <TApplication.h>
#include <TCanvas.h>
#include <TRootCanvas.h>
#include <TH1F.h>

int main(int argc, char** argv) {
  sim::Particle::AddParticleType("pion", 134.9, 0);
  sim::Particle::AddParticleType("positron", 0.5109, 1);

  sim::Particle::PrintParticleTypes();

  sim::Particle particle("pion", 0, 0, 0);

  particle.SetIndex("positron");

  // TApplication is required for the application to work correctly.
  TApplication app("app", &argc, argv);

  // This is needed to terminate program when canvas is closed.
  // I am not sure whether i want this or not, but I spent a good half an
  // hour trying to make this code work and i'm gonna keep it for now.
  // Please note that These require linking ROOT::Gui.
  // (TCanvas worked with ROOT::Gpad as well, but TRootCanvas does not).
  auto canvas = new TCanvas();
  auto rc = (TRootCanvas *)canvas->GetCanvasImp();
  rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

  TH1F* table = new TH1F("name", "title", 2, 2, 2);
  table->Fill(3);
  table->Fill(3);


  table->Draw();

  // Start ROOT event loop.
  app.Run();
}
