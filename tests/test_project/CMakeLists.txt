
cmake_minimum_required(VERSION 3.16) # CMake version check
project(test_project VERSION 0.0.1) # Create project "test_project"
set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard

set(SOURCES
        test_project.cpp
        )

# Add main.cpp file of project root directory as source file
set(${PROJECT_NAME} test_project.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries to project
target_link_libraries(${PROJECT_NAME} ${myasoundlib} BCM2835)






