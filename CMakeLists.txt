cmake_minimum_required(VERSION 3.16) # CMake version check
project(soundzone_client VERSION 0.0.1) # Create project "soundzone_client"
set(CMAKE_CXX_STANDARD 20) # Enable c++14 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


##########################################################################################
##############################   Include asound   ########################################
##########################################################################################

# configure a header file to pass the version number only
configure_file(soundZoneClientConfig.h.in soundZoneClientConfig.h)

# This finds the asound library
find_library(myasoundlib asound)
if(${myasoundlib})
    message(FATAL_ERROR "asound lib not found")
else()
    message(STATUS "asound lib found as ${myasoundlib}")
endif()

##########################################################################################
###########################   Add subdirectories   #######################################
##########################################################################################

add_subdirectory(src)
add_subdirectory(extern/szs_soundzone_protocol)

#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/szs_soundzone_protocol)

# Adds sub directories so file name is only needed under #include  "fileName.h"
# Link to the header files of alsa-lib
#include_directories(/usr/include/alsa/)

# Link libraries to project
#target_link_libraries(${PROJECT_NAME} ${myasoundlib} BCM2835 datatransport_lib SoundZoneProtocol_lib)
#target_link_libraries(${PROJECT_NAME} ${myasoundlib} szs_soundzone_protocol)

# add_subdirectory(tests)
