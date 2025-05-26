#include <stdio.h>
#include <limits.h>

unsigned getbits(unsigned x, int p, int n);
unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y);
unsigned int invert(unsigned int x, unsigned int p, unsigned int n);
unsigned char rightrot(unsigned char x, unsigned char n);

int main()
{
    /*
    Example:
        Start from pos 4(count right to left from zero)
        Take 3 bits from y and change x
        
        10010100 <= 148
           ---
        01011000 <= 88
           ===
        10011000 <= 152
    */
    printf("%d\n", setbits(148, 4, 3, 88));

    /*
    Example:
        Start from pos 4(count right to left from zero)
        Take 3 bits from x and ivert them

        10010100 <= 148
           ===
        10001000 <= 136
    */
    printf("%d\n", invert(148, 4, 3));

    /*
    Example:
        Rotate 3 bits

        10010100 <= 148
           ===
        10010010 <= 146
    */
    printf("%u\n", rightrot(148, 3));

    return 0;
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

unsigned int invert(unsigned int x, unsigned int p, unsigned int n)
{
    if (p + 1 < n)
    {
        return 0;
    }

    // (1 << n) - 1 or 2 ^ n - 1 always gives a num with n LSB bits set, then just moving it to right
    // place and use XOR for inverting
    return ((1 << n) - 1) << (p - n + 1) ^ x;
}


unsigned char rightrot(unsigned char x, unsigned char n)
/*
this function works with unsigned int too, just replace
all "char" types on int in this function
*/
{
    unsigned char temp = ((1 << n) - 1);
    temp &= x;
    temp <<= sizeof(unsigned char) * 8 - n;

    return temp | (x >> n);
}

