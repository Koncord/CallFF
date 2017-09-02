#ifndef CALLFF_CALLARG_HPP
#define CALLFF_CALLARG_HPP

#include <vector>
#include <utility>
#include <cstdint>
#include <cstddef>

class CallArgs
{
public:
    typedef std::vector<std::pair<char, uintptr_t>> Type;
    typedef Type::iterator Iterator;
    typedef Type::const_iterator CIterator;

    inline void push_integer(uint64_t val) noexcept {
        if(sizeof(uintptr_t) < sizeof(uint64_t)) // if uint64_t is 8 and uintptr_t is 4
        {
            args.emplace_back('i', *reinterpret_cast<uintptr_t*>(&val));
            args.emplace_back('i', *reinterpret_cast<uintptr_t*>((uintptr_t) &val + 4));
        }
        else
            args.emplace_back('i', val);
    }
    inline void push_integer(int64_t val) noexcept {
        if(sizeof(uintptr_t) < sizeof(int64_t)) // if int64_t is 8 and uintptr_t is 4
        {
            args.emplace_back('i', *reinterpret_cast<uintptr_t*>(&val));
            args.emplace_back('i', *reinterpret_cast<uintptr_t*>((uintptr_t) &val + 4));
        }
        else
            args.emplace_back('i', static_cast<uintptr_t>(val));
    }
    inline void push_integer(uint64_t *val) noexcept {
        args.emplace_back('i', reinterpret_cast<uintptr_t>(val));
    }
    inline void push_integer(int64_t *val) noexcept {
        args.emplace_back('i', reinterpret_cast<uintptr_t>(val));
    }

    inline void push_integer(uint32_t val) noexcept {
        args.emplace_back('i', static_cast<uintptr_t>(val));
    }
    inline void push_integer(int32_t val) noexcept {
        args.emplace_back('i', static_cast<uintptr_t>(val));
    }
    inline void push_integer(uint32_t *val) noexcept {
        args.emplace_back('i', reinterpret_cast<uintptr_t>(val));
    }
    inline void push_integer(int32_t *val) noexcept {
        args.emplace_back('i', reinterpret_cast<uintptr_t>(val));
    }

    inline void push_stringPtr(char *ptr) noexcept {
        args.emplace_back('s', reinterpret_cast<uintptr_t>(ptr));
    }
    inline void push_stringPtr(const char *ptr) noexcept {
        args.emplace_back('s', reinterpret_cast<uintptr_t>(ptr));
    }

    inline void push_double(double val) noexcept {
        if(sizeof(uintptr_t) < sizeof(double)) // if double is 8 and uintptr_t is 4
        {
            args.emplace_back('f', *reinterpret_cast<uintptr_t*>(&val));
            args.emplace_back('f', *reinterpret_cast<uintptr_t*>((uintptr_t) &val + 4));
        }
        else
            args.emplace_back('f', *reinterpret_cast<uintptr_t*>(&val));
    }
    inline void push_double(double *ptr) noexcept {
        args.emplace_back('d', reinterpret_cast<uintptr_t>(ptr));
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
