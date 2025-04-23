cmake_minimum_required(VERSION 3.14)
project(alarm_project)

option(CODE_COVERAGE ON)

enable_testing()

#if(CODE_COVERAGE)
    add_compile_options(--coverage -O0 -g)
	add_link_options(--coverage)
#endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CTest)

add_subdirectory(src)
add_subdirectory(test)


