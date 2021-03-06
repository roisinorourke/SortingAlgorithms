#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

/* function to find the partition element */
int partition(int arr[], int low, int high)
{
    int part = low; // take the first element as the partition

    while (low < high)
    {
        while (arr[low] <= arr[part] && low < high)
        {
            low++; // find the first element greater than the partition to the left of the partition
        }
        
        while (arr[high] > arr[part])
        {
            high--; // find the first element smaller than the partition to the right of the partition
        }
        
        if (low < high) // if there is an element to the left of the partition greater than it, swap with the element to the right of it
        {
            /* swap two integers */
            int temp = arr[low]; 
            arr[low] = arr[high]; 
            arr[high] = temp; 
        }
        
    }
    if (arr[part] > arr[high]) // may happen if the array only has two elements, swap the partition with the element to the right
    {
        /* swap two integers */
        int temp = arr[part]; 
        arr[part] = arr[high]; 
        arr[high] = temp; 
    }

    return high; // return new partition element, everything to the left is smaller,
                 // everything to the right is greater
}

/* function to partially sort an array */
void ksort(int arr[], int lo, int hi, int k)
{
    int pivot = 0;

    if (lo < hi)
    {
        pivot = partition(arr, lo, hi); // find the partition element, or pivot
        ksort(arr, lo, pivot - 1, k);
        if (pivot < k-1)
        {
            ksort(arr, pivot + 1, hi, k);
        }
    }
}

/* extracts the number from the file name so we know the length of the array */
int array_len( char *p)
{
    long length;

    /* go through the file name char by char */
    while (*p) 
    { // While there are more characters to process...
        if ( isdigit(*p) ) 
        {
        // Found a number
            length = strtol(p, &p, 10); // Read number
        } 
        else 
        {
        // Otherwise, move on to the next character.
            p++;
        }
    }
    return length;
}

int main(int argc, char *argv[]) 
{  
    
    FILE *fp1;
    FILE *fp2;

    /* find the length of the array */
    int length = array_len(argv[1]);

    /* declare a pointer for the array of integers and allocate a block of memory for the array */
    int *num = NULL;
    num = (int *)malloc(sizeof(int)*length);
    
    /* open the file of unsorted integers in the command line and pass the integers into an array */
    fp1 = fopen(argv[1], "r");

    for (int i = 0; i < length; i++)
    {
        fscanf(fp1, "%d", &num[i]);
    }

    fclose(fp1);

    /* find the value that k will be */
    int k = (length / 3) + 1;

    /* pass the array, high, low figure, and k into the ksort function */
    ksort(num, 0, length - 1, k); 

    /* name the new file the k sorted array will be in */
    char flength[50];
    sprintf(flength, "%d", length);

    char fname[50] = "ksorted";
    strcat(fname, flength);
    strcat(fname, ".txt");

    /* open the file to write to and pass the k-sorted array into it */
    fp2 = fopen(fname, "w");

    for (size_t i = 0; i < length; i++)
    {
        fprintf(fp2, "%d ", num[i]);
    }
    fprintf(fp2, "\n");
    fclose(fp2);

    /* release the memory allocated for the array */
    free(num);
    return 0;
} 