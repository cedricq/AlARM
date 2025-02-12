cmake_minimum_required(VERSION 3.14)
project(my_alarm_project)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER "g++" )
set(CMAKE_C_COMPILER "gcc" )
set(CMAKE_CXX_FLAGS "-isystem -mconsole -std=c++20 -fpermissive -pthread")
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

include_directories("inc")

add_executable (alarm_test src/AlARM.cpp src/NameString.cpp test/AlARM_t.cpp)
target_link_libraries(alarm_test gtest_main)
add_test(alarm_test alarm_test)
