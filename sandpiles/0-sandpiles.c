#include <stdlib.h>
#include <stdio.h>
#include "sandpiles.h"

/**
* is_stable - Check if a grid is stable
* @grid: 3x3 sandpile that need to be checked stabilities
*
* Description: check value of each cell if it greater than 3
* Return: 1 if it is stable and 0 if not
*/
int is_stable(int grid[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				return (0);
			}
		}
	}
	return (1);
}

/**
* print_grid - print out a grid
* @grid: 3x3 sandpile that need to be printed
*
* Description: print all the grains value of a grid
*/
static void print_grid(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

/**
* topple - Stabilize then perform the toppling operation on a grid
* @grid: 3x3 sandpile that need to be toppled
*
* Description: Check if the grid is unstable and performs the topping
* until the grid becomes stable then check if any cell has more than 3 grains
*  & redistributes grains to its neighbor cells
*/
void topple(int grid[3][3])
{
	int i, j;
	int temp[3][3];

	while (!is_stable(grid))
	{
		printf("=\n");
		print_grid(grid);

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				temp[i][j] = grid[i][j];

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (temp[i][j] > 3)
				{
					grid[i][j] -= 4;
					if (i > 0)
						grid[i - 1][j] += 1;
					if (i < 2)
						grid[i + 1][j] += 1;
					if (j > 0)
						grid[i][j - 1] += 1;
					if (j < 2)
						grid[i][j + 1] += 1;
				}
			}
		}
	}
}

/**
* sandpiles_sum - Computes the sum of two sandpiles and stabilizes the result
* @grid1: First 3x3 sandpile (result stored here)
* @grid2: second 3x3 sandpiles
*
* Description: Add two 3x3 sandpiles together and calls topple function
* to stabilize the grid if needed
*/
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid1[i][j] += grid2[i][j];
		}
	}

	topple(grid1);
}
