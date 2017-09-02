#include <cstdio>
#include <call.hpp>
#include <cassert>
#include <cstring>

using namespace std;


uintptr_t fn(const char *str, int &b, int a0, int a1, int a2, int a3, double &c1,  int a4, int a5, double c2) noexcept
{
    auto newStr = new char[1024];
    sprintf(newStr, str, b, a1, c1, c2);
    b = 10000;
    double c3 = c1;
    c1 = 0.654;
    b = b+a0+a1+a2+a3+a4+a5+c3+c2+c1;
    return reinterpret_cast<uintptr_t>(newStr);
}

double f = 123.456;
double f2 = 23.23;

int i_val = 54321;

int main()
{
    auto fCpp = reinterpret_cast<Func>(&fn);
    CallArgs data;

    data.push_stringPtr("Hello World %d %d %.3f %.3f!");
    data.push_integer(&i_val);
    data.push_integer(0);
    data.push_integer(1);
    data.push_integer(2);
    data.push_integer(3);
    data.push_double(&f);
    data.push_integer(4);
    data.push_integer(5);
    data.push_double(f2);

    uintptr_t ret = Call(fCpp, data);

    assert(strcmp(reinterpret_cast<char*>(ret), "Hello World 54321 1 123.456 23.230!") == 0);
    assert(f == 0.654);
    assert(i_val == 10162); // b+a0+a1+a2+a3+a4+a5+c3+c2+c1
    delete reinterpret_cast<char*>(ret);

    return 0;
}