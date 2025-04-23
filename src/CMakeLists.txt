cmake_minimum_required(VERSION 3.14)
project(alarm)

add_library(${PROJECT_NAME} AlARM.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/inc)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

