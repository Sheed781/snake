#include <chrono>
#include "World.h"
#include "TextPrintingUtility.h"

using namespace std::chrono;

#define WORLD_HEIGHT 20
#define WORLD_WIDTH 50
#define SNAKE_START_LEN 5
#define SNAKE_START_SPEED 7
#define FRAME_RATE 15 // milliseconds per frame

int main() {
	
	// Get a handle to the console output screen
	HANDLE handle_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleInputScanner scanner(GetStdHandle(STD_INPUT_HANDLE));

	if (handle_std_out == INVALID_HANDLE_VALUE || handle_std_out == NULL) {
		return -1;
	}

	// Hide the text cursor
	CONSOLE_CURSOR_INFO hidden_cursor = { 100, false };
	SetConsoleCursorInfo(handle_std_out, &hidden_cursor);

	// Create the world object
	World world(WORLD_HEIGHT, WORLD_WIDTH, SNAKE_START_LEN, SNAKE_START_SPEED);
	world.initial_draw(handle_std_out);

	// Run the game loop until game over
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (!world.done()) {

		scanner.step();
		world.poll(scanner);

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		milliseconds time_span = duration_cast<milliseconds>(t2 - t1);

		if (time_span.count() > FRAME_RATE) {
			world.step(handle_std_out);
			t1 = t2;
		}
	}

	// Game over
	print_string(handle_std_out, { 0, WORLD_HEIGHT + 1 }, FOREGROUND_RED, "Game over! Press ENTER to close.");

	while (!scanner.key_just_pressed(VK_RETURN)) {
		scanner.step();
	}
	
	return 0;
}
