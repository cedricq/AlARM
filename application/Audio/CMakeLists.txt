cmake_minimum_required(VERSION 3.14)
project(audioI)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} INTERFACE alarm_lib)

add_subdirectory(AudioFake)