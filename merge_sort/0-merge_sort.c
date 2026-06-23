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

	printf("Merging...\n[left]: ");
	for (size_t x = left; x <= mid; x++)
		printf("%s%d", x > left ? ", " : "", array[x]);
	printf("\n[right]: ");
	for (size_t x = mid + 1; x <= right; x++)
		printf("%s%d", x > mid + 1 ? ", " : "", array[x]);
	printf("\n");

	while (i <= mid && j <= right)
		temp[k++] = (array[i] <= array[j]) ? array[i++] : array[j++];
	while (i <= mid)
		temp[k++] = array[i++];
	while (j <= right)
		temp[k++] = array[j++];
	for (k = left; k <= right; k++)
		array[k] = temp[k];

	printf("[Done]: ");
	for (k = left; k <= right; k++)
		printf("%s%d", k > left ? ", " : "", array[k]);
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

	size_t mid = left + (right - left - 1) / 2;

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
