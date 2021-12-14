cmake_minimum_required(VERSION 3.1)

# Specify the C++ standard (CMake3+)
add_compile_options(-std=c++11)

# Add header files
file(GLOB INCLUDES "includes/*.h")

# Add src files
file(GLOB SOURCES "../*.cpp")


# Add library interface for our files
add_library(LabLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(LabLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})