#include <cstdint>
#include <cstdio>

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "term.h"

namespace flags {
    // Input mode flags: no break, no CR to NL, no parity check, no strip char, no start/stop output control.
    constexpr tcflag_t RawInput = ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    // Output mode flags: disable post processing.
    constexpr tcflag_t NoPostProcessing = ~(OPOST);
    // Control mode flags: set 8 bit chars.
    constexpr tcflag_t ControlMode8Bit = (CS8);
    // Local mode flags: echo off, canonical off, no extended functions, no signal chars (^Z, ^C).
    constexpr tcflag_t RawLocal = ~(ECHO | ICANON | IEXTEN | ISIG);
    // Control characters: no minimum number of bytes.
    constexpr tcflag_t MinBytes = 0;
    // Control characters: 100ms timout.
    constexpr tcflag_t Timeout = 1;
}

struct termios initial_state;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &initial_state);
}

termios get_raw_attr(termios current) {
    auto raw = current;

    raw.c_iflag &= flags::RawInput;
    raw.c_oflag &= flags::NoPostProcessing;
    raw.c_cflag |= flags::ControlMode8Bit;
    raw.c_lflag &= flags::RawLocal;
    raw.c_cc[VMIN] = flags::MinBytes;
    raw.c_cc[VTIME] = flags::Timeout;

    return raw;
}

term::RawModeResult term::enable_raw_mode() {
    if (!isatty(STDIN_FILENO)) {
        return RawModeResult::InvalidTty;
    }

    if (tcgetattr(STDIN_FILENO, &initial_state) < 0) {
        return RawModeResult::FailedToRetrieveTermAttr;
    }
    
    atexit(disable_raw_mode);

    const auto raw_term_state = get_raw_attr(initial_state);

    // Flush terminal and set raw mode.
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_term_state) < 0) {
        return RawModeResult::FailedToSetRawAttr;
    }

    return RawModeResult::Ok;
}

// Keys input from user can have up to 4 bytes.
// Each key is read directly onto a uint32_t instead of the typical char[]. 
// This greatly simplifies the implementation.
// TODO: 
//  Byte endianness is affected by the order in which term input sets the bytes on the buffer.
//  For now, assume that Big Endian is standard for Linux.
//  Research documentation to find out if this order may change across platforms.
term::Key term::read_key() {
    uint32_t code {0};
    const auto size = (size_t) read(STDIN_FILENO, &code, sizeof(uint32_t));
    return term::Key { .code = code, .size = size };
}

void term::write_bytes(const void* buffer, size_t size) {
    write(STDOUT_FILENO, buffer, size);
}

void term::flush() {
    fflush(stdout);
}