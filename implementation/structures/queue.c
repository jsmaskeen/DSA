# ifndef HEADERFILE
# define HEADERFILE
#include "header.h"
# endif
typedef struct queuenode
{
    int val;
    struct queuenode *next;

} queuenode;

typedef struct queue
{
    queuenode *head;
    queuenode *tail;
    int size;
} queue;

void enqueue(queue *q, int val)
{
    queuenode *tmp = (queuenode *)malloc(sizeof(queuenode));
    tmp->val = val;
    tmp->next = NULL;
    
    if (q->head == NULL && q->tail == NULL){
        q->head = tmp;
        q->tail = tmp;
    }
    else {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->size++;
}

void printqueue(queue *q)
{
    queuenode *tmp = q->head;
    while (tmp != NULL)
    {
        printf("%d|", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}

int dequeue(queue *q)
{
    if (q->head == NULL && q->tail == NULL){
        return -1;
    }
    
    queuenode *tmp = q->head;
    q->head = q->head->next;
    if (q->head == NULL){
        q->tail = NULL;
    }
    int v = tmp->val;
    q->size--;
    free(tmp);
    return v;
}

int peek(queue *q)
{
    if (q->head == NULL)
    {
        return -1;
    }
    return q->head->val;
}

queue *makequeue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}



queue *arr_to_queue(int arr[], int len)
{
    queue *q = makequeue();
    for (int i = 0; i < len; i++)
    {
        enqueue(q, arr[len - i - 1]);
    }
    return q;
}

queue *random_queue(int len)
{
    int *arr = get_random_array(len);
    return arr_to_queue(arr,len);
}


