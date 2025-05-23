#!/usr/bin/python3
"""
  Minimum Operations Function.
"""


def minOperations(n):
    """
      @n: number of operation processed
      return: int n
    """

    if n <= 1:
        return 0

    min_operation = 0

    current_length = 1

    store = 0

    # Loop until the current length is equal to n
    while current_length < n:
        if n % current_length == 0:

            store = current_length

            min_operation += 1

        current_length += store

        min_operation += 1

    return min_operation
