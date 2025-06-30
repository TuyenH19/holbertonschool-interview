#!/usr/bin/python3
"""
0-rain.py
"""


def rain(walls):
    """
    Compute total units of water retained between walls.

    Args:
        walls (list[int]): non-negative wall heights

    Returns:
        int: total trapped water
    """
    if not walls or len(walls) < 3:
        return 0

    left, right = 0, len(walls) - 1
    left_max = right_max = 0
    water = 0

    while left < right:
        if walls[left] < walls[right]:
            if walls[left] >= left_max:
                left_max = walls[left]
            else:
                water += left_max - walls[left]
            left += 1
        else:
            if walls[right] >= right_max:
                right_max = walls[right]
            else:
                water += right_max - walls[right]
            right -= 1

    return water
