#include "utils.hpp"

namespace utils
{
    void Value64ToString(uint64_t val, unsigned char *code, size_t &codeOffset) noexcept
    {
#ifdef _MSC_VER
        uint64_t ad = _byteswap_uint64(val);
#else
        uint64_t ad = __builtin_bswap64(val);
#endif

        for (int i = 0; i < 8; i++)
            code[codeOffset + 7 - i] = (unsigned char) (ad >> (i * 8));

        codeOffset += 8;
    }


    void Value32ToString(uint32_t val, unsigned char *code, size_t &codeOffset) noexcept
    {
#ifdef _MSC_VER
        uint32_t ad = _byteswap_ulong(val);
#else
        uint32_t ad = __builtin_bswap32(val);
#endif

        for (int i = 0; i < 4; i++)
            code[codeOffset + 3 - i] = (unsigned char) (ad >> (i * 8));

        codeOffset += 4;
    }
}
