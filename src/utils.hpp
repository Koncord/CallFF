#ifndef CALLFF_UTILS
#define CALLFF_UTILS

#include <cstdint>
#include <cstddef>
#include <initializer_list>
#include <algorithm>

namespace utils
{
    inline size_t braceToString(std::initializer_list<unsigned char> c, unsigned char* str) noexcept
    {
        std::copy(c.begin(), c.end(), str);
        return c.size();
    }
    void Value64ToString(uint64_t addr, unsigned char *code, size_t &codeOffset) noexcept;
    void Value32ToString(uint32_t addr, unsigned char *code, size_t &codeOffset) noexcept;
}

#endif // CALLFF_UTILS
