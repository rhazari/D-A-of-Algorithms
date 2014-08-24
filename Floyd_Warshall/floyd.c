/*Implementation of the Floyd-Warshall Algorithm
Computing the All Pair Shortest Path & finding the minimum of all the shortest Path.
All making the check for the existence of negative cycles.
Running time O(n^3); Space O(n^2)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INFINITY 10000

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the filename to read the items; their weights and values\n");
        return 2;
    }
    
    char* infile = argv[1];
    
    //Open the input file
    FILE* file = fopen(infile,"r");
    if(file == NULL)
    {
        printf("Cannot open file. Exiting...\n");
        return 2;
    }
    
    
    int nodes, edges;
    fscanf(file,"%d %d",&nodes,&edges);
    
    //Initializing the adjacency List to NULL
    int* adjMatrix = (int *)malloc((nodes+1)*(nodes+1)*sizeof(int));
    for(int i = 1; i<= nodes; i++)
    {
        for(int j = 1; j <= nodes; j++)
        {
            if(i != j)
            {
                //adjMatrix[i][j] = INFINITY;
                *(adjMatrix + i*(nodes)+j) = INFINITY;
            }
            else
            {
                *(adjMatrix + i*(nodes)+j) = 0;
            }
        }
    }
    
    bool read = true;
    int tail, head, length;
    while(read)
    {
        if(fscanf(file,"%d %d %d",&tail, &head, &length) != 3)
        {
            read = false;
            fclose(file);
            break;
        }        
        //adjMatrix[tail][head] = length;
        *(adjMatrix + tail*(nodes)+ head) = length;
    }
    
    //Print out of the Adjacency Matrix
    /*for(int i = 1; i <= nodes; i++)
    {
        for(int j = 1; j <=nodes; j++)
        {
            printf("%d\t",*(adjMatrix+ i*(nodes)+j));
        }
        printf("\n");
    }*/
    
    //Floyd-Warshall Algorithm...
    //2-D Array containing the shortest path from every i-j nodes
    //Initializing the D-array with the immediate edges...
    int* D = (int*)malloc((nodes+1)*(nodes+1)*sizeof(int));
    
    //Initializing the prev array for extracting the path from nodes i-j
    int* prev = (int*)malloc((nodes+1)*(nodes+1)*sizeof(int));
    
    for(int i = 1; i <= nodes; i++)
    {
        for(int j = 1; j <= nodes; j++)
        {
            *(D+ i*(nodes)+j) = *(adjMatrix+ i*(nodes)+j);
            *(prev+ i*(nodes)+j) = -1;
        }
    }
    
    //Including the nodes numbered (1...k) 
    for(int k = 1; k <= nodes; k++)
    {
        for(int i = 1; i <= nodes; i++)
        {
            for(int j = 1; j <= nodes; j++)
            {
                if( *(D+i*(nodes)+k) + *(D+k*(nodes)+j) < *(D+i*(nodes)+j) )
                {
                    *(D+i*(nodes)+j) = *(D+i*(nodes)+k) + *(D+k*(nodes)+j);
                    *(prev+i*(nodes)+j) = k;
                }
            }
        }
    }
    
    //The D-Matrix
    //The shortest minimum distance between any nodes i-j
    int min_dist = INFINITY;
    for(int i = 1; i<= nodes; i++)
    {
        for(int j = 1; j<= nodes; j++)
        {
            //printf("%d\t",D[i][j]);
            if(min_dist > *(D + i*(nodes)+j))
            {
                min_dist = *(D + i*(nodes)+j);
            }
            if((i == j) && *(D + i*(nodes)+j) < 0)
            {
                printf("\n");
                printf("Negative cycle exist\n");
                return 2;
            }
        }
        //printf("\n");
    }
    
    printf("\n");
    printf("Min-dist: %d\n",min_dist);
    
    return 0;
}
