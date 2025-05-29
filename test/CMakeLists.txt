cmake_minimum_required(VERSION 3.14)
project(alarm_app)

add_executable (${PROJECT_NAME}_test AlARM_app_t.cpp )
target_link_libraries(${PROJECT_NAME}_test gtest_main alarm alarm_thread)
add_test(${PROJECT_NAME} ${PROJECT_NAME}_test --gtest_color=yes)

add_executable (${PROJECT_NAME} AlARM_app.cpp )
target_link_libraries(${PROJECT_NAME} alarm alarm_thread)



