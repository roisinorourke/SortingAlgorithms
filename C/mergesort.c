#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void merge(int arr[], int lo, int mid, int hi)
{
    int n1 = mid - lo + 1;
    int n2 = hi - mid;
 
    /* create temp arrays L and R using dynamic memory */
    int *L = (int *)malloc(sizeof(int)*n1);
    int *R = (int *)malloc(sizeof(int)*n2);
 
    /* Copy data to the temp arrays */
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[lo + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }
 
    /* Merge the temp arrays back into arr */
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = lo; // Initial index of merged subarray
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) // if the num in the L array is less than num in R array, add back to main array
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    /* free the allocated dynamic memory for the temp arrays */
    free(L);
    free(R);
}
 
/* lo is for left index and hi is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int lo, int hi)
{
    if (lo < hi) 
    {
        
        int mid = lo + (hi - lo) / 2; // find the index of the middle array
 
        /* Sort first and second halves of the array */
        mergeSort(arr, lo, mid);
        mergeSort(arr, mid + 1, hi);
 
        merge(arr, lo, mid, hi);
    }
}
/* bases on mergesort code from geeksforgeeks */ 

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
// based on code from https://www.quora.com/How-do-I-extract-an-integer-from-the-string-in-C


/* function to make sure the array is sorted */
void sorted_check(int num[], int length)
{
    bool x = true; // let x initally be true
    
    for (int i = 0; i < length - 1; i++) // go through the array one element at a time
    {
        if (num[i] > num[i + 1]) // if one element is greater than the element before it, array is not sorted
        {
            x = false; // change x to be false if the array is not sorted 
        }
    }

    if (x) // if x is still true, no non sorted numbers in the array
    {
        printf("sorted");
    }
    else
    {
        printf("not sorted");
    }
}

int main(int argc, char *argv[]) 
{  
    /* start the clock to record how long the program takes */
    clock_t begin = clock();
    
    FILE *fp;

    /* find the length of the array */
    int length = array_len(argv[1]);

    /* declare a pointer for the array of integers and allocate a block of memory for the array */
    int *num = NULL;
    num = (int *)malloc(sizeof(int)*length);
    
    /* open the file in the command line and pass the integers into an array */
    fp = fopen(argv[1], "r");

    for (int i = 0; i < length; i++)
    {
        fscanf(fp, "%d", &num[i]);
    }

    fclose(fp); // close the file after the content has been moved to the num array

    mergeSort(num, 0, length - 1); // pass the array, high and low figure into the mergesort function 

    /* end the clock when the quicksort program finishes running */
    clock_t end = clock();

    /* print how the program took to run */
    printf("Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    /* make sure the array is sorted */
    sorted_check(num, length);

    /* release the memory allocated for the array */
    free(num); 

    return 0;
} 