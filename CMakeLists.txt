#--- CMake version and project settings ----------
cmake_minimum_required(VERSION 3.16...3.27)

# Project name
project(CubeSimulation)

# Find Geant4 package, including UI and visualization modules
find_package(Geant4 REQUIRED ui_all vis_all)

#--- Adding src subdirectory ----------
add_subdirectory(src)

#--- Custom target for building the simulation ----------
add_custom_target(CubeSim DEPENDS exampleCubeSim)

#--- Enable C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--- Install target for the executable ----------
install(TARGETS exampleCubeSim DESTINATION bin)
