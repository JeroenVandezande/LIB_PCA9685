cmake_minimum_required(VERSION 3.19)
project(LIB_PCA9685 C)

set(CMAKE_C_STANDARD 99)

# add dependencies
include(cpm/CPM.cmake)
CPMAddPackage("gh:JeroenVandezande/LowLevelCInterfaces@1.0.6")

add_library(LIB_PCA9685 PCA9685.c PCA9685.h)

target_include_directories (LIB_PCA9685 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(LIB_PCA9685 PUBLIC LowLevelCInterfaces m)