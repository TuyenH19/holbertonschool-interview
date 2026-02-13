#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * remove_center - Recursively removes the center of squares to create Menger Carpet
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
 * menger - Draws a 2D Menger Sponge (Menger Carpet)
 * @level: The recursion level of the Menger Sponge
 */
void menger(int level)
{
	int size;
	int i, j;
	int **grid;

	if (level < 0)
		return;

	/* Calculate the size of the grid (3^level x 3^level) */
	size = (int)pow(3, level);

	/* Allocate memory for the grid */
	grid = malloc(size * sizeof(int *));
	if (grid == NULL)
		return;

	for (i = 0; i < size; i++)
	{
		grid[i] = malloc(size * sizeof(int));
		if (grid[i] == NULL)
			return;
	}

	/* Initialize all cells to 1 (filled) */
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			grid[i][j] = 1;

	/* Generate the Menger Sponge */
	remove_center(grid, 0, 0, size, level);

	/* Print the grid */
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

	/* Free allocated memory */
	for (i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
}
