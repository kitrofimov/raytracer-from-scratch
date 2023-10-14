#pragma once
#include <format>
#include <stdexcept>

// See this page for more information:
// https://en.wikipedia.org/wiki/ANSI_escape_code

// ===========================================
// CSI (Control Sequence Introducer) sequences
// ===========================================

#define CURSOR_UP(n)          ("\33[" + std::to_string(n) + "A")
#define CURSOR_DOWN(n)        ("\33[" + std::to_string(n) + "B")
#define CURSOR_RIGHT(n)       ("\33[" + std::to_string(n) + "C")
#define CURSOR_LEFT(n)        ("\33[" + std::to_string(n) + "D")
#define CURSOR_POSITION(x, y) ("\33[" + std::to_string(y) + ";" + std::to_string(x) + "H")
#define ERASE_IN_DISPLAY(n)   ("\33[" + std::to_string(n) + "J")
#define ERASE_IN_LINE(n)      ("\33[" + std::to_string(n) + "K")

// =========================================
// SGR (Select Graphic Rendition) parameters
// =========================================

#define GENERIC_SGR(n)               ("\33[" + std::to_string(n) + "m")
#define RESET                        "\33[0m"
#define BOLD                         "\33[1m"
#define FAINT                        "\33[2m"
#define ITALIC                       "\33[3m"
#define UNDERLINE                    "\33[4m"
#define SLOW_BLINK                   "\33[5m"
#define RAPID_BLINK                  "\33[6m"
#define CROSSED_OUT                  "\33[9m"
#define DOUBLE_UNDERLINE             "\33[21m"
#define NORMAL_INTENSITY             "\33[22m"
#define NO_ITALIC                    "\33[23m"
#define NO_UNDERLINE                 "\33[24m"
#define NO_BLINK                     "\33[25m"
#define NO_CROSSED_OUT               "\33[29m"
#define FOREGROUND(n)                ("\33[38;5;" + std::to_string(n) + "m")
#define FOREGROUND_RGB(r, g, b)      ("\33[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m")
#define BACKGROUND(n)                ("\33[48;5;" + std::to_string(n) + "m")
#define BACKGROUND_RGB(r, g, b)      ("\33[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m")
#define DISABLE_PROPORTIONAL_SPACING "\33[50m"
#define OVERLINE                     "\33[53m"
#define NO_OVERLINE                  "\33[55m"
#define UNDERLINE_COLOR              "\33[58m"
