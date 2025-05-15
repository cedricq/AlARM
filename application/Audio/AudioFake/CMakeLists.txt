cmake_minimum_required(VERSION 3.14)
project(audio_fake)

add_library(${PROJECT_NAME} AudioFake.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} audioI)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

