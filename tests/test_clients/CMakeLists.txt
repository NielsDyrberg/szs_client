cmake_minimum_required(VERSION 3.16) # CMake version check
set(CMAKE_CXX_STANDARD 20) # Enable c++14 standard

##########################################################################################
####################################   Client 1   ########################################
##########################################################################################


project(test_client_1 VERSION 0.0.1) # Create project "test_recv_packet"


# Add main.cpp file of project root directory as source file
set(${PROJECT_NAME} test_clients.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} test_clients.cpp)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} soundzone_client_lib)


##########################################################################################
####################################   Client 2   ########################################
##########################################################################################

project(test_client_2 VERSION 0.0.1) # Create project "test_recv_packet"

# Add main.cpp file of project root directory as source file
set(${PROJECT_NAME} test_clients.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} test_clients.cpp)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} soundzone_client_lib)
