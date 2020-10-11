#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(ana_knucl)
#
#----------------------------------------------------------------------------
# Setup include directory for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories($ENV{KNUCLSRCDIR}/include)
#
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# include Geant4
#
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
#
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# include Root
#
list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
find_package(ROOT)
include_directories(${ROOT_INCLUDE_DIR})
#
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# include KinFittrer
#
include_directories($ENV{KFSRCDIR})
#
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(ana_knucl ana_knucl.cc ${sources} ${headers})
target_link_libraries(ana_knucl ${ROOT_LIBRARIES} $ENV{KNUCLSRCDIR}/build/libKnuclROOT.so $ENV{KFLIBDIR}/libTKinFitter.so -lEG)
#add_executable(ana_knucl_e15 ana_knucl_e15.cc ${sources} ${headers})
#target_link_libraries(ana_knucl_e15 ${ROOT_LIBRARIES} $ENV{KNUCLSRCDIR}/build/libKnuclROOT.so -lEG)
add_executable(plot_knucl plot_knucl.cc ${sources} ${headers})
target_link_libraries(plot_knucl ${ROOT_LIBRARIES} $ENV{KNUCLSRCDIR}/build/libKnuclROOT.so $ENV{KFLIBDIR}/libTKinFitter.so -lEG -lHistPainter)
set(CMAKE_MACOSX_RPATH 1)
