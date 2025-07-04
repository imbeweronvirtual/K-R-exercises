#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// List
typedef struct ListNode_S
{
    int m_value;
    struct ListNode_S *p_next;
} ListNode;

ListNode* struct_init(int value);
void struct_deinit(ListNode **ptr);
void list_deinit(ListNode **head_ptr);
void add_last(ListNode *head_ptr, ListNode *node_to_add);
void add_by_index(ListNode *head_ptr, ListNode *node_to_add, unsigned int index);
void remove_last(ListNode **head_ptr);
void remove_by_index(ListNode **head_ptr, unsigned int index);
void print(ListNode *head_ptr);




int main()
{   
    ListNode  *list = struct_init(0);
    // list_deinit(&list);
    ListNode  *node1 = struct_init(1);
    ListNode  *node2 = struct_init(2);
    ListNode  *node3 = struct_init(3);
    ListNode  *node4 = struct_init(4);
    ListNode  *node5 = struct_init(5);
    ListNode  *node6 = struct_init(6);

    add_last(list, node1);
    add_last(list, node2);
    add_last(list, node3);
    add_last(list, node4);
    add_last(list, node5);
    add_last(list, node6);

    // 0 1 2 3 4 5 6
    print(list);

    ListNode *node7 = struct_init(7);

    // 0 1 7 2 3 4 5 6
    add_by_index(list, node7, 2);
    // 0 1 7 2 3 4 5
    remove_last(&list);
    printf("==============\n");
    // 0 1 2 3 4 5
    remove_by_index(&list, 2);
    print(list);

    // NULL
    list_deinit(&list);
    printf("ACHTUNG BELOW - last check\n");
    print(list); // expected nothing to be printed

    return 0;
}

ListNode *struct_init(int value)
{
    ListNode *res = malloc(sizeof(ListNode));
    if (res == NULL)
    {
        printf("malloc fail");
        return res;
    }
    
    res->m_value = value;
    res->p_next = NULL;
    return res;
}

void struct_deinit(ListNode **ptr) 
{
    free(*ptr);
    *ptr = NULL;

    return;
}

void list_deinit(ListNode **head_ptr)
{  
   while ((*head_ptr) != NULL)
   {
        remove_last(head_ptr);
   }

   return;
}

void add_last(ListNode *head_ptr, ListNode *node_to_add)
{
    ListNode *current = head_ptr;

    if(current == NULL)
    {
        printf("add_by_index - empty list\n");
        return;
    }

    while (current->p_next != NULL)
    {
        current = current->p_next;
    }
    
    current->p_next = node_to_add;

    return;
}

void add_by_index(ListNode *head_ptr, ListNode *node_to_add, unsigned int index)
{
    ListNode *current = head_ptr;

    if(current == NULL)
    {
        printf("add_by_index - empty list\n");
        return;
    }

    for(size_t i = 0; i < index - 1; i++)
    {
        current = current->p_next;
        if(current == NULL)
        {
            printf("add_by_index - wrong index %d\n", index);
            return;
        }
    }
    node_to_add->p_next = current->p_next;
    current->p_next = node_to_add;
}

void remove_last(ListNode **head_ptr)
{
    ListNode *current = *head_ptr;
    ListNode *last;

    if (head_ptr == NULL || *head_ptr == NULL)
    {
        return;
    }

    if ((*head_ptr)->p_next == NULL)
    {
        struct_deinit(head_ptr);
        return;
    }

    while (current->p_next->p_next != NULL)
    {
        current = current->p_next;
    }

    ListNode *to_delete = current->p_next;
    current->p_next = NULL;
    struct_deinit(&to_delete);

    return;
}

void remove_by_index(ListNode **head_ptr, unsigned int index)
{
    ListNode *current = *head_ptr;
    ListNode *last;

    if (index == 0 && *head_ptr != NULL)
    {
        list_deinit(head_ptr);
    }

    for(size_t i = 0; i < index; i++)
    {
        if(current == NULL)
        {
            printf("remove_by_index - wrong index %d\n", index);
            return;
        }
        
        last = current;
        current = current->p_next;
    }

    last->p_next = current->p_next;
    struct_deinit(&current);

    return;
}

void print(ListNode *head_ptr)
{
    ListNode *current = head_ptr;

    if(current == NULL)
    {
        return;
    }

    while(current->p_next != NULL)
    {
        printf("%d\n", current->m_value);
        current = current->p_next;
    }

    printf("%d\n", current->m_value);
}