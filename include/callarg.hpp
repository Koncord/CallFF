#ifndef CALLFF_CALLARG_HPP
#define CALLFF_CALLARG_HPP

#include <vector>
#include <utility>
#include <cstdint>

class CallArgs
{
public:
    typedef std::vector<std::pair<char, uintptr_t>> Type;
    typedef Type::iterator Iterator;
    typedef Type::const_iterator CIterator;

    inline void push_integer(uint64_t val) noexcept {
        args.push_back(std::make_pair('i', val));
    }
    inline void push_integer(int64_t val) noexcept {
        args.push_back(std::make_pair('i', static_cast<uintptr_t>(val)));
    }
    inline void push_integer(uint64_t *val) noexcept {
        args.push_back(std::make_pair('i', reinterpret_cast<uintptr_t>(val)));
    }
    inline void push_integer(int64_t *val) noexcept {
        args.push_back(std::make_pair('i', reinterpret_cast<uintptr_t>(val)));
    }

    inline void push_integer(uint32_t val) noexcept {
        args.push_back(std::make_pair('i', static_cast<uintptr_t>(val)));
    }
    inline void push_integer(int32_t val) noexcept {
        args.push_back(std::make_pair('i', static_cast<uintptr_t>(val)));
    }
    inline void push_integer(uint32_t *val) noexcept {
        args.push_back(std::make_pair('i', reinterpret_cast<uintptr_t>(val)));
    }
    inline void push_integer(int32_t *val) noexcept {
        args.push_back(std::make_pair('i', reinterpret_cast<uintptr_t>(val)));
    }

    inline void push_stringPtr(char *ptr) noexcept {
        args.push_back(std::make_pair('s', reinterpret_cast<uintptr_t>(ptr)));
    }
    inline void push_stringPtr(const char *ptr) noexcept {
        args.push_back(std::make_pair('s', reinterpret_cast<uintptr_t>(ptr)));
    }

    inline void push_double(double val) noexcept {
        args.push_back(std::make_pair('f', *reinterpret_cast<uintptr_t*>(&val)));
    }
    inline void push_double(double *ptr) noexcept {
        args.push_back(std::make_pair('d', reinterpret_cast<uintptr_t>(ptr)));
    }

    inline CIterator begin() noexcept {
        return args.begin();
    }
    inline CIterator end() noexcept {
        return args.end();
    }
    inline size_t size() const noexcept {
        return args.size();
    }
    inline Type::reference operator[](size_t v) noexcept {
        return args[v];
    }

private:
    Type args;
};

#endif //CALLFF_CALLARG_HPP
