/* Implementation of the median maintenace problem */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int num;
    struct node* next;
}
node;

node* first = NULL; 


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the text file for reading in the GRAPH!!!\n");
        return 2;
    }
    
    //Storing the filename
    char* infile = argv[1];
    //Open the input file
    FILE* file = fopen(infile,"r");
    if(file == NULL)
    {
        printf("Cannot open file. Exiting...\n");
        return 2;
    }    
    
    bool read = true;
    //To keep track of the number of integers inserted in the single link list
    int count = 0;
    int medianSum = 0;
    while(read)
    {
        node* ptr = malloc(sizeof(node));
        ptr->next = NULL;
        if(fscanf(file,"%d",&ptr->num)<1)
        {
            read = false;
            free(ptr);
            fclose(file);
            break;
        }
        
        //Insertion of integers in a single list
        //Integers in Sorted Order
        node* present = first;
        node* prev = NULL;
        
        if(first == NULL)
        {
            first = ptr;
            count++;
        }
        else
        {
            while(present != NULL && present->num < ptr->num)
            {
                prev = present;
                present = present->next;
            }
            //Insertion in the first node
            if(prev == NULL)
            {
                ptr->next = first;
                first = ptr;
                count++;
            }
            else
            {
                ptr->next = present;
                prev->next = ptr;
                count++;
            }
        }
        
        node* p1 = first;
        int index = (count+1)/2;
        for(int k = 1; k<index; k++)
        {
            p1 = p1->next;
        }
        medianSum = medianSum + p1->num;
        
    }
    medianSum = medianSum%10000;
    
    printf("Result:%d\n",medianSum);
    
    return 0;
}
