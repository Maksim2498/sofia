# Globals setup

cmake_minimum_required(VERSION 3.31)

project(
    sofia
    VERSION 0.1.0
    DESCRIPTION "Sofia programming language"
    LANGUAGES CXX
)

# Target setup

# - Variables

set(TARGET_NAME "${CMAKE_PROJECT_NAME}")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# - Creation

add_executable("${TARGET_NAME}" "${SRC_DIR}/sofia/main.cpp")

# - Modules addition

file(GLOB_RECURSE MODULES CONFIGURE_DEPENDS "${SRC_DIR}/*.cppm")

target_sources(
    "${TARGET_NAME}"
    PUBLIC FILE_SET CXX_MODULES
    FILES "${MODULES}"
)

# - Include paths

target_include_directories("${TARGET_NAME}" PUBLIC "${SRC_DIR}")

# - Properties setup

set_target_properties(
    "${TARGET_NAME}"

    PROPERTIES

    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)

target_compile_options(
    "${TARGET_NAME}"

    PUBLIC

    "$<$<CXX_COMPILER_ID:MSVC>:/W4;/experimental:module;/std:c++latest;/utf-8>"
    "$<$<CXX_COMPILER_ID:Clang>:-fmodules>"
    "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall;-Wextra;-Wpedantic;-Wshadow;-Wpointer-arith;-Wcast-qual;-finput-charset=UTF-8;-fexec-charset=UTF-8>"
)