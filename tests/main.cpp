#include <cstdio>
#include <call.hpp>

using namespace std;


uint64_t fn(const char *str, int &b, int a0, int a1, int a2, int a3, double &c1,  int a4, int a5, double c2) noexcept
{
    printf(str, b, a1, c1, c2);
    b = 12345;
    return 123;
}

double f = 123.456;
double f2 = 23.23;

int i_val = 54321;

int main()
{
printf("%s\n", CALLFF_VERSION_STRING);
    Func fCpp = reinterpret_cast<Func>(&fn);
    CallArgs data;

    data.push_stringPtr("Hello World %d %d %f %f!\n");
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
    printf("%d\n", i_val);
    printf("return from func %ld\n", ret);
    return 0;
}