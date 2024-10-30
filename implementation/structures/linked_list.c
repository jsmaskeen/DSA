# ifndef HEADERFILE
# define HEADERFILE
#include "header.h"
# endif

typedef struct node
{
    int val;
    struct node *next;
} node;

void printLL(node *head)
{
    while (head != NULL)
    {
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

node *getnode(int val)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->next = NULL;
    tmp->val = val;
    return tmp;
}

int get_length(node *head)
{
    int len = 0;
    while (head != NULL)
    {
        len++;
        head = head->next;
    }
    return len;
}

void insert_at_ith_position(node **poi_2_head, int posiiton, int val)
{
    // 0 indexed position
    node *tmp = getnode(val);
    int len = get_length(*poi_2_head);
    if (posiiton > len)
    {
        return;
    }
    if (*poi_2_head == NULL)
    {
        *poi_2_head = tmp;
        return;
    }
    if (posiiton == 0)
    {
        tmp->next = *poi_2_head;
        *poi_2_head = tmp;
        return;
    }
    if (posiiton == -1)
    {
        insert_at_ith_position(poi_2_head, len, val);
        return;
    }
    node *headcp = *poi_2_head;
    int i = 0;
    while (i < posiiton - 1)
    {
        headcp = headcp->next;
        i++;
    }
    tmp->next = headcp->next;
    headcp->next = tmp;
    return;
}

node *create_ll(int a[],int len)
{
    if (len == 0){
        return NULL;
    }
    node* LL = getnode(a[0]);
    node* copy = LL;
    for (int i = 1; i < len; i++)
    {
        // insert_at_ith_position(&LL,-1,a[i]);
        copy->next = getnode(a[i]);
        copy = copy->next;
    }
    return LL;
}

node* random_linked_list(int len){
    int*arr = get_random_array(len);
    return create_ll(arr,len);
}