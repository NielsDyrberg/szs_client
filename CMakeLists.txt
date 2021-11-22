cmake_minimum_required(VERSION 3.16) # CMake version check
project(soundzone_client_lib VERSION 0.1.0) # Create project "soundzone_client_lib"
set(CMAKE_CXX_STANDARD 20) # Enable c++14 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# configure a header file to pass the version number only
configure_file(soundZoneClientConfig.h.in soundZoneClientConfig.h)

##########################################################################################
##################################  Make library  ########################################
##########################################################################################

#Generate the static library from the library sources
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_sources(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/szs_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/alsadriver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy_alsa_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sync_handler.cpp
        )

##########################################################################################
################################   Find pthread   ########################################
##########################################################################################

# This finds the pthread library
find_library(mypthreadlib pthread)
if(${mypthreadlib})
    message(FATAL_ERROR "pthread lib not found")
else()
    message(STATUS "pthread lib found as ${mypthreadlib}")
endif()


##########################################################################################
################################   Find asound   #########################################
##########################################################################################

# This finds the asound library
find_library(myasoundlib asound)
if(${myasoundlib})
    message(FATAL_ERROR "asound lib not found")
else()
    message(STATUS "asound lib found as ${myasoundlib}")
endif()

##########################################################################################
################################   Find BCM2835   ########################################
##########################################################################################

# This finds the asound library
find_library(mybcm2835 bcm2835)
if(${mybcm2835})
    message(FATAL_ERROR "bcm2835 lib not found")
else()
    message(STATUS "bcm2835 lib found as ${mybcm2835}")
endif()

##########################################################################################
###########################   Add subdirectories   #######################################
##########################################################################################

# Externale libaries
add_subdirectory(extern)

# Adds sub directories so file name is only needed under #include  "fileName.h"
# Link to the header files of alsa-lib
include_directories(/usr/include/alsa/)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} INTERFACE ${myasoundlib} ${mybcm2835} ${mypthreadlib} szs_soundzone_protocol szs_time_sync)

##########################################################################################
########################   Make executable project   ####################################
##########################################################################################

# Add main.cpp file of project root directory as source file
set(soundzone_client main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(soundzone_client ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
# Link libraries to project
target_link_libraries(soundzone_client soundzone_client_lib)

##########################################################################################
##################################  Add tests  ###########################################
##########################################################################################

# Tests concerning szs client
add_subdirectory(tests)