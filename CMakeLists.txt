cmake_minimum_required(VERSION 2.8)

# Set Policies
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

if(POLICY CMP0023)
  cmake_policy(SET CMP0023 NEW)
endif()

if(POLICY CMP0079)
  cmake_policy(SET CMP0079 NEW)
endif()

##########################################################

# https://stackoverflow.com/questions/43862273/cmake-c-include-relative-to-base-directory
project(Airport VERSION 1.0)

add_subdirectory(graph)
add_subdirectory(lab_inheritance)

add_compile_options(-std=c++11)

# Add header files
file(GLOB INCLUDES "includes/*.h")

# Add graph files
file(GLOB SOURCES "graph/*.cpp")

# Add lab files
file(GLOB SOURCES "lab_inheritance/*.cpp")

# Add testing sources
file(GLOB TEST_SOURCES "test/*.cpp")

# Add library interface for our files
add_library(MainLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(MainLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(MainLib PUBLIC "graph/include" "lab_inheritance/include")

link_directories("../graph" "../lab_inheritance")
target_link_libraries(MainLib GraphLib LabLib)

# Add the executable
add_executable(draw drawandalgorithms.cpp)
target_link_libraries(draw MainLib)

target_include_directories(draw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Add Catch2
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.1
)

FetchContent_MakeAvailable(Catch2)
add_executable(test_main ${SOURCES} ${TEST_SOURCES})
target_link_libraries(test_main MainLib Catch2::Catch2)
