#ifndef CALLFF_CALLGEN_HPP
#define CALLFF_CALLGEN_HPP

#include <callarg.hpp>

typedef uintptr_t (*Func)();

size_t GenerateCode(Func &fCpp, CallArgs &data, unsigned char *code) noexcept;

#endif //CALLFF_CALLGEN_HPP
