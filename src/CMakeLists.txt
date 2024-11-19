#--- src/CMakeLists.txt ----------

# Get all source files in the src directory
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

# Add the main executable for your simulation, but ensure exampleCubeSim.cc is explicitly included
add_executable(exampleCubeSim ${sources} ${PROJECT_SOURCE_DIR}/exampleCubeSim.cc)

# Link the executable to Geant4 libraries, ensuring UI and vis libraries are included
target_link_libraries(exampleCubeSim ${Geant4_LIBRARIES})

# Include directories for Geant4 headers and project headers
include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIRS})

