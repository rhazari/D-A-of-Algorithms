/*Implementation of Prim's Minimum Spanning Tree
Algorithm - Algorithm Part 2 Coursera*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3

typedef struct node
{
    int nbr;
    int cost;
    struct node* next;
}
node;

//Initializing Adjacency List
node* adjList[501];

//Insert into the Adjacency List
void insert(int x, int y, int z)
{
    node* ptr = malloc(sizeof(node));
    ptr->nbr = y;
    ptr->cost = z;
    
    if(adjList[x] == NULL)
    {
        adjList[x] = ptr;
    }
    else
    {
        node* p = adjList[x];
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next = ptr;
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the file with nodes and edge cost\n");
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
    
    //Reading the number of Nodes and Edges of the Graph from the input file
    int arr[SIZE];
    for(int k = 0; k<SIZE; k++)
    {
        fscanf(file,"%d",&arr[k]);
    }    
    
    //Initializing the Adjacency List pointers to NULL
    int Nodes = arr[0];
    for(int k = 1; k<=Nodes; k++)
    {
        adjList[k] = NULL;
    }
    
    //Reading the Nodes and the Edge Cost between them; Inserting them into the Adjacency List   
    bool read = true;
    int a, b, c;   
    while(read)
    {
        if(fscanf(file,"%d %d %d",&a,&b,&c) != 3)
        {
            read = false;
            fclose(file);
            break;
        }
        
        if(c != 0)
        {
            insert(a,b,c);
            insert(b,a,c);
        }
    }
    
    //Print out of the Adjacency List
    /*for(int k = 1; k<=Nodes; k++)
    {
        node* p1 = adjList[k];
        while(p1 != NULL)
        {
            printf("%d %d\t",p1->nbr,p1->cost);
            p1 = p1->next;
        }
        printf("\n");
    }*/
    
    //Log of the Nodes covered by Prim's MST Algorithm
    int visited[Nodes+1];
    for(int k = 1; k<=Nodes; k++)
    {
        visited[k] = 0;
    }
       
    //Prim's Minimum Spanning Tree
    int index = 1, visitor_count = 1, min_cost;;
    visited[index] = 1;
    long long int MST_sum = 0;
    
    while(visitor_count<Nodes)
    {
        min_cost = 10000000;
        for(int k = 1; k<= Nodes; k++)
        {
            if(visited[k] == 1)
            {
                node* ptr = adjList[k];
                while(ptr != NULL)
                {
                    if(ptr->cost < min_cost && visited[ptr->nbr] == 0)
                    {
                        min_cost = ptr->cost;
                        index = ptr->nbr;
                    }
                    ptr = ptr->next;
                }
            }
        }
        visited[index] = 1;
        MST_sum += min_cost;
        visitor_count += 1;
    }
      
    printf("The Prim's MST cost : %lld\n", MST_sum);

    return 0;
}
