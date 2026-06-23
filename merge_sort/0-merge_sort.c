#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * merge - Merges two sorted subarrays into a single sorted subarray
 * @array: The original array
 * @temp: Temporary array for merging
 * @left: Start index of the left subarray
 * @mid: End index of the left subarray (mid + 1 is start of right)
 * @right: End index of the right subarray
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
    size_t i = left, j = mid + 1, k = left;

    printf("Merging...\n");
    
    /* Print left subarray */
    printf("[left]: ");
    for (size_t idx = left; idx <= mid; idx++)
    {
        if (idx > left)
            printf(", ");
        printf("%d", array[idx]);
    }
    printf("\n");
    
    /* Print right subarray */
    printf("[right]: ");
    for (size_t idx = mid + 1; idx <= right; idx++)
    {
        if (idx > mid + 1)
            printf(", ");
        printf("%d", array[idx]);
    }
    printf("\n");

    /* Merge the two halves into temp */
    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    /* Copy remaining elements from left half */
    while (i <= mid)
        temp[k++] = array[i++];

    /* Copy remaining elements from right half */
    while (j <= right)
        temp[k++] = array[j++];

    /* Copy merged elements back to original array */
    for (k = left; k <= right; k++)
        array[k] = temp[k];

    /* Print merged result */
    printf("[Done]: ");
    for (k = left; k <= right; k++)
    {
        if (k > left)
            printf(", ");
        printf("%d", array[k]);
    }
    printf("\n");
}

/**
 * merge_sort_recursive - Recursive helper for merge sort
 * @array: The array to sort
 * @temp: Temporary array for merging
 * @left: Start index of the subarray
 * @right: End index of the subarray
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
    if (left >= right)
        return;

    size_t mid = left + (right - left) / 2;  /* Ensures left <= right */

    /* Sort left half first */
    merge_sort_recursive(array, temp, left, mid);
    /* Then sort right half */
    merge_sort_recursive(array, temp, mid + 1, right);
    /* Merge the sorted halves */
    merge(array, temp, left, mid, right);
}

/**
 * merge_sort - Sorts an array of integers in ascending order using Merge Sort
 * @array: The array to sort
 * @size: The size of the array
 *
 * This is a top-down implementation. Allocates a temporary array once.
 */
void merge_sort(int *array, size_t size)
{
    if (!array || size < 2)
        return;

    int *temp = malloc(sizeof(int) * size);
    if (!temp)
        return;

    merge_sort_recursive(array, temp, 0, size - 1);
    free(temp);
}
