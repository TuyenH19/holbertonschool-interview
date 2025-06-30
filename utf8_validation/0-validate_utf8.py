#!/usr/bin/env python3
"""
0-validate_utf8.py
"""


def validUTF8(data):
    """
    Return True if 'data' is a valid UTF-8 byte sequence, else False.
    data: list[int] – each int is treated as one byte (use its 8 LSBs).
    """
    need = 0  # bytes still to read in current code point

    for num in data:
        byte = num & 0xFF              # keep only 8 least-significant bits

        if need == 0:
            # Figure out how many leading 1s the byte has
            mask = 0x80
            count = 0
            while mask & byte:
                count += 1
                mask >>= 1

            if count == 0:             # 1-byte ASCII
                continue
            if count == 1 or count > 4:
                return False           # invalid leader size
            need = count - 1           # continuation bytes still expected
        else:
            # Must be a continuation byte: 10xxxxxx
            if (byte & 0xC0) != 0x80:
                return False
            need -= 1

    return need == 0
