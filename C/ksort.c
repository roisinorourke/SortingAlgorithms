#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// CHANGE VARIABLE NAMES
// FILE WILL BE IN DIFFERENT DIRECTORY

int partition(int arr[], int lo, int hi)
{
    int part = lo;

    while (lo < hi)
    {
        while (arr[lo] <= arr[part] && lo < hi)
        {
            lo++;
        }
        
        while (arr[hi] > arr[part])
        {
            hi--;
        }
        
        if (lo < hi)
        {
            int temp = arr[lo]; 
            arr[lo] = arr[hi]; 
            arr[hi] = temp; 
        }
        
    }
    if (arr[part] > arr[hi])
    {
        int temp = arr[part]; 
        arr[part] = arr[hi]; 
        arr[hi] = temp; 
    }

    return hi;
}

void ksort(int arr[], int lo, int hi, int k)
{
    int pivot = 0;

    if (lo < hi)
    {
        pivot = partition(arr, lo, hi);
        ksort(arr, lo, pivot - 1, k);
        if (pivot < k-1)
        {
            ksort(arr, pivot + 1, hi, k);
        }
    }
}

int main(int argc, char *argv[]) 
{  
    
    FILE *fp;

    char *p = argv[1];
    long length;

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
    // based on code from https://www.quora.com/How-do-I-extract-an-integer-from-the-string-in-C

    int *num = NULL;
    num = (int *)malloc(sizeof(int)*length);
    
    fp = fopen(argv[1], "r");

    for (int i = 0; i < length; i++)
    {
        fscanf(fp, "%d", &num[i]);
    }

    fclose(fp);

    int k = 10;

    ksort(num, 0, length - 1, k); 

    /* make a new file to add the k sorted array to */
    char flength[50];
    sprintf(flength, "%ld", length);
    
    FILE *fptr;
    char fname[50] = "ksorted";
    strcat(fname, flength);
    strcat(fname, ".txt");

    fptr = fopen(fname, "w");

    for (size_t i = 0; i < length; i++)
    {
        fprintf(fptr, "%d ", num[i]);
    }
    fprintf(fptr, "\n");
    fclose(fptr);

    free(num);
    return 0;
} 