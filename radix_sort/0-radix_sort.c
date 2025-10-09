#include <stdlib.h>
#include "sort.h"

/**
 * get_max - Get the maximum value in an array
 * @array: The array to search
 * @size: The size of the array
 *
 * Return: The maximum value in the array
 */
static int get_max(const int *array, size_t size)
{
	int max = array[0];

	for (size_t i = 1; i < size; i++)
		if (array[i] > max)
			max = array[i];
	return (max);
}

/**
 * counting_sort_by_digit - Stable counting sort by a specific base-10 digit.
 * @array: Pointer to the array of integers to be sorted in-place.
 * @size: Number of elements in @array.
 * @exp:  Exponent for the digit to sort by (1 for units, 10 for tens, etc.).
 *
 * Return: void
 */
static void counting_sort_by_digit(int *array, size_t size, int exp)
{
	int count[10] = {0};
	int *out = (int *)malloc(size * sizeof(int));

	if (!out)
		return; /* If allocation fails, silently skip (keeps program safe) */

	/* Count occurrences of digits */
	for (size_t i = 0; i < size; i++)
		count[(array[i] / exp) % 10]++;

	/* Prefix sums -> positions */
	for (int d = 1; d < 10; d++)
		count[d] += count[d - 1];

	/* Build output (stable: traverse from right to left) */
	for (ssize_t i = (ssize_t)size - 1; i >= 0; i--)
	{
		int d = (array[i] / exp) % 10;

		out[--count[d]] = array[i];
	}

	for (size_t i = 0; i < size; i++)
		array[i] = out[i];

	print_array(array, size);

	free(out);
}

/**
 * radix_sort - Sort an array of integers in ascending order using LSD radix.
 * @array: Pointer to the array of integers to sort.
 * @size: Number of elements in @array.
 * Return: void
 */
void radix_sort(int *array, size_t size)
{
		if (!array || size < 2)
			return;
	
		int max = get_max(array, size);

		/* Sort by each digit (base 10) */
		for (int exp = 1; max / exp > 0; exp *= 10)
			counting_sort_by_digit(array, size, exp);
}
