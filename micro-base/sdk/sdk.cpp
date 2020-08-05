#include "sdk.hpp"

auto sdk_t::initialize() -> void
{
	m_is_dlc_present = reinterpret_cast<decltype(m_is_dlc_present)>(memory::scan("48 89 5C 24 ? 57 48 83 EC 20 81 F9 ? ? ? ?"));
}