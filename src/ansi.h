namespace term::ansi {
    constexpr uint8_t Seq[] = "\x1b[";
    constexpr uint8_t Clear[] = "\x1b[2J";
    constexpr uint8_t Reset[] = "\x1b[0m";
    constexpr uint8_t Pos[] = "H";
    constexpr uint8_t NextLine[] = "\x1b[1E";
    constexpr uint8_t Home[] = "\x1b[H";
    constexpr uint8_t Del1[] = "\x1b[1P";
    constexpr uint8_t BackDel1[] = "\x1b[1D\x1b[1P";
    constexpr uint8_t Underline[] = "\x1b[4m";
    constexpr uint8_t StrikeThrough[] = "\x1b[9m";
}