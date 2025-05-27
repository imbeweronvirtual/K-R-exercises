#include <stdio.h>
#include <limits.h>

unsigned int bitcount(unsigned long long x);

int main()
{
    printf("%u\n", bitcount(ULLONG_MAX)); // 64 must be received if llong has 64 bits set

    return 0;
}

unsigned int bitcount(unsigned long long x)
{
    unsigned int res = 0;

    while (x > 0)
    {
        x &= (x - 1);
        res++;
    }
    
    return res;
}