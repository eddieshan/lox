cmake_minimum_required(VERSION 3.13.4)

project(lox VERSION 0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/term/term.cpp
    src/buffers/gap_buffer.cpp
    src/buffers/fixed_buffer.cpp
    src/buffers/piece.cpp
    src/buffers/piece_table.cpp
    src/components/text_view.cpp    
    src/components/cursor.cpp
    src/components/editor.cpp
    src/main.cpp
)

add_executable(lox ${SOURCES})

target_compile_features(lox PUBLIC cxx_std_17)