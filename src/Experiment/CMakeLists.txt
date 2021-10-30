ADD_LIBRARY(Experiment STATIC experiment.cpp)

TARGET_LINK_LIBRARIES(Experiment Entity ROOT::Hist ROOT::MathCore)
