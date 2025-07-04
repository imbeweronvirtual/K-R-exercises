/*
    LIFO would be usually count from top to bottom(last index to first index(zero))
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int m_size;
    unsigned int *m_array;
} Lifo_stack;

int lifo_stack_add(Lifo_stack *struct_p, unsigned int num);
int lifo_stack_delete(Lifo_stack *struct_p);
int lifo_stack_output(Lifo_stack *struct_p);
int uiarr_expand_compress(unsigned int **ptr, int compress_need, unsigned int *current_size);

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

    free(example.m_array);
    return 0;
}

int lifo_stack_add(Lifo_stack *struct_p, unsigned int num)
{
    if (uiarr_expand_compress(&struct_p->m_array, 0, &struct_p->m_size) == 1)
    {
        free(struct_p->m_array);
    }

    for (int i = (struct_p->m_size) - 2; i >= 0; i--)
    {
        struct_p->m_array[i + 1] = struct_p->m_array[i];
    }
    struct_p->m_array[0] = num;

    return 0;
}

int lifo_stack_delete(Lifo_stack *struct_p)
{
    if (struct_p->m_size == 0)
    {
        return 1;
    }

    for (size_t i = 0; i < struct_p->m_size - 1; i++)
    {
        struct_p->m_array[i] = struct_p->m_array[i + 1];
    }

    if (uiarr_expand_compress(&struct_p->m_array, 1, &struct_p->m_size) == 1)
    {
        free(struct_p->m_array);
    }
    
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

int uiarr_expand_compress(unsigned int **ptr, int compress_need, unsigned int *current_size)
{
    int new_size = compress_need ? *current_size - 1 : *current_size + 1;

    if (compress_need)
    {
        if (*current_size == 1)
        {
            free(*ptr);
        }
        if (*current_size < 1)
        {
            return 1;
        }
        
        unsigned int *temp = malloc(new_size * sizeof(unsigned int));

        if (temp == NULL)
        {
            return 1;
        }

        memcpy(temp, *ptr, new_size * sizeof(unsigned int));

        free(*ptr);

        *ptr = temp;
        *current_size = new_size;

        return 0;
    }
    else
    {
        unsigned int *temp = malloc(new_size * sizeof(unsigned int));
    
        if (temp == NULL)
        {
            return 1;
        }
    
        memcpy(temp, *ptr, *current_size * sizeof(unsigned int));
    
        if (*current_size > 0)
        {
            free(*ptr);
        }
        
        *ptr = temp;
        *current_size = new_size;
    
        return 0;
    }   
}
