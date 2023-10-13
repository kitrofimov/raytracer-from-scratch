#ifdef __linux__
    #include <sys/ioctl.h>
    #include <stdio.h>
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

#include "utils/vec/vec2.hpp"
#include "get_terminal_size.hpp"

vec2i get_terminal_size()
{
    #ifdef __linux__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int cols = w.ws_col;
        int rows = w.ws_row;
    #elif _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #endif
    return vec2i(cols, rows);
}
