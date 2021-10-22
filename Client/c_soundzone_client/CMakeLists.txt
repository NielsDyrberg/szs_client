cmake_minimum_required(VERSION 3.16) # CMake version check
project(c_soundzone_client VERSION 0.0.1) # Create project "c_soundzone_client"
set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard

# configure a header file to pass the version number only
configure_file(soundZoneClientConfig.h.in soundZoneClientConfig.h)

# This finds the asound library
find_library(myasoundlib asound)
if(${myasoundlib})
    message(FATAL_ERROR "asound lib not found")
else()
    message(STATUS "asound lib found as ${myasoundlib}")
endif()


# Add main.cpp file of project root directory as source file
set(${PROJECT_NAME} main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} main.cpp
        src/test_src.h src/test_src.cpp
        deps/tests/c_project_test/c_project_test.h deps/tests/c_project_test/c_project_test.cpp
        deps/library/bcm2835.h deps/library/bcm2835.c
        src/alsadriver.cpp src/alsadriver.h
        )

# Adds sub directories so file name is only needed under #include  "fileName.h"
include_directories(src/)
include_directories(deps/)
include_directories(deps/tests/)
include_directories(deps/tests/c_project_test/)
include_directories(deps/library/)

# Link to the header files of alsa-lib
include_directories(/usr/include/alsa/)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} ${myasoundlib})

