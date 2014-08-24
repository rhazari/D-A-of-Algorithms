/*Implementation of the Knapsack problem on a larger data set*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int GCD(int x, int y)
{
    while( y > 0)
    {
        int temp = y;
        y = x%y;
        x = temp;
    }
    return x;
}

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
    
    /*for(int k = 1; k<=items; k++)
    {
        printf("%d\t %d\n",list[k][0], list[k][1]);
    }*/
    
    int gcd;
    gcd = GCD(list[1][1],list[2][1]);
    for(int k = 3; k<=items; k++)
    {
        gcd = GCD(list[k][1],gcd);
    }
    
    for(int k = 1; k<=items; k++)
    {
        list[k][1] = list[k][1]/gcd;
        //printf("%d\t %d\n",list[k][0],list[k][1]);
    }
    
    int cap = capacity/gcd;
    int min_wt = cap;
    int max_wt = 0;
    for(int k = 1; k<= items; k++)
    {
        if(min_wt > list[k][1])
        {
            min_wt = list[k][1];
        }
        if(max_wt < list[k][1])
        {
            max_wt = list[k][1];
        }            
    }  
    
    //The KnapSack...
    //int V[items+1][cap+1];
    int* V =  (int *)malloc((items+1)*(cap+1)*sizeof(int));
    
    //return 0;
    
    printf("Min-Weight: %d\n", min_wt);
    printf("Max-Weight: %d\n", max_wt);
    printf("Capacity: %d\n", cap);
    printf("GCD: %d\n", gcd);
    
    //return 0;
       
    //The KnapSack Algorithm...
    for(int w = 0; w<=cap; w++)
    {
        //V[0][w] = 0;
        *(V+w) = 0;
    }
    //return 0;
    #if 1
    int wi, vi;
    for(int i = 1; i<= items; i++)
    {
        vi = list[i][0];
        wi = list[i][1];
        for(int w = 0; w<= cap; w++)
        {
            //if(wi <= w && (vi+V[i-1][w-wi] > V[i-1][w])) 
            if(wi <= w && (vi+*(V+(i-1)*(cap+1)+(w-wi)) > *(V+(i-1)*(cap+1)+w))) 
            {
                //V[i][w] = vi + V[i-1][w-wi];
                *(V+i*(cap+1)+w) = vi + *(V+(i-1)*(cap+1)+(w-wi));
            }
            else
            {
                //V[i][w] = V[i-1][w];
                *(V+i*(cap+1)+w) = *(V+(i-1)*(cap+1)+w);
            }
        }
    }
    
    printf("The Knapsack Value: %d\n",*(V+items*(cap+1)+cap));
    
    
    return 0;
    #endif
} 
