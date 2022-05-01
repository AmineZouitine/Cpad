cmake_minimum_required(VERSION 3.10)

project(cpad)

set(TARGET_NAME "cpad")
set(COMPILE_OPTIONS -Wall -Wextra -Werror -pedantic)

# Global compile options
add_compile_options(${COMPILE_OPTIONS})

add_subdirectory(src)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Use C++ 20
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
