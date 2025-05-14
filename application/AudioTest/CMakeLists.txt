cmake_minimum_required(VERSION 3.14)
project(audio_test)

add_library(${PROJECT_NAME} src/AudioTest.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} alarm)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

