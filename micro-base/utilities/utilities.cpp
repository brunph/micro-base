#include "utilities.hpp"

auto input::initialize() -> void
{
	// we will use the window class to find it, cause the window name could be something else you never know :O 
	hwnd = FindWindowA("grcWindow", nullptr);
}

[[nodiscard]] auto input::get_input_state(const int virtual_key) -> short
{
	if (GetForegroundWindow() != hwnd)
		return FALSE;

	if (!(GetAsyncKeyState(virtual_key) & 0x8000))
		return FALSE;
	
	return TRUE;
}
