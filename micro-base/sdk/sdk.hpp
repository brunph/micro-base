#pragma once
#include "../mbase.hpp"

struct sdk_t
{
	using is_dlc_present = bool(std::uint32_t hash);
	is_dlc_present* m_is_dlc_present;

	void initialize();
}; inline sdk_t sdk;