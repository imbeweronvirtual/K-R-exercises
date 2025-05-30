#include <stdio.h>
#include <stdlib.h>

int binsearch(int x, int v[], int n);

int main()
{
    unsigned int *big_array = malloc(100000000 * sizeof(int)); // test big array to see the difference

    if (big_array == NULL)
    {
        return 1;
    }
    
    for (size_t i = 0; i < 100000000; i++)
    {
        big_array[i] = i + 1;
    }
    
    printf("%d", binsearch(356781, big_array, 1000000));

    free(big_array);
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    mid = 0;
    high = n - 1 ;

    while (low <= high && x != v[mid])
    {
        mid = (low + high) / 2;
        
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return x == v[mid] ? mid : -1; 
}