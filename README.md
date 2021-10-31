<div align="center">
  <img alt="Alma Mater Studiorum Logo" src="assets/unibo-logo.png">
</div>

# ALICE-simulation
This is my project for my Physics laboratory-2 course at University of Bologna.
The goal of this project is to simulate a real-world use case for ROOT software.
The project is divided in two parts. Firstly, we will generate data using the
Montecarlo method, then we will analyze that data using ROOT's powerful
instruments. The data we will be generating will mimic the real-world ALICE
experiment at CERN. We want to prove that the K* particle exists in an unstable
state that decays in a pion-kaon pair; to do that, we will be generating "mock"
particle data, (which simulates real-world data acquired from CERN).
If the K* particle exists, we will find some statistical discrepancies in the
resulting data during the second phase of the prohect.

## Data analysis
see other repo (https://github.com/P2-718na/kstar-decayment-analysis)

--------------------------------------------------------------------------------

## Dependencies
- [ROOT](https://root.cern/) (required, version 6.18^)
- [Doctest](https://github.com/onqtam/doctest) (bundled)
- [CMake](https://cmake.org/) (recommended)

## Building
The preferred way to build this code is by using CMake.
```shell
mkdir build
cd build
cmake ..
```
Then, run either of these commands
```shell
make lab      # compile the program only
make tests    # compile tests only
make          # compile both
```
Both executables will be generated inside the build folder.

### NOTE: Building ROOT application with CMake
I run into some trouble while trying to compile ROOT with CMake.
I think the solution is just to use the latest version of ROOT (at least
version 6.18, I tested it out on 6.24). If you encounter any other problem,
good luck.

## Running
This code was tested and running on _Mac OS X 10.14.6 Mojave_.
Please note that this is still WIP, I will update this section later.

### Running via terminal
TBD

### Running on WSL
This can actually be done quite easily. There is a catch, though: ROOT uses
dynamic libraries, and they are loaded into `$LD_LIBRARY_PATH` when you
`source thisroot.sh`. This means that, if you are launching the program from
outside WSL (e.g. CLion), your program _will not_ find the required libraries.
If you want to run the program, you can either setup the required environment
variables manually, or just launch it from a terminal shell.

### Testing
Make sure to compile tests (see [Building](#building)), then run
```shell
./tests
```

--------------------------------------------------------------------------------

## Additional notes
TBD
