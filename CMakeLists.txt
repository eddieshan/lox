cmake_minimum_required(VERSION 3.13.4)

project(lox VERSION 0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/gap_buffer.cpp
    src/fixed_buffer.cpp
    src/editor.cpp
    src/term.cpp
    src/main.cpp
)

add_executable(lox ${SOURCES})

target_compile_features(lox PUBLIC cxx_std_17)