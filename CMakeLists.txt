cmake_minimum_required(VERSION 3.13.4)

project(lox VERSION 0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/utils/convert.cpp
    src/utils/geometry.cpp
    src/term/ansi.cpp
    src/term/term.cpp
    src/buffers/gap_buffer.cpp
    src/buffers/fixed_buffer.cpp
    src/buffers/piece.cpp
    src/buffers/piece_table.cpp
    src/syntax/tokenize.cpp
    src/syntax/grammar.cpp
    src/text/navigation.cpp
    src/models/text_area.cpp
    src/views/text_view.cpp
    src/views/syntax_view.cpp
    src/views/line_counter_view.cpp
    src/views/status_bar_view.cpp
    src/views/cursor.cpp
    src/components/controller.cpp
    src/components/view.cpp
    src/components/editor.cpp
    src/settings/theme.cpp    
    src/main.cpp
)

add_executable(lox ${SOURCES})

target_compile_features(lox PUBLIC cxx_std_17)