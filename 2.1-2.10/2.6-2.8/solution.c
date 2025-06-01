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


/*
this function works with unsigned int too, just replace
all "char" types on int in this function
For example:
    1. We take x as 148 bitwise 10010100
    2. We take n as 3
    3. We create temp variable that has n(3) LSB bits set as 1
    4. We copy n(3) LSB bits from x(148) to temp
    5. We shift these bits to MSB
*/
unsigned char rightrot(unsigned char x, unsigned char n)
{
    unsigned char temp = ((1 << n) - 1);  // 00000111
    temp &= x; // 00000100
    temp <<= sizeof(unsigned char) * 8 - n; // 10000000

    /*
    temp = 128(10000000 bitwise)
    x = 148(10010100 bitwise)
    x >> n(3) = 18(00010010)
    128 | 18 = 10000000 | 00010010 = 10010010
    */
    return temp | (x >> n);
}

