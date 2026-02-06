#!/usr/bin/python3
"""
N Queens Problem Solver

Usage: nqueens N
    - N must be an integer greater than or equal to 4
"""
import sys


def is_safe(board, row, col, n):
    """
    Check if it's safe to place a queen at position (row, col)

    Args:
        board: List of queen positions [row, col] for each placed queen
        row: Row position to check
        col: Column position to check
        n: Size of the board

    Returns:
        True if position is safe, False otherwise

    Explanation:
        A position is safe if no other queen can attack it.
        Queens attack horizontally, vertically, and diagonally.
        Since we place one queen per row, we only need to check:
        1. Column conflicts (same column)
        2. Diagonal conflicts (same diagonal)
    """
    # Check each previously placed queen
    for queen in board:
        prev_row, prev_col = queen

        # Check if same column
        if prev_col == col:
            return False

        # Check diagonal attacks
        # Two queens are on the same diagonal if the absolute difference
        # of their rows equals the absolute difference of their columns
        if abs(prev_row - row) == abs(prev_col - col):
            return False

    return True


def solve_nqueens(n, row, board, solutions):
    """
    Recursively solve N queens problem using backtracking

    Args:
        n: Size of the board (N×N)
        row: Current row we're trying to place a queen in
        board: Current state of placed queens
        solutions: List to store all valid solutions

    Explanation:
        This is a backtracking algorithm:
        1. Try placing a queen in each column of the current row
        2. For each placement, check if it's safe
        3. If safe, recursively solve for the next row
        4. If we reach row N, we've found a complete solution
        5. Backtrack by removing the queen and trying the next column
    """
    # Base case: all queens are placed successfully
    if row == n:
        # Add a copy of the current solution
        solutions.append([queen[:] for queen in board])
        return

    # Try placing a queen in each column of the current row
    for col in range(n):
        # Check if this position is safe
        if is_safe(board, row, col, n):
            # Place the queen
            board.append([row, col])

            # Recursively solve for the next row
            solve_nqueens(n, row + 1, board, solutions)

            # Backtrack: remove the queen and try next position
            board.pop()


def print_solutions(solutions):
    """
    Print all solutions in the required format

    Args:
        solutions: List of all valid queen placements

    Explanation:
        Each solution is printed as a list of [row, col] positions
        where each position represents where a queen is placed.
    """
    for solution in solutions:
        print(solution)


def main():
    """
    Main function to validate input and solve N queens problem

    Explanation of the overall algorithm:

    STEP 1: Input Validation
        - Check if exactly one argument is provided
        - Verify it's a valid integer
        - Ensure N is at least 4 (problem requirement)

    STEP 2: Initialize Data Structures
        - board: List to track currently placed queens
        - solutions: List to store all valid solutions

    STEP 3: Solve Using Backtracking
        - Start from row 0
        - For each row, try placing a queen in each column
        - Use recursion to explore all possibilities
        - Backtrack when a placement leads to no solution

    STEP 4: Output Results
        - Print all valid solutions found

    Time Complexity: O(N!)
        - In the worst case, we explore N! possible arrangements

    Space Complexity: O(N)
        - Recursion depth is N
        - Board state stores at most N queens
    """
    # STEP 1: Validate command line arguments
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    # Check if N is a valid integer
    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    # Check if N is at least 4
    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    # STEP 2: Initialize data structures
    board = []  # Current state of placed queens
    solutions = []  # All valid solutions

    # STEP 3: Solve the N queens problem
    solve_nqueens(n, 0, board, solutions)

    # STEP 4: Print all solutions
    print_solutions(solutions)


if __name__ == "__main__":
    main()
