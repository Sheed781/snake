#ifndef FOOD_H
#define FOOD_H

#include "Sprite.h"
#include "Point.h"

class Food : public Sprite
{
public:
	Point location;
	WORD color;

	Food(int x, int y, WORD color) : location(x, y), color(color) { }
	void poll(const ConsoleInputScanner& scanner) override {}
	bool step() override { return false; }		// Food stays put, and so doesn't have to be updated.
	void initial_draw(HANDLE h_out) const override
	{
		DWORD result;
		WriteConsoleOutputAttribute(h_out, &color, 1, COORD{ location.x, location.y }, &result);
	}
	void redraw(HANDLE h_out) override {}	// Food stays put, and so doesn't have to be redrawn.
};

#endif