cmake_minimum_required(VERSION 3.10)

project(cpad)

set(TARGET_NAME "cpad")
set(COMPILE_OPTIONS -Wall -Wextra -Werror -pedantic)
set(CMAKE_STATIC_LIBRARY_PREFIX_CXX "")

# GTest
find_package(GTest REQUIRED)

# Global compile options
add_compile_options(${COMPILE_OPTIONS})

add_subdirectory(src)


add_library(libcpad STATIC ${SOURCE_FILES})

add_executable(${TARGET_NAME} ${EXECUTABLE_SOURCE_FILES})
target_link_libraries(${TARGET_NAME} PRIVATE libcpad)

add_subdirectory(tests/)

add_executable(unit-tests ${TEST_SOURCES_FILES})
target_link_libraries(unit-tests gtest libcpad)

# Discover tests
include(GoogleTest)
gtest_discover_tests(unit-tests)

# Use C++ 20
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_compile_features(libcpad PRIVATE cxx_std_20)
