#ifndef CALLFF_CALL_HPP
#define CALLFF_CALL_HPP

#include <cstdint>
#include "callarg.hpp"

#define CALLFF_VERSION_MAJOR 0
#define CALLFF_VERSION_MINOR 1
#define CALLFF_VERSION_REVISION 0

#define CALLFF_VERSION_STRING "0.1.0"

typedef uintptr_t (*Func)();

uintptr_t Call(Func &fCpp, CallArgs &data) noexcept;

#endif //CALLFF_CALL_HPP
