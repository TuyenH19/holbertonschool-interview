#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * remove_center - Recursively removes the center of squares
 * @grid: The 2D grid representing the carpet
 * @x: X coordinate of the top-left corner
 * @y: Y coordinate of the top-left corner
 * @size: Size of the current square
 * @level: Current recursion level
 */
static void remove_center(int **grid, int x, int y, int size, int level)
{
	int new_size;
	int i, j;

	if (level == 0)
		return;

	new_size = size / 3;

	/* Remove the center square */
	for (i = x + new_size; i < x + 2 * new_size; i++)
		for (j = y + new_size; j < y + 2 * new_size; j++)
			grid[i][j] = 0;

	/* Recursively apply to the other 8 squares */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == 1 && j == 1)
				continue; /* Skip center */
			remove_center(grid, x + i * new_size, y + j * new_size,
					new_size, level - 1);
		}
	}
}

/**
 * allocate_grid - Allocates and initializes memory for the grid
 * @size: Size of the grid
 *
 * Return: Pointer to allocated grid or NULL on failure
 */
static int **allocate_grid(int size)
{
	int **grid;
	int i, j;

	grid = malloc(size * sizeof(int *));
	if (grid == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		grid[i] = malloc(size * sizeof(int));
		if (grid[i] == NULL)
			return (NULL);
		for (j = 0; j < size; j++)
			grid[i][j] = 1;
	}
	return (grid);
}

/**
 * print_and_free - Prints the grid and frees memory
 * @grid: The grid to print and free
 * @size: Size of the grid
 */
static void print_and_free(int **grid, int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (grid[i][j])
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}

	for (i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
}

/**
 * menger - Draws a 2D Menger Sponge (Menger Carpet)
 * @level: The recursion level of the Menger Sponge
 */
void menger(int level)
{
	int size;
	int **grid;

	if (level < 0)
		return;

	size = (int)pow(3, level);
	grid = allocate_grid(size);
	if (grid == NULL)
		return;

	remove_center(grid, 0, 0, size, level);
	print_and_free(grid, size);
}
