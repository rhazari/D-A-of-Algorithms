/*Implementation of the two sum algorithm */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUCKETSIZE 10007
#define SIZE 1501

typedef struct node
{
    int num;
    struct node* next;
}
node;
node* HashTable[BUCKETSIZE];
node* table[SIZE];


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
    FILE* scanFile = fopen(infile,"r");
    if(file == NULL)
    {
        printf("Cannot open file. Exiting...\n");
        return 2;
    }
    
    //Initializing the HashTables
    for(int k = 0; k<BUCKETSIZE; k++)
    {
        HashTable[k] = NULL;
    }
    
    for(int k = 0; k<SIZE; k++)
    {
        table[k] = NULL;
    }
    
    //Entering the data into the Hash Table
    //Loading the Hash Table
    bool read = true;
    int hashValue;
    while(read)
    {
        node* ptr =  malloc(sizeof(node));
        if (ptr == NULL)
        {
            read = false;
            break;
        }
        
        ptr->next = NULL;
        if (fscanf(file,"%d",&ptr->num)<1)
        {
            read = false;
            free(ptr);
            fclose(file);
            break;
        }
        
        //Knuth Variant on Division
        //The Hash Function
        int val = ptr->num;
        hashValue = (val%BUCKETSIZE)*((val+3)%BUCKETSIZE)%BUCKETSIZE;
        
        //Entering a number to the HashTable
        if(HashTable[hashValue] == NULL)
        {
            HashTable[hashValue] = ptr;
        }
        else
        {
            node* p1 = HashTable[hashValue];
            while(p1->next != NULL)
            {
                p1 = p1->next;
            }
            p1->next = ptr;   
        }         
    }
    
    int x;
    int y, index = 0;
    read = true;
    while(read)
    {
        if(fscanf(scanFile,"%d",&x)<1)
        {
            read = false;
            break;
        }
        
        for(int t = 2500; t<=4000; t++)
        {
            y = t-x;
            if(y > 0 && y != x)
            {
                hashValue = y*(y+3)%BUCKETSIZE;
                node* p1 = HashTable[hashValue];
                while(p1 != NULL)
                {
                    if(p1->num == y)
                    {
                        hashValue = t%SIZE;
                        if(table[hashValue] == NULL)
                        {
                            node* p2 = malloc(sizeof(node));
                            p2->num = t;
                            p2->next = NULL;
                            table[hashValue] = p2;
                            index++;
                        }
                        break;
                    }
                    else
                        p1 = p1->next;
                }
            }
        }
        
    }
    
    printf("Count:%d\n",index);
    
    
    
    return 0;
}
