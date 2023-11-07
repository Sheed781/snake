#include <cstring>
#include <climits>
#include "ConsoleInputScanner.h"
#include "verify.h"

ConsoleInputScanner::ConsoleInputScanner(HANDLE input_handle)
	: input_handle(input_handle)
{
	memset(key_states, 0, 2 * 256 * sizeof(bool) * (CHAR_BIT / 8));
	step();
}

void ConsoleInputScanner::step()
{
	cur_key_state = 1 - cur_key_state;
	memcpy(key_states[cur_key_state], key_states[1 - cur_key_state], 256 * sizeof(bool) * (CHAR_BIT / 8));

	verify(GetNumberOfConsoleInputEvents(input_handle, &num_events));

	if (!num_events)
		return;

	verify(ReadConsoleInput(input_handle, arr_input_records, MAX_INPUT_RECORDS, &num_events));

	for (DWORD i = 0; i < num_events; ++i)
	{
		switch (arr_input_records[i].EventType)
		{
		case KEY_EVENT:
			key_states[cur_key_state][arr_input_records[i].Event.KeyEvent.wVirtualKeyCode] =
				(arr_input_records[i].Event.KeyEvent.bKeyDown == TRUE);
			break;
		}
	}
}

bool ConsoleInputScanner::key_is_pressed(WORD virtualKey) const
{
	return key_states[cur_key_state][virtualKey];
}

bool ConsoleInputScanner::key_is_released(WORD virtualKey) const
{
	return !key_states[cur_key_state][virtualKey];
}

bool ConsoleInputScanner::key_just_toggled(WORD virtualKey) const
{
	return key_states[cur_key_state][virtualKey] != key_states[1 - cur_key_state][virtualKey];
}

bool ConsoleInputScanner::key_just_pressed(WORD virtualKey) const
{
	return key_states[cur_key_state][virtualKey] && !key_states[1 - cur_key_state][virtualKey];
}

bool ConsoleInputScanner::key_just_released(WORD virtualKey) const
{
	return !key_states[cur_key_state][virtualKey] && key_states[1 - cur_key_state][virtualKey];
}
