cmake_minimum_required(VERSION 3.16) # CMake version check
project(c_soundzone_client VERSION 0.0.1) # Create project "c_soundzone_client"
set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard


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
##########################################################################################
##########################################################################################

# Add main.cpp file of project root directory as source file
set(${PROJECT_NAME} main.cpp)

set(SOURCES
        main.cpp
        src/test_src.cpp
        src/alsadriver.cpp
        )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )

##########################################################################################
###########################   Add subdirectories   #######################################
##########################################################################################

add_subdirectory(deps)

# Adds sub directories so file name is only needed under #include  "fileName.h"
# Link to the header files of alsa-lib
include_directories(/usr/include/alsa/)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} ${myasoundlib} BCM2835 datatransport_lib)

add_subdirectory(tests)
