#include <iostream>
using namespace std;
constexpr int size = 512 << 20; // 256MB
char p[size];
void hello(int x)
{
    int p;
    cout << x << endl;
    hello(x + 1);
}
int main()
{
    __asm__("MOV %0, %%RSP\n" :: "r"(p + size));
    hello(0);
    return 0;
}