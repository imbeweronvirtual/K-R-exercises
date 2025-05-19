#include <limits.h>
#include <float.h>
#include <stdio.h>

unsigned long long count_max(unsigned int bits_amount);

int main()
{
   printf("The value of UCHAR_MAX: %u\n", UCHAR_MAX);
   printf("The value of CHAR_MAX: %d\n", CHAR_MAX);
   printf("The value of SHRT_MAX: %d\n", SHRT_MAX);
   printf("The value of USHRT_MAX: %u\n", USHRT_MAX);
   printf("The value of INT_MAX: %d\n", INT_MAX);
   printf("The value of UINT_MAX: %u\n", UINT_MAX);
   printf("The value of LONG_MAX: %ld\n", LONG_MAX);
   printf("The value of ULONG_MAX: %lu\n", ULONG_MAX);

   for (unsigned int i = 8; i <= 64; i *= 2)
   {
        printf("In %d unsigned bits %llu is the biggest number, if signed: %llu\n", i, count_max(i), count_max(i)/2);
   }
   
   return 0;
}

unsigned long long count_max(unsigned int bits_amount)
{
   bits_amount = bits_amount ? bits_amount : 1;
   unsigned long long return_max = 1;
   for (size_t i = 0; i < bits_amount; i++)
        return_max *= 2;
   
   return return_max - 1;
}