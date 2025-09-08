# Globals setup

cmake_minimum_required(VERSION 3.31)

project(
    sofia
    VERSION 0.1.0
    DESCRIPTION "Sofia programming language"
    LANGUAGES CXX
)

# re2c lookup

find_program(RE2C_EXECUTABLE re2c)

if(NOT RE2C_EXECUTABLE)
    message(FATAL_ERROR "re2c not found! Please install re2c.")
endif()

# - Tokenizer setup

set(TOKENIZER_INPUT "${SRC_DIR}/sofia/parsing/lexis/tokenizer.cppm")
set(TOKENIZER_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/tokenizer.gen.cppm")

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
    PRIVATE FILE_SET CXX_MODULES
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