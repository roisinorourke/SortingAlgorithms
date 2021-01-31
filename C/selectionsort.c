#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* function to swap two integers */
void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
/* function to sort the array using selection sort */
void selection_sort(int arr[], int length) 
{ 
    /* initialise variables */
    int i = 0;
    int j = 0;
    int min_index; 

    for (i = 0; i < length - 1; i++) // move through the unsorted section of the array one by one
    { 
        /* Find the index of the smallest element in the array */
        min_index = i; 
        for (j = min_index + 1; j < length; j++) 
        {
            if (arr[j] < arr[min_index]) 
            {
                min_index = j; 
            }
        }
        // Swap the smallest element with the first element 
        swap(&arr[min_index], &arr[i]); 
    } 
}

/* function that extracts the number from the file name so we know the length of the array */
int array_len( char *p)
{
    int length;

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

    selection_sort(num, length); // pass the array and length into the selection sort function

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