#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <cstdio>
#include "Config.h"

// Console cursor positioning function
inline void gotoxy(int x, int y, const char* s) {
    COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

#endif // UTILS_H
