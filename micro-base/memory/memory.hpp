#pragma once
#include "../mbase.hpp"

namespace memory
{
    std::uintptr_t* scan(const char* signature);

    std::uintptr_t dereference(uintptr_t address, unsigned int offset);
}