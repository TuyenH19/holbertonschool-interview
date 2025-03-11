#include <stdlib.h>
#include <stdio.h>
#include "sandpiles.h"

int is_stable(int grid[3][3]);
void sandpiles_sum(int grid1[3][3], int grid2[3][3]);
void stablize_sandpile(int grid[3][3]);

int is_stable(int grid[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (grid[i][j] >= 4)
			{
				return (0);
			}
		}
	}
	return (1);
}

void stablize_sandpile(int grid[3][3])
{
	int temp[3][3];

	while (!is_stable(grid))
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[i][j] = grid[i][j];
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (temp[i][j] >= 4)
				{
					grid[i][j] -= 4;
					if (i > 0)
						grid[i - 1][j]++;
					if (i < 2)
						grid[i + 1][j]++;
					if (j > 0)
						grid[i][j - 1]++;
					if (j < 2)
						grid[i][j + 1]++;
				}
			}
		}
	}
}


void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int temp[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] =  grid1[i][j] + grid2[i][j];
		}
	}

	if (!is_stable(temp)) {
		printf("=\n");
		print_grid(temp);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			grid1[i][j] = temp[i][j];
		}
	}

	stablize_sandpile(grid1);
}
