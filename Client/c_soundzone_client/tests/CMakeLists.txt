
############################################################
# Create a library
############################################################

#Generate the static library from the library sources
#add_library(tests STATIC
#        c_project_test/c_project_test.cpp
#        test_DataTransport/test_DataTransport.cpp
#        )

#target_include_directories(tests PUBLIC include)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test_DataTransport)
add_subdirectory(c_project_test)