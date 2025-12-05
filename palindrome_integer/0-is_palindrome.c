#include "palindrome.h"

/**
 * is_palindrome - checks whether or not a given unsigned integer is palindrome
 * @n: the number to be checked
 *
 * Return: 1 if n is a palindrome, and 0 otherwise
 */
int is_palindrome(unsigned long n)
{
	unsigned long reversed = 0;
	unsigned long original = n;
	unsigned long remainder;

	/* Reverse the number */
	while (n != 0)
	{
		remainder = n % 10;
		reversed = reversed * 10 + remainder;
		n = n / 10;
	}

	/* Check if original number equals reversed number */
	if (original == reversed)
		return (1);
	else
		return (0);
}
