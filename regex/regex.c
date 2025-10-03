#include <stdio.h>
#include <stdlib.h>
#include "regex.h"
#include <string.h>

/**
 * regex_match - Checks if a string matches a given pattern
 * @str: The input string
 * @pattern: The regex pattern (supports '.' and '*')
 *
 * Return: 1 if the string matches the pattern, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
	if (*pattern == '\0')
		return (*str == '\0');

	int first_match = (*str != '\0' && (*pattern == *str || *pattern == '.'));

	if (*(pattern + 1) == '*')
	{
		return (regex_match(str, pattern + 2) ||
						(first_match && regex_match(str + 1, pattern)));
	}
	else
	{
		return (first_match && regex_match(str + 1, pattern + 1));
	}
}
