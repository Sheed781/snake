#include <random>
#include <chrono>
#include "Snake.h"
#include "Food.h"
#include "TextPrintingUtility.h"

class World
{
public :
	World(SHORT height, SHORT width, int snake_init_len, int snake_init_speed)
		: snake(snake_init_len + 2, height / 2, snake_init_len, snake_init_speed,
			BACKGROUND_GREEN, BACKGROUND_GREEN | BACKGROUND_RED),
		food(width - 4, height / 2, BACKGROUND_RED),
		height(height),
		width(width),
		points(0),
		score_text_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
		generator(std::chrono::system_clock::now().time_since_epoch().count()),
		distribution()
	{
	}
	bool done() const
	{
		// check if snake head is on/outside the rectangular boundary or overlaps with its own body.
		Point pt = snake.get_head_location();
		if (pt.x <= 0 || pt.y <= 0 || pt.x >= width - 1 || pt.y >= height - 1 || snake.overlaps_body(pt)) {
			return true;
		}
		return false;
	}
	void poll(const ConsoleInputScanner& scanner)
	{
		snake.poll(scanner);
		food.poll(scanner);
	}
	void step(HANDLE h_out)
	{
		bool redraw_snake = snake.step();

		// if snake ate the food, respawn it elsewhere on the board, lengthen the snake,
		// update and redraw the score
		if (food.location == snake.get_head_location()) {
			Point pt;
			do {
				pt.x = distribution(generator) % (width - 2) + 1;
				pt.y = distribution(generator) % (height - 2) + 1;
			} while (pt == snake.get_head_location() || snake.overlaps_body(pt));
			food.location = pt;
			food.initial_draw(h_out);
			snake.elongate();
			print_value(h_out, { 7, height }, score_text_color, ++points);
		}

		if (redraw_snake) {
			snake.redraw(h_out);
		}
	}
	void initial_draw(HANDLE h_out) const
	{
		snake.initial_draw(h_out);
		food.initial_draw(h_out);
		
		// draw the rectangular boundary
		DWORD result;
		WORD border_color = BACKGROUND_BLUE;
		for (SHORT x = 0; x < width; ++x) {
			WriteConsoleOutputAttribute(h_out, &border_color, 1, COORD{ x, 0 }, &result);
			WriteConsoleOutputAttribute(h_out, &border_color, 1, COORD{ x, height - 1 }, &result);
		}
		for (SHORT y = 0; y < height; ++y) {
			WriteConsoleOutputAttribute(h_out, &border_color, 1, COORD{ 0, y }, &result);
			WriteConsoleOutputAttribute(h_out, &border_color, 1, COORD{ width - 1, y }, &result);
		}
		// draw score label
		print_string(h_out, { 0, height }, score_text_color, "Score: 0");
	}

private:
	Snake snake;
	Food food;
	SHORT height;
	SHORT width;
	int points;
	WORD score_text_color;
	std::default_random_engine generator;
	std::uniform_int_distribution<SHORT> distribution;
};