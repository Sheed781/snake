#include <iostream>
#include <list>
#include "Sprite.h"
#include "Point.h"
#include "ConsoleInputScanner.h"

class Snake : public Sprite
{
public:

	Snake(int start_x, int start_y, int init_length, int speed, WORD head_color, WORD body_color)
		: speed(speed), elapsed(0), head_color(head_color), body_color(body_color),
		cur_direction(DIRECTION::RIGHT), next_direction(DIRECTION::RIGHT), body(), growing(false)
	{
		for (int i = 0; i < init_length; ++i) {
			body.push_back(Point(start_x - i, start_y));
		}
	}
	void poll(const ConsoleInputScanner& scanner) override
	{
		if ((scanner.key_is_pressed(VK_LEFT) || scanner.key_is_pressed('A')) && cur_direction != DIRECTION::RIGHT) {
			next_direction = DIRECTION::LEFT;
		}
		if ((scanner.key_is_pressed(VK_RIGHT) || scanner.key_is_pressed('D')) && cur_direction != DIRECTION::LEFT) {
			next_direction = DIRECTION::RIGHT;
		}
		if ((scanner.key_is_pressed(VK_UP) || scanner.key_is_pressed('W')) && cur_direction != DIRECTION::DOWN) {
			next_direction = DIRECTION::UP;
		}
		if ((scanner.key_is_pressed(VK_DOWN) || scanner.key_is_pressed('S')) && cur_direction != DIRECTION::UP) {
			next_direction = DIRECTION::DOWN;
		}
	}
	bool step() override
	{
		if (++elapsed == speed) {
			// Push a point onto the front of the list for the new location of the head
			std::list<Point>::const_iterator hit = body.begin();
			std::list<Point>::const_iterator nit = hit;
			++nit;
			if (next_direction == DIRECTION::RIGHT) {
				body.push_front(Point(hit->x + 1, hit->y));
			}
			else if (next_direction == DIRECTION::LEFT) {
				body.push_front(Point(hit->x - 1, hit->y));
			}
			else if (next_direction == DIRECTION::DOWN) {
				body.push_front(Point(hit->x, hit->y + 1));
			}
			else if (next_direction == DIRECTION::UP) {
				body.push_front(Point(hit->x, hit->y - 1));
			}
			cur_direction = next_direction;
			elapsed = 0;
			return true;
		}
		return false;
	}
	void initial_draw(HANDLE h_out) const override
	{
		DWORD result;
		WriteConsoleOutputAttribute(h_out, &head_color, 1, COORD{ body.front().x, body.front().y }, &result);
		for (std::list<Point>::const_iterator it = body.cbegin(); ++it != body.cend();) {
			WriteConsoleOutputAttribute(h_out, &body_color, 1, COORD{ it->x, it->y }, &result );
		}
	}
	void redraw(HANDLE h_out) override
	{
		DWORD result;
		std::list<Point>::const_iterator it = body.begin();

		// draw the new position of the head using the head color
		WriteConsoleOutputAttribute(h_out, &head_color, 1, COORD{ it->x, it->y }, &result);

		// redraw the previous position of the head using the body color
		++it;
		WriteConsoleOutputAttribute(h_out, &body_color, 1, COORD{ it->x, it->y }, &result);

		if (growing) {
			growing = false;
		} else {
			// erase the tail from output screen and the body list
			std::list<Point>::const_reverse_iterator it = body.rbegin();
			WORD black = 0x0000;
			WriteConsoleOutputAttribute(h_out, &black, 1, COORD{ it->x, it->y }, &result);
			body.pop_back();
		}
	}
	Point get_head_location() const
	{
		return body.front();
	}
	void elongate()
	{
		growing = true;
	}
	bool overlaps_body(Point pt) const {	// Returns true if and only if pt overlaps the portion
											// of the body not including the head.
		for (std::list<Point>::const_iterator it = body.begin(); ++it != body.end();) {
			if (*it == pt) {
				return true;
			}
		}
		return false;
	}

private:
	int speed;		// number of frames per movement
	int elapsed;	// number of frames since last movement
	WORD head_color;
	WORD body_color;
	enum class DIRECTION { UP, DOWN, LEFT, RIGHT };
	DIRECTION cur_direction;
	DIRECTION next_direction;
	std::list<Point> body;	// The head of the snake is at the front of the list.
							// The tail of the snake is at the back of the list.
	bool growing;
};