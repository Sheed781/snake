#ifndef SPRITE_H
#define SPRITE_H

#include "ConsoleInputScanner.h"

class Sprite
{
public:
	virtual ~Sprite() {}
	virtual void poll(const ConsoleInputScanner&) = 0;
	virtual bool step() = 0;	// Shall return true if a subsequent redraw is needed
	virtual void initial_draw(HANDLE h_out) const = 0;
	virtual void redraw(HANDLE h_out) = 0;
};

#endif
