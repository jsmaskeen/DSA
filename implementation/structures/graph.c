#include "linked_list.c"
#include "stack.c"
#include "queue.c"

int **random_adj_matrix(int numvertex, int directed)
{
    int **adj_matrix = (int **)malloc(sizeof(int *) * numvertex);
    for (int i = 0; i < numvertex; i++)
    {
        adj_matrix[i] = (int *)malloc(sizeof(int) * numvertex);
    }
    time_t curtime;
    srand(time(&curtime));
    if (directed == 1)
    {
        for (int i = 0; i < numvertex; i++)
        {
            for (int j = 0; j < numvertex; j++)
            {
                if (rand() % 100 <= 30)
                {
                    adj_matrix[i][j] = 1;
                }
                else
                {
                    adj_matrix[i][j] = 0;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < numvertex; i++)
        {
            for (int j = i; j < numvertex; j++)
            {
                if (rand() % 100 <= 30)
                {
                    adj_matrix[i][j] = 1;
                    adj_matrix[j][i] = 1;
                }
                else
                {
                    adj_matrix[i][j] = 0;
                    adj_matrix[j][i] = 0;
                }
            }
        }
    }
    for (int i = 0; i < numvertex; i++)
    {
        adj_matrix[i][i] = 0;
    }
    for (int i = 0; i < numvertex; i++)
    {
        int su = arrsum(adj_matrix[i], numvertex);
        if (su == 0)
        {
            int dd = rand() % numvertex;
            adj_matrix[i][dd] = 1;
            if (directed != 1)
            {
                adj_matrix[dd][i] = 1;
            }
        }
    }

    return adj_matrix;
}

void printAdjMat(int **adjm, int numvertex)
{
    for (int i = 0; i < numvertex; i++)
    {
        for (int j = 0; j < numvertex; j++)
        {
            printf("%d ", adjm[i][j]);
        }
        printf("\n");
    }
}

node **adjMat_to_adjLst(int **adjm, int numvertex)
{
    node **adjacenylist = (node **)malloc(sizeof(node *) * numvertex);
    for (int i = 0; i < numvertex; i++)
    {
        adjacenylist[i] = NULL;
    }

    for (int i = 0; i < numvertex; i++)
    {
        for (int j = 0; j < numvertex; j++)
        {
            if (adjm[i][j] == 1)
            {
                insert_at_ith_position(adjacenylist + i, 0, j + 1);
            };
        }
    }
    return adjacenylist;
}
void printAdjLst(node **adjlist, int numvertex)
{
    for (int i = 0; i < numvertex; i++)
    {
        printf("Vertex: %d - ", i + 1);
        node *head = adjlist[i];
        while (head != NULL)
        {
            printf("%d, ", head->val);
            head = head->next;
        }
        printf("\n");
    }
}
int get_num_edges_from_AdjLst(node **adjlist, int numvertex)
{
    int numedges = 0;
    for (int i = 0; i < numvertex; i++)
    {
        numedges += get_length(adjlist[i]);
    }
    return numedges;
}

int **adjLst_to_edgLst(node **adjlist, int numvertex)
{
    int numedges = get_num_edges_from_AdjLst(adjlist, numvertex);
    int **edglst = (int **)malloc(sizeof(int *) * numedges);
    for (int i = 0; i < numedges; i++)
    {
        edglst[i] = (int *)malloc(sizeof(int) * 2);
    }
    int m = 0;
    for (int i = 0; i < numvertex; i++)
    {
        node *tmp = adjlist[i];
        while (tmp != NULL)
        {
            edglst[m][0] = i + 1;
            edglst[m][1] = tmp->val;
            tmp = tmp->next;
            m++;
        }
    }
    return edglst;
}

int **edgLst_to_adjMat(int **edglst, int numedges)
{
    int numvertex = 0;
    for (int i = 0; i < numedges; i++)
    {
        int tmp = edglst[i][0];
        if (edglst[i][1] > tmp)
        {
            tmp = edglst[i][1];
        }
        if (tmp > numvertex)
        {
            numvertex = tmp;
        }
    }
    int **adj_matrix = (int **)malloc(sizeof(int *) * numvertex);
    for (int i = 0; i < numvertex; i++)
    {
        adj_matrix[i] = (int *)malloc(sizeof(int) * numvertex);
    }
    for (int i = 0; i < numvertex; i++)
    {
        for (int j = 0; j < numvertex; j++)
        {
            adj_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < numedges; i++)
    {
        adj_matrix[edglst[i][0] - 1][edglst[i][1] - 1] = 1;
    }

    return adj_matrix;
}

void printEdgLst(int **elist, int numedges)
{
    for (int i = 0; i < numedges; i++)
    {
        printf("%d - %d\n", elist[i][0], elist[i][1]);
    }
}

int get_num_edges_from_AdjMat(int **adjm, int numvertex)
{
    int nume = 0;
    for (int i = 0; i < numvertex; i++)
    {
        for (int j = 0; j < numvertex; j++)
        {
            if (adjm[i][j] == 1)
                nume++;
        }
    }
    return nume;
}

typedef struct graph
{
    int nvertex;
    node **adjlist;
} graph;

graph *make_random_graph(int nvertex, int directed)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->nvertex = nvertex;
    int **A = random_adj_matrix(nvertex, directed);
    g->adjlist = adjMat_to_adjLst(A, nvertex);
    return g;
}

void dfs(graph *g, int startnode)
{
    int *visited = (int *)malloc(sizeof(int) * g->nvertex);

    for (int i = 0; i < g->nvertex; i++) visited[i] = 0;
    stack *s = makestack();
    printf("Pushed %d to stack\n", startnode);
    push(s, startnode);
    while (s->size > 0)
    {
        int v = pop(s);
        printf("Popped %d from stack\n", v);
        if (visited[v - 1] == 0)
        {
            visited[v - 1] = 1;
            printf("Visited vertex %d\n", v);
            node *h = g->adjlist[v - 1];
            while (h != NULL)
            {
                if (visited[h->val - 1] == 0)
                {
                    push(s, h->val);
                    printf("Pushed %d to stack\n", h->val);
                }
                h = h->next;
            }
        }
    }
}


void bfs(graph *g, int startnode)
{
    int *visited = (int *)malloc(sizeof(int) * g->nvertex);

    for (int i = 0; i < g->nvertex; i++) visited[i] = 0;

    queue *q = makequeue();
    printf("Enqueued %d to queue\n", startnode);
    enqueue(q, startnode);
    while (q->size > 0)
    {
        int v = dequeue(q);
        printf("Dequeued %d from queue\n", v);
        if (visited[v - 1] == 0)
        {
            visited[v - 1] = 1;
            printf("Visited vertex %d\n", v);
            node *h = g->adjlist[v - 1];
            while (h != NULL)
            {
                if (visited[h->val - 1] == 0)
                {
                    enqueue(q, h->val);
                    printf("Enqueued %d to queue\n", h->val);
                }
                h = h->next;
            }
        }
    }
}

int main()
{
    int nvtex = 6;
    graph *g = make_random_graph(nvtex, 1);
    printAdjLst(g->adjlist, nvtex);
    bfs(g, 1);
}