#include "linked_list.c"

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

int main()
{
    int **A = random_adj_matrix(6, -1);
    printAdjMat(A, 6);
    node **A_adjlst = adjMat_to_adjLst(A, 6);
    printAdjLst(A_adjlst, 6);
    int **A_Edglst = adjLst_to_edgLst(A_adjlst, 6);
    printEdgLst(A_Edglst, get_num_edges_from_AdjLst(A_adjlst, 6));
    int **A_dup = edgLst_to_adjMat(A_Edglst, get_num_edges_from_AdjLst(A_adjlst, 6));
    printAdjMat(A_dup, 6);
}