cmake_minimum_required(VERSION 3.14)
project(alarm_thread)

add_library(${PROJECT_NAME} AlarmThread.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC alarm audio_fake)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
