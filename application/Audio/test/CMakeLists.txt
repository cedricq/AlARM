cmake_minimum_required(VERSION 3.14)
project(audio_test)

add_executable (${PROJECT_NAME} AudioFake_t.cpp )
target_link_libraries(${PROJECT_NAME} gtest_main audio_fake )
add_test(${PROJECT_NAME} ${PROJECT_NAME} --gtest_color=yes)

enable_coverage(${PROJECT_NAME})

