#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int m_capacity;
    int m_size;
    int *m_data;
} FIFO;

void push_fifo(FIFO* fifo, int value);
int pop_fifo(FIFO* fifo);
void print_fifo(FIFO* fifo);
void init_fifo(FIFO *fifo);
void deinit_fifo(FIFO *fifo);
int expand_fifo(FIFO *fifo);

int main()
{
    FIFO *example;
    example = malloc(sizeof(FIFO));
    init_fifo(example);
    
    push_fifo(example, 1);
    push_fifo(example, 2);
    push_fifo(example, 3);
    push_fifo(example, 4);
    push_fifo(example, 5);
    push_fifo(example, 6);
    print_fifo(example);

    pop_fifo(example);
    pop_fifo(example);
    pop_fifo(example);

    print_fifo(example);

    deinit_fifo(example);
    free(example);
    return 0;
}
   
void init_fifo(FIFO *fifo)
{   
    fifo->m_data = NULL;
    fifo->m_capacity = 0;
    fifo->m_size = 0;
}

void deinit_fifo(FIFO *fifo)
{
    // free is the same as delete in C++
    free(fifo->m_data); 
    fifo->m_capacity = 0;
    fifo->m_size = 0;
}

int expand_fifo(FIFO *fifo)
{
    int *temp = malloc((fifo->m_capacity * sizeof(int)) * 2 + sizeof(int));
    if (temp == NULL)
    {
        return 1;
    }

    fifo->m_capacity = fifo->m_capacity * 2 + 1;

    for (size_t i = 0; i < fifo->m_size; i++)
    {
        temp[i] = fifo->m_data[i];
    }
    
    free(fifo->m_data);
    
    fifo->m_data = temp;

    return 0;
}

void push_fifo(FIFO* fifo, int value)
{
    if (fifo->m_capacity < fifo->m_size + 1)
    {
        if (expand_fifo(fifo) == 1)
        {
            free(fifo->m_data);
        }
    }

    fifo->m_data[fifo->m_size++] = value;
}

int pop_fifo(FIFO* fifo)
{
    int result = fifo->m_data[0];
    for (int i = 1; i < fifo->m_size; i++)
    {
        fifo->m_data[i - 1] = fifo->m_data[i];
    }
    fifo->m_size--;

    return result;
}

void print_fifo(FIFO* fifo)
{
    printf("\n");
    for (int i = 0; i < fifo->m_size; i++)
    {
        printf("%d\t", fifo->m_data[i]);
    }
}
