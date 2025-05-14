cmake_minimum_required(VERSION 3.14)
project(alarm_project)

option(CODE_COVERAGE ON)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  option(CODE_COVERAGE "Enable coverage reporting" ON)
endif()

if(CODE_COVERAGE)
  message(STATUS "Code coverage enabled")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g -fprofile-abs-path)
    add_link_options(--coverage)
  endif()
endif()


include(CTest)

add_subdirectory(application/AlARM)
add_subdirectory(application/AudioTest)
add_subdirectory(application/NameString)
add_subdirectory(test)


