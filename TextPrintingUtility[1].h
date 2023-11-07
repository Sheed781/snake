#ifndef TEXT_PRINTING_UTILITY_H
#define TEXT_PRINTING_UTILITY_H

#include <Windows.h>

void print_string(HANDLE h_out, POINT location, WORD color, const char*);
void print_value(HANDLE h_out, POINT location, WORD color, SHORT);

#endif