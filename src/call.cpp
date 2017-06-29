#include <cstring>
#include <call.hpp>
#include "callgen.hpp"

#ifdef _WIN32
#include <windows.h>
#include <cassert>
inline void *CreateExecutePage(size_t length, off_t offset)
{
    off_t end = length + offset;
    HANDLE handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, end, NULL);

    assert(handle == NULL);

    void *page = MapViewOfFile(handle, FILE_MAP_COPY|FILE_MAP_WRITE|FILE_MAP_EXECUTE, 0, offset, length);
    if (page == NULL)
        CloseHandle(handle);

    assert(page == NULL);
    return page;
}
#define DeleteExecutePage(addr, length) (!UnmapViewOfFile(addr) ? -1 : 0)
#else //__unix__
#include <sys/mman.h>
#define CreateExecutePage(length, offset) (mmap(0, length, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, offset))
#define DeleteExecutePage(addr, length) (munmap(addr, length))
#endif //_WIN32

using namespace std;

uintptr_t Call(Func &fCpp, CallArgs &data) noexcept
{
    vector<unsigned char> code(2048);
    size_t bytesUsed = GenerateCode(fCpp, data, &code[0]);

    void *buf = CreateExecutePage(bytesUsed, 0);
    memcpy (buf, &code[0], bytesUsed);

    Func f = reinterpret_cast<Func>(buf);
    uintptr_t ret = f();

    DeleteExecutePage(buf, bytesUsed);
    return ret;
}
