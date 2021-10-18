<div align="center">
  <img alt="Alma Mater Studiorum Logo" src="assets/unibo-logo.png">
</div>

# ALICE-simulation
This is a simulation of CERN-ALICE particle events, generated using Montecarlo
generation integrated in ROOT. I will add more details in the future.
I'm writing this code for my Physics Lab-2 exam at University of Bologna.

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
version 6.18, I tested it on 6.24). If you encounter any other problem,
good luck.

## Running
This code was tested and running on _Mac OS X 10.14.6 Mojave_.
Please note that this is still WIP, I will update this section later.

### Running via terminal
TBD

### Testing
Make sure to compile tests (see [Building](#building)), then run
```shell
./tests
```

--------------------------------------------------------------------------------

## Additional notes
TBD
