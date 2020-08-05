#pragma once
#include "../mbase.hpp"

namespace input
{
	inline HWND hwnd{};
	
	extern void initialize();
	
	extern short get_input_state(int virtual_key);

}