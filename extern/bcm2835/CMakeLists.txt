cmake_minimum_required(VERSION 3.16)

project(BCM2835)

add_library(BCM2835 INTERFACE)

target_include_directories(BCM2835 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(${PROJECT_NAME} INTERFACE
        bcm2835.c
        )

message(STATUS "From bcm2835: ${BCM2835}")