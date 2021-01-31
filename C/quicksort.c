#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int partition(int arr[], int low, int high)
{
    int part = low;

    while (low < high)
    {
        while (arr[low] <= arr[part] && low < high)
        {
            low++;
        }
        
        while (arr[high] > arr[part])
        {
            high--;
        }
        
        if (low < high)
        {
            int temp = arr[low]; 
            arr[low] = arr[high]; 
            arr[high] = temp; 
        }
        
    }
    if (arr[part] > arr[high])
    {
        int temp = arr[part]; 
        arr[part] = arr[high]; 
        arr[high] = temp; 
    }

    return high;
}

void quicksort(int arr[], int low, int high)
{
    int pivot = 0;

    if (low < high)
    {
        pivot = partition(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

int array_len( char *p)
{
    int length;

    /* extracts the number from the file name so we know the length of the array */
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
    // based on code from https://www.quora.com/How-do-I-extract-an-integer-from-the-string-in-C
}

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

    quicksort(num, 0, length - 1); // pass the array, high and low figure into the quicksort function 

    /* end the clock when the quicksort program finishes running */
    clock_t end = clock();
 
    /* print how the program took to run */
    printf("Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

    sorted_check(num, length);
    
    /* release the memory allocated for the string */
    free(num);

    return 0;
} 