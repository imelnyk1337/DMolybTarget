cmake_minimum_required(VERSION 3.20...3.28)
project(DMolybTarget)

set(CMAKE_CXX_STANDARD 20)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${Geant4_INCLUDE_DIR} include)

file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY macros DESTINATION ${PROJECT_BINARY_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


add_executable(DMolybTarget DMolybTarget.cxx ${sources} ${headers})
target_link_libraries(DMolybTarget ${Geant4_LIBRARIES})
install(TARGETS DMolybTarget DESTINATION ${PROJECT_SOURCE_DIR}/install)