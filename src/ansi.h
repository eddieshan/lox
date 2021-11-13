namespace term::ansi {
    constexpr unsigned char Seq[] = "\x1b[";
    constexpr unsigned char Clear[] = "\x1b[2J";
    constexpr unsigned char Reset[] = "\x1b[0m";
    constexpr unsigned char Pos[] = "H";
    constexpr unsigned char NextLine[] = "\x1b[1E";
    constexpr unsigned char Home[] = "\x1b[H";
    constexpr unsigned char Del1[] = "\x1b[1P";
    constexpr unsigned char BackDel1[] = "\x1b[1D\x1b[1P";
    constexpr unsigned char Underline[] = "\x1b[4m";
    constexpr unsigned char StrikeThrough[] = "\x1b[9m";
}