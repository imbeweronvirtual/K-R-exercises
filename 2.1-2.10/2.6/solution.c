#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);
unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y);

int main()
{
    /*
    Example:
        Start from pos 4(count right to left from zero)
        Take 3 bits from y and change x
        
        10010100 <= 148
           ---
        01011000 <= 88
           ---
        10011000 <= 152
    */
    printf("%d", setbits(148, 4, 3, 88));
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}


unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y) 
{
    if (p + 1 < n)
    {
        return 0;
    }
    
    for (size_t i = 0; i < n; i++)
    {
        if (y & (1 << p))
        {
            x |= (1 << p);
        }
        else
        {
            x &= ~(1 << p); 
        }
        
        p--;
    }
    
    return x;
}