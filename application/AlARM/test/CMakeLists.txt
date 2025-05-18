cmake_minimum_required(VERSION 3.14)
project(alarm_test)

add_executable (${PROJECT_NAME} AlARM_t.cpp )
target_link_libraries(${PROJECT_NAME} gtest_main alarm audio_fake)
add_test(${PROJECT_NAME} ${PROJECT_NAME} --gtest_color=yes)

