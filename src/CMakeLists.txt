ADD_EXECUTABLE(lab main.cpp)

ADD_SUBDIRECTORY(Entities)
ADD_SUBDIRECTORY(Experiment)

TARGET_LINK_LIBRARIES(lab Experiment)

SET_TARGET_PROPERTIES(
        lab PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

## Symlink root file to notebook directory.
## This probably needs to be rethought.
#add_custom_command(TARGET lab
#                   COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_BINARY_DIR}/kaon-s-decay-hist.root ${PROJECT_SOURCE_DIR}/notebooks/kaon-s-decay-hist.root
#                   COMMENT "Symlinking notebook..."
#                  )
