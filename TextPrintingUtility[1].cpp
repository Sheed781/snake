#include <cstring>
#include <sstream>
#include "TextPrintingUtility.h"

void print_string(HANDLE h_out, POINT location, WORD color, const char* str)
{
	// todo
	size_t len = strlen(str);
	CHAR_INFO* ci_str = new CHAR_INFO[len];
	for (size_t i = 0; i < len; ++i) {
		ci_str[i].Char.UnicodeChar = 0;
		ci_str[i].Char.AsciiChar = str[i];
		ci_str[i].Attributes = color;
	}
	SMALL_RECT write_region = { location.x, location.y, location.x + len - 1, location.y };
	WriteConsoleOutput(h_out, ci_str, { (SHORT)len, 1 }, { 0, 0 }, &write_region);
}

void print_value(HANDLE h_out, POINT location, WORD color, SHORT val)
{
	std::stringstream ss;
	ss << val;
	std::string str = ss.str();
	CHAR_INFO score[10];
	for (size_t i = 0; i < str.length(); ++i) {
		score[i].Char.UnicodeChar = 0;
		score[i].Char.AsciiChar = str[i];
		score[i].Attributes = color;
	};
	SMALL_RECT write_region = { location.x, location.y, location.x + (SHORT)str.length() - 1, location.y };
	WriteConsoleOutput(h_out, score, { (SHORT)str.length(), 1 }, { 0, 0 }, &write_region);
}