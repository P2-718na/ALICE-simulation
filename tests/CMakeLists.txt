ADD_EXECUTABLE(lab-test ./lab.test.cpp)

SET_TARGET_PROPERTIES(
        lab-test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

TARGET_LINK_LIBRARIES(lab-test ParticleType ResonanceType Particle)
