#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

unsigned long int count = 0;

void merge(int* , int* , int, int, int);
void merge_sort(int arr[], int* temp, int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = (low+high)/2;
        merge_sort(arr, temp, low, pivot);
        merge_sort(arr, temp, pivot+1, high);
        merge(arr, temp,low,pivot,high);
    }
}

void merge(int arr[], int* b, int low, int pivot, int high)
{
    int h, i, j, k;
    h = low;
    i = low;
    j = pivot+1;
    
    while((h<=pivot)&&(j<=high))
    {
        if(arr[h]<=arr[j])
        {
            b[i]=arr[h];
            h++;
        }
        else
        {
            b[i]=arr[j];
            j++;
            count += pivot+1 - h; 
        }
        i++;
    }
    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            b[i]=arr[k];
            i++;
        }
    }
    else
    {
        for(k=h; k<=pivot; k++)
        {
            b[i]=arr[k];
            i++;
        }
    }
    
    for(k=low; k<=high; k++)
    {
        arr[k]=b[k];
    }
}    


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the text file to sort\n");
        return 2;
    }
    
    //Storing the File Name
    char* infile = argv[1];
    
    //Open the input file
    FILE* file = fopen(infile,"r");
    if(file == NULL)
    {
        printf("Cannot open file\n");
        return 2;
    } 
    
    int arr[SIZE], k;
    
    for(k = 0; k< SIZE; k++)
    {
        fscanf(file,"%d", &arr[k]);
        //printf("%d\n",arr[k]);
    }
    
    printf("\n");
    printf("\n");
    int* temp = malloc(sizeof(int)*SIZE);
    
    merge_sort(arr,temp, 0, SIZE-1);
    
    FILE* outFile = fopen("outfile2.txt","w");
    for(k = 0; k < SIZE; k++)
    {
        fprintf(outFile,"%d\n", arr[k]);
    }
    
    printf("The number of count inversions is %lu\n", count);
    return 0;
}
