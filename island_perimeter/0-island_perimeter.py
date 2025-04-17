#!/usr/bin/python3
"""
Function to calculate the perimeter of the island described in a grid.
"""


def island_perimeter(grid):
    """
        @grid: A 2D list representing the grid where 1 is land and 0 is water.
        return: int: The perimeter of the island.
    """
    rows = len(grid)
    cols = len(grid[0]) if rows > 0 else 0
    perimeter = 0

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 1:
                perimeter += 4

                # Check if there is land above this grid
                if r > 0 and grid[r-1][c] == 1:
                    perimeter -= 2

                # Check if there is land on the left of this grid
                if c > 0 and grid[r][c-1] == 1:
                    perimeter -= 2

    return perimeter
