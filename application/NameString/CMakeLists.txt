cmake_minimum_required(VERSION 3.14)
project(namestring)

add_library(${PROJECT_NAME} src/NameString.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

