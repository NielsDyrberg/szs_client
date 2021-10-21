cmake_minimum_required(VERSION 3.16) # CMake version check
project(c_soundzone_client VERSION 0.0.1) # Create project "c_soundzone_client"
set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(c_soundzone_client main.cpp)

# configure a header file to pass the version number only
configure_file(soundZoneClientConfig.h.in soundZoneClientConfig.h)

# Adds sub directories so file name is only needed onder #include "fileName.h"
include_directories(src/)
include_directories(deps/)
include_directories(deps/tests/)

# With this, files for add_executable under deps, only has to be added under deps/CMakeLists.txt
#add_subdirectory(deps/)
# added under src/CMakeLists.txt
#add_subdirectory(src/)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(c_soundzone_client main.cpp
        src/test_src.h src/test_src.cpp
        deps/tests/c_project_test/c_project_test.h deps/tests/c_project_test/c_project_test.cpp)


# -----Add wiringPi-----
add_library(wiringPi STATIC IMPORTED)
set_target_properties(wiringPi PROPERTIES IMPORTED_LOCATION /usr/lib/libwiringPi.so)
set_target_properties(wiringPi PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
target_link_libraries(c_soundzone_client wiringPi)
# For at better import of wiringPi
# https://discourse.cmake.org/t/how-to-statically-link-external-library-by-target-link-libraries/1718/2
# Locate libraries and headers
#find_package(WIRINGPI_LIBRARIES NAMES wiringPi)
# ----- -----