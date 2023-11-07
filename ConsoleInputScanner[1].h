#ifndef CONSOLEINPUTSCANNER_H
#define CONSOLEINPUTSCANNER_H

#include <Windows.h>

const DWORD MAX_INPUT_RECORDS = 50;

class ConsoleInputScanner
{
public:

	// Constructors
	ConsoleInputScanner(HANDLE input_handle);

	// Updates the status of the virtual keys
	void step();

	// Check if specified virtual key (e.g. VK_RETURN) is down/up or has changed
	bool key_is_pressed(WORD) const;
	bool key_is_released(WORD) const;
	bool key_just_toggled(WORD) const;
	bool key_just_pressed(WORD) const;
	bool key_just_released(WORD) const;

private:

	HANDLE input_handle;
	INPUT_RECORD arr_input_records[MAX_INPUT_RECORDS];
	DWORD num_events;

	bool key_states[2][256];
	unsigned int cur_key_state; // Either 0 or 1. Specifies whether to use key_states[0] or key_states[1]
};

#endif