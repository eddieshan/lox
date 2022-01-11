cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconcepts")

project(lox VERSION 0.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/utils/slice.cpp
    src/utils/convert.cpp
    src/utils/geometry.cpp
    src/utils/packed_array.cpp
    src/utils/io.cpp    
    src/term/ansi.cpp
    src/term/term.cpp
    src/buffers/vt100_buffer.cpp
    src/buffers/piece.cpp
    src/buffers/piece_table.cpp
    src/syntax/tokenize.cpp
    src/syntax/grammar.cpp
    src/text/navigation.cpp
    src/models/command.cpp
    src/models/editor_state.cpp
    src/views/plain_text.cpp
    src/views/syntax.cpp
    src/views/line_counter.cpp
    src/views/status_bar.cpp
    src/views/command_line.cpp
    src/views/edit.cpp
    src/controllers/edit_controller.cpp
    src/controllers/command_controller.cpp    
    src/components/editor.cpp
    src/settings/theme.cpp
    src/main.cpp
)

add_executable(lox ${SOURCES})

target_compile_features(lox PUBLIC cxx_std_20)
