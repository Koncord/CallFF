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

        for (int i = 0; i < sizeof(uint64_t); i++)
            code[codeOffset + sizeof(uint64_t) -1 - i] = (unsigned char) (ad >> (i * 8));

        codeOffset += sizeof(uint64_t);
    }


    void Value32ToString(uint32_t val, unsigned char *code, size_t &codeOffset) noexcept
    {
#ifdef _MSC_VER
        uint32_t ad = _byteswap_ulong(val);
#else
        uint32_t ad = __builtin_bswap32(val);
#endif

        for (int i = 0; i < sizeof(uint32_t); i++)
            code[codeOffset + sizeof(uint32_t) - 1 - i] = (unsigned char) (ad >> (i * 8));

        codeOffset += sizeof(uint32_t);
    }
}
