#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NODES 501
#define EDGES 125001

typedef struct node
{
    int data, rank;
    struct node *next, *parent;
}
node;

typedef struct edge
{
    int len;
    struct node *src, *dest;
}
edge;

node* head[NODES];
edge* e[EDGES];

void makeset(int a)
{
    node* x = malloc(sizeof(node));
    x->data = a;
    x->parent = x;
    x->rank = 0;
    x->next = NULL;
    head[a] = x;
}

struct node* findset(struct node* a)
{
    if(a != a->parent)
    {
        a->parent = findset(a->parent);
    }
    return a->parent;
}

void union1(struct node* x, struct node* y)
{
    if(x->rank > y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
        if(x->rank == y->rank)
            y->rank = y->rank+1;
    }
}


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the text file with node points & their distances\n");
        return 2;
    }
    
    //Storing the file name
    char* infile = argv[1];
    
    //Open the input file
    FILE* file = fopen(infile,"r");
    if (file == NULL)
    {
        printf("Cannot open file. Exiting...\n");
        return 2;
    }
    
    //Number of Nodes in the Graph
    int num_Nodes;
    fscanf(file,"%d",&num_Nodes);
    
    for(int k = 1; k<= num_Nodes; k++)
    {
        makeset(k);
    }
    
    //Reading the Nodes and the Edge Cost between them; Inserting them into the Adjacency List   
    bool read = true;
    int a, b, c, index = 0;   
    while(read)
    {
        if(fscanf(file,"%d %d %d",&a,&b,&c) != 3)
        {
            read = false;
            fclose(file);
            break;
        }
        
        index++;
        edge* ptr = malloc(sizeof(edge));        
        ptr->src = head[a];
        ptr->dest = head[b];
        ptr->len = c;
        
        e[index] = ptr;
    }
    
    //Insertion Sort of the Edge Costs
    int i, l, p;
    struct edge* temp;
    i = 1;
    while(i < index)
    {
        p = i;
        l = i+1;
        while(l <= index)
        {
            if(e[p]->len > e[l]->len)
            {
                p = l;
            }
            l++;
        }
        if(p != i)
        {
            temp = e[p];
            e[p] = e[i];
            e[i] = temp;
        }
        i++;
    }
    
    
    /*for(int k = 1; k<= index; k++)
    {
        printf("Edge Cost: %d\n",e[k]->len);
    }*/
    
    //Union-Find Operation on the Edges
    //long long int MST_cost = 0;
    
    //Target number of clusters set to 4
    int cluster_count = num_Nodes;  
    for(i=1;i<=index;i++)  
    {  
        if(findset(e[i]->src)!=findset(e[i]->dest) && cluster_count != 4)  
        {                           
            //if src & dest. are different then combing them into the same cluster  
            union1((findset(e[i]->src)),(findset(e[i]->dest)));
            cluster_count--;
            //MST_cost += e[i]->len;                  
            //printf("\n%d->%d",e[i]->src->data,e[i]->dest->data);   
        }
        else if(findset(e[i]->src)!=findset(e[i]->dest) && cluster_count == 4)
        {
            printf("Max Spacing between the clusters: %d\n", e[i]->len);
            break;
        }  
    }
    
    //printf("The Kruskal MST cost: %lld\n", MST_cost); 
    return 0;
}
