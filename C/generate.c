#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function to generate a list of random numbers (unsorted) in a file */
void rando(int size)
{
    char num[50];
    FILE *fptr;

    sprintf(num, "%d", size); // turn the size of the array into a string, and assign it to the num variable

    /* name the file */
    char fname[50] = "random";
    strcat(fname, num);
    strcat(fname, ".txt"); // file name will be, for example, random100.txt, where there are 100 random integers

    /* write to the file */
    fptr = fopen(fname, "w");

    for (size_t i = 0; i < size; i++) // while i is less than the length of the array, keep adding a random, unsorted integer to the file
    {
        fprintf(fptr, "%d ", rand());
    }
    fprintf(fptr, "\n"); // add a new line at the end of the file
    fclose(fptr); // close the file
}

/* function to generate an array of sorted numbers in a file */
void sorted(int size)
{
    char num[50];
    FILE *fptr;

    sprintf(num, "%d", size); // turn the size of the array into a string, and assign it to the num variable
    
    char fname[100] = "sorted";
    strcat(fname, num);
    strcat(fname, ".txt"); // file name will be for example sorted1000.txt, for an array of 1000 sorted integers

    fptr = fopen(fname, "w"); // open the file

    for (int i = 1; i <= size; i++) // while i is less than the size of the array add i to the file and increase i by one
    {
        fprintf(fptr, "%d ", i);
    }
    fprintf(fptr, "\n");
    fclose(fptr);
}

/* function to generate a reversed array of sorted numbers in a file */
void reversed(int size)
{
    char num[50];
    sprintf(num, "%d", size);
    
    FILE *fptr;
    char fname[50] = "reversed";
    strcat(fname, num);
    strcat(fname, ".txt"); // file name will be reversed100.txt for a file containing a reversed array of 100 integers

    fptr = fopen(fname, "w");

    for (int i = size; i > 0; i--) // let i = the size of the array, keep adding i to the file until i = 1
    {
        fprintf(fptr, "%d ", i);
    }
    fprintf(fptr, "\n");
    fclose(fptr);
}

int main(int argc, char const *argv[])
{
    int size = atoi(argv[1]); // take the integer from the command line argument

    /* pass the size of the array to the different array generating functions */
    rando(size);
    sorted(size);
    reversed(size);

    return 0;
}
