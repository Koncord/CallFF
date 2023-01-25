#ifndef CALLFF_CALL_HPP
#define CALLFF_CALL_HPP

#include <cstdint>
#include <sys/types.h>
#include "callarg.hpp"

#define CALLFF_VERSION_MAJOR 0
#define CALLFF_VERSION_MINOR 2
#define CALLFF_VERSION_REVISION 0

#define CALLFF_VERSION_STRING "0.2.0"

typedef uintptr_t (*Func)();

uintptr_t Call(Func &fCpp, CallArgs &data) noexcept;

#endif //CALLFF_CALL_HPP
