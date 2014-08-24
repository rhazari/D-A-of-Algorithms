#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    
    int capacity, items;
    fscanf(file,"%d %d",&capacity,&items);
    
    int list[items+1][2];
    bool read = true;
    int value, weight, index = 1;
    while(read)
    {
        if(fscanf(file,"%d %d",&value, &weight)!= 2)
        {
            read = false;
            fclose(file);
            break;
        }
        
        list[index][0] = value;
        list[index][1] = weight;
        index++;
    }
    
    for(int k = 1; k<=items; k++)
    {
        printf("%d\t %d\n",list[k][0], list[k][1]);
    }
       
    //The KnapSack..
    int V[items+1][capacity+1];
    
    //The KnapSack Algorithm...
    for(int k = 0; k<=capacity; k++)
    {
        V[0][k] = 0;
    }
    
    int wi, vi;
    for(int i = 1; i<= items; i++)
    {
        vi = list[i][0];
        wi = list[i][1];
        for(int w = 0; w<= capacity; w++)
        {
            if(wi <= w && (vi+V[i-1][w-wi] > V[i-1][w])) 
            {
                V[i][w] = vi + V[i-1][w-wi];
            }
            else
            {
                V[i][w] = V[i-1][w];
            }
        }
    }
    
    printf("The Knapsack Value: %d\n",V[items][capacity]);
    return 0;
}

