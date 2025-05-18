cmake_minimum_required(VERSION 3.14)
project(alarm_app_test)

add_executable (${PROJECT_NAME} AlARM_app_t.cpp )
target_link_libraries(${PROJECT_NAME} gtest_main alarm alarm_thread)
add_test(${PROJECT_NAME} ${PROJECT_NAME} --gtest_color=yes)

