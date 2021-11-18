# lox

Lox (funky transliteration of LOCs) is a terminal code editor inspired by Vim.
It was born out of a "if I had dime ...". 
As in, if I had written a chunk of code for every time I complained about never finding the ideal code editor, by now I might have one of my own.

If code is a craft and decent craftsmen make their own tools, it makes sense to roll out your own code editor.

It has zero dependencies (no ncurses).
For the language heavy lifting parts eg. LSP support I expect I will need to integrate external libs.
But that will not happen short term, till then zero deps it is. 

This project was actually started in Rust, you can check it out [here](https://github.com/eddieshan/foo-editor).
Some time after, a few handicaps became apparent,

- A code editor makes intense use of data structures, some of which may easily be cyclic.
  This can be done in Rust but is usually cumbersome and non idiomatic.
  Text data structures are essential for a code editor so this is a part where I wanted to work comfortably.

- Templates.
  The first use case that came to mind was combining different VT100 escape sequences in compile time.
  In general, there is a lot of buffering involved where minimizing allocations is a big win.
  Intuitively, I expected templates would be very useful in this area despite not seeing all the use cases yet. 
  Rust templates are not so powerful but C++'s should do the job just fine.

- External libs.
  As stated above, for the language heavy lifting I may resort to external libs which may not be available as Rust crates.
  Probably easier to do in C++ since Rust's FFI story is not that great.
  Not a deal breaker but it stacked up on top of the others.