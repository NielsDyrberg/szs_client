cmake_minimum_required(VERSION 3.16) # CMake version check
set(CMAKE_CXX_STANDARD 20) # Enable c++14 standard

##########################################################################################
##########################################################################################
##########################################################################################

# Add main.cpp file of project root directory as source file
set(${PROJECT_NAME} src/main.cpp)

set(SOURCES
        main.cpp
        test_src.cpp
        alsadriver.cpp
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

# Adds sub directories so file name is only needed under #include  "fileName.h"
# Link to the header files of alsa-lib
include_directories(/usr/include/alsa/)

# Link libraries to project
#target_link_libraries(${PROJECT_NAME} ${myasoundlib} BCM2835 datatransport_lib SoundZoneProtocol_lib)
target_link_libraries(${PROJECT_NAME} ${myasoundlib} szs_soundzone_protocol)
