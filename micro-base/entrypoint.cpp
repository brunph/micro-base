#include "mbase.hpp"

auto detach()
{
	// do any unhooking here
}


auto entry(void* thread_param) -> BOOL
{
	input::initialize();

	sdk.initialize();

	// this is gonna be replaced with proper input checking in the future
	while (!input::get_input_state(VK_END))
		std::this_thread::sleep_for(250ms);
	
	FreeLibraryAndExitThread(static_cast<HMODULE>(thread_param), EXIT_SUCCESS);
}

// ReSharper disable once CppInconsistentNaming
auto __stdcall DllMain(const HMODULE module, const DWORD reason, LPVOID reserved) -> BOOL
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);

		if (auto* handle = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(entry), module, NULL, nullptr))
		{
			CloseHandle(handle);
		}
	}
	
    return TRUE;
}

