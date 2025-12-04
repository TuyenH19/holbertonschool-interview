#!/usr/bin/python3
"""
Log parsing script.

Reads from stdin line by line and computes:
- Total file size
- Number of lines by specific status codes

Prints statistics after every 10 lines and on keyboard interruption (CTRL + C).
"""

import sys


def print_stats(total_size, status_counts):
    """Print the accumulated statistics."""
    print(f"File size: {total_size}")
    for code in sorted(status_counts.keys()):
        if status_counts[code] > 0:
            print(f"{code}: {status_counts[code]}")


def main():
    total_size = 0
    line_count = 0

    # Initialize status code counters
    valid_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    status_counts = {code: 0 for code in valid_codes}

    try:
        for line in sys.stdin:
            line = line.strip()
            if not line:
                continue

            line_count += 1

            parts = line.split()
            # Expect at least: ... <status code> <file size>
            if len(parts) < 2:
                # Invalid format, skip
                if line_count % 10 == 0:
                    print_stats(total_size, status_counts)
                continue

            status_str = parts[-2]
            size_str = parts[-1]

            # Try to parse file size
            try:
                size = int(size_str)
                total_size += size
            except (ValueError, TypeError):
                # Bad file size, skip status code,
                # but still count line for printing
                if line_count % 10 == 0:
                    print_stats(total_size, status_counts)
                continue

            # Try to parse status code
            try:
                status = int(status_str)
            except (ValueError, TypeError):
                status = None

            if status in status_counts:
                status_counts[status] += 1

            # Every 10 lines, print stats
            if line_count % 10 == 0:
                print_stats(total_size, status_counts)

    except KeyboardInterrupt:
        # On CTRL + C, print stats and re-raise to mimic sample behavior
        print_stats(total_size, status_counts)
        raise

    # After EOF, print final stats
    print_stats(total_size, status_counts)


if __name__ == "__main__":
    main()
