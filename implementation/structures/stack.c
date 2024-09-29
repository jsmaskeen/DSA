#include "header.h"

typedef struct stacknode
{
    int val;
    struct stacknode *next;

} stacknode;

typedef struct stack
{
    stacknode *top;
    int size;
} stack;

void push(stack *s, int val)
{
    stacknode *tmp = (stacknode *)malloc(sizeof(stacknode));
    tmp->val = val;
    if (s->top == NULL)
    {
        tmp->next = NULL;
    }
    else
    {
        tmp->next = s->top;
    }
    s->top = tmp;
    s->size++;
}

void printStack(stack *s)
{
    stacknode *tmp = s->top;
    while (tmp != NULL)
    {
        printf("%d|", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}

int pop(stack *s)
{
    if (s->top == NULL)
    {
        return -1;
    }
    stacknode *tmp = s->top;
    s->top = s->top->next;
    int v = tmp->val;
    free(tmp);
    return v;
}

int peek(stack *s)
{
    if (s->top == NULL)
    {
        return -1;
    }
    return s->top->val;
}

stack *makestack()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

stack *arr_to_stack(int arr[], int len)
{
    stack *s = makestack();
    for (int i = 0; i < len; i++)
    {
        push(s, arr[len - i - 1]);
    }
    return s;
}

stack *random_stack(int len)
{
    int *arr = get_random_array(len);
    return arr_to_stack(arr,len);
}