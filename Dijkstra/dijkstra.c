#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 200

typedef struct node
{
    int id;
    int cost;
    int min_dist;
    bool visited;
    struct node* next;
}
node;

node* adjList[SIZE+1];

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the text file to read the Graph!!!\n");
        return 2;
    }
    
    //Storing the fileName
    char* infile = argv[1];
    //Open the output file
    FILE* file = fopen(infile,"r");
    if(file == NULL)
    {
        printf("Cannot open file. Exiting...\n");
        return 2;
    }
    
    //Initializing Adjacency List to NULL
    for(int k = 1; k<=SIZE; k++)
    {
        adjList[k] = NULL;
    }
    
    //Forming the Adjacency List
    bool read = true;
    int index = 1;
    int a,b;
    while(read)
    {
        if(fscanf(file,"%d,%d",&a,&b)<2)
        {
            read = false;
            fclose(file);
            break;
        }
        
        node* ptr = malloc(sizeof(node));
        ptr->id = a;
        ptr->cost = b;
        ptr->next = NULL;
        
        if(ptr->id == SIZE+1)
        {
            index++;
        }
        else if(adjList[index] == NULL)
        {
            adjList[index] = ptr;
            adjList[index]->visited = false;
            adjList[index]->min_dist = 1000000;         
        }
        else
        {
            node* p = adjList[index];
            while(p->next != NULL)
            {
                p = p->next;
            }
            p->next = ptr;
        }    
    }
    
    /*for(int k = 1; k<=SIZE; k++)
    {
        node* p1 = adjList[k];
        while(p1 != NULL)
        {
            printf("%d %d\t",p1->id,p1->cost);
            p1 = p1->next;
        }
        printf("\n");
    }*/
    
    int source = 1;
    adjList[source]->visited = true;
    adjList[source]->min_dist = 0;
    int num = 1;
    int array[SIZE];
    array[0] = source;
    
    while(num != SIZE)
    {
        int ptr,dist,ID;
        dist = 1000000;
        for(int k = 0; k<num; k++)
        {
            ptr = array[k];
            node* p1 = adjList[ptr];
            while(p1->next != NULL)
            {
                p1 = p1->next;
                ID = p1->id;
                if(adjList[ID]->visited == false && (adjList[ptr]->min_dist + p1->cost)< dist)
                {
                    dist = adjList[ptr]->min_dist + p1->cost;
                    index = ID;
                }
            }
        }
        array[num] = index;
        adjList[index]->visited = true;
        adjList[index]->min_dist = dist;
        num++;
    }
    
    // Printing out the shortest distances to the following 10 vertices
    // 7,37,59,82,99,115,133,165,188,197
    printf("%d\n", adjList[7]->min_dist);
    printf("%d\n", adjList[37]->min_dist);
    printf("%d\n", adjList[59]->min_dist);
    printf("%d\n", adjList[82]->min_dist);
    printf("%d\n", adjList[99]->min_dist);
    printf("%d\n", adjList[115]->min_dist);
    printf("%d\n", adjList[133]->min_dist);
    printf("%d\n", adjList[165]->min_dist);
    printf("%d\n", adjList[188]->min_dist);
    printf("%d\n", adjList[197]->min_dist);
    return 0;
}
