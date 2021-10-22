cmake_minimum_required(VERSION 3.16) # CMake version check
project(c_soundzone_client VERSION 0.0.1) # Create project "c_soundzone_client"
set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lasound")

# Add main.cpp file of project root directory as source file
set(c_soundzone_client main.cpp)

# configure a header file to pass the version number only
configure_file(soundZoneClientConfig.h.in soundZoneClientConfig.h)

# Adds sub directories so file name is only needed under #include  "fileName.h"
include_directories(src/)
include_directories(deps/)
include_directories(deps/tests/)
include_directories(deps/tests/c_project_test/)
include_directories(deps/library/)
include_directories(deps/library/alsa/)
include_directories(deps/library/alsa/sound/)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(c_soundzone_client main.cpp
        src/test_src.h src/test_src.cpp
        deps/tests/c_project_test/c_project_test.h deps/tests/c_project_test/c_project_test.cpp
        deps/library/bcm2835.h deps/library/bcm2835.c
        src/alsadriver.cpp src/alsadriver.h
        )

LINK_DIRECTORIES(deps/library/alsa)
LINK_DIRECTORIES(/usr/include/alsa)
#target_include_directories(c_soundzone_client PRIVATE include /usr/include/alsa)
#target_link_libraries(c_soundzone_client alsa/asoundlib.h)



# -----Add alsa/asoundlib.h-----
#add_library(asoundlib STATIC IMPORTED)
#set_target_properties(asoundlib PROPERTIES IMPORTED_LOCATION /usr/include/alsa/asoundlib.h)
#set_target_properties(asoundlib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
#target_link_libraries(c_soundzone_client asoundlib)




# -----Add wiringPi-----
#add_library(wiringPi STATIC IMPORTED)
#set_target_properties(wiringPi PROPERTIES IMPORTED_LOCATION /usr/lib/libwiringPi.so)
#set_target_properties(wiringPi PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
#target_link_libraries(c_soundzone_client wiringPi)
# For at better import of wiringPi
# https://discourse.cmake.org/t/how-to-statically-link-external-library-by-target-link-libraries/1718/2
# Locate libraries and headers
#find_package(WIRINGPI_LIBRARIES NAMES wiringPi)
# ----- -----