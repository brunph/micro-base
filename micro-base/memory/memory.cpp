#include "memory.hpp"
namespace memory
{
    std::uintptr_t* scan(const char* signature) {
        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int>{};
            auto* start = const_cast<char*>(pattern);
            auto* end = const_cast<char*>(pattern) + strlen(pattern);

            for (auto* current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;
                    if (*current == '?')
                        ++current;
                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(strtoul(current, &current, 16));
                }
            }
            return bytes;
        };

        auto* const module = GetModuleHandle(nullptr);

        auto* const dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dos_header->e_lfanew);

        const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
        auto pattern_bytes = pattern_to_byte(signature);
        auto* scan_bytes = reinterpret_cast<std::uint8_t*>(module);

        const auto s = pattern_bytes.size();
        auto* const d = pattern_bytes.data();

        for (auto i = 0ul; i < size_of_image - s; ++i) {
            auto found = true;
            for (auto j = 0ul; j < s; ++j) {
                if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return reinterpret_cast<std::uintptr_t*>(&scan_bytes[i]);
            }
        }
        return nullptr;
    }
	
    std::uintptr_t dereference(const uintptr_t address, const unsigned int offset) {
        return address == 0 ? reinterpret_cast<std::uintptr_t>(nullptr) : address +
            static_cast<int>(*reinterpret_cast<int*>(address + offset) +
	            offset + sizeof(int));
    }
}
