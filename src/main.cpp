#include <iostream>

#include "editor.h"

int main()
{
    std::cout << "Starting Lox" << std::endl;

    Editor::instance().start();
}