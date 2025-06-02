/*
    LIFO would be usually count from top to bottom(last index to first index(zero))
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int m_size;
    unsigned int m_array[1000];
} Lifo_stack;

int lifo_stack_add(Lifo_stack *struct_p, unsigned int num);
int lifo_stack_delete(Lifo_stack *struct_p);
int lifo_stack_output(Lifo_stack *struct_p);

int main()
{
    // create and initialize struct
    Lifo_stack example;
    example.m_size = 0;

    lifo_stack_add(&example, 1);
    lifo_stack_add(&example, 2);
    lifo_stack_add(&example, 3);
    lifo_stack_add(&example, 4);
    lifo_stack_add(&example, 5);
    lifo_stack_add(&example, 6);

    lifo_stack_output(&example);

    lifo_stack_delete(&example);
    lifo_stack_delete(&example);
    lifo_stack_delete(&example);

    lifo_stack_output(&example);

    lifo_stack_add(&example, 7);   
    lifo_stack_add(&example, 8);   
    lifo_stack_add(&example, 9);   

    lifo_stack_output(&example);

    return 0;
}

int lifo_stack_add(Lifo_stack *struct_p, unsigned int num)
{
    if ((struct_p->m_size) + 1 > sizeof(struct_p->m_array) / sizeof(unsigned int))
    {
        return 1;
    }
    
    for (int i = (struct_p->m_size) - 1; i >= 0; i--)
    {
        struct_p->m_array[i + 1] = struct_p->m_array[i];
    }
    struct_p->m_array[0] = num;
    struct_p->m_size++;

    return 0;
}

int lifo_stack_delete(Lifo_stack *struct_p)
{
    if (struct_p->m_size == 0)
    {
        return 1;
    }

    for (size_t i = 0; i < struct_p->m_size; i++)
    {
        struct_p->m_array[i] = struct_p->m_array[i + 1];
    }
    struct_p->m_size--;
    
    return 0;
}

int lifo_stack_output(Lifo_stack *struct_p)
{
    for (size_t i = 0; i < struct_p->m_size; i++)
    {
        printf("%u\t", struct_p->m_array[i]);
    }
    printf("\n");
    
    return 0;
}

