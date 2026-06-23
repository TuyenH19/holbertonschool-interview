#include <stdlib.h>
#include <string.h>

/**
 * count_matching_words - Count words from the array match in the given window
 * @s: String pointer to window position
 * @words: Array of words to match
 * @nb_words: Number of words in array
 * @word_len: Length of each word
 *
 * Return: Number of matching words found in window
 */
static int count_matching_words(char const *s, char const **words,
	int nb_words, int word_len)
{
	int *window_count;
	int i;
	int j;
	int matches;
	char const *word;

	window_count = malloc(sizeof(int) * nb_words);
	if (!window_count)
		return (-1);

	for (i = 0; i < nb_words; i++)
		window_count[i] = 0;

	matches = 0;
	for (i = 0; i < nb_words; i++)
	{
		word = s + (i * word_len);
		for (j = 0; j < nb_words; j++)
		{
			if (strncmp(word, words[j], word_len) == 0 &&
				window_count[j] < 1)
			{
				window_count[j]++;
				matches++;
				break;
			}
		}
	}

	free(window_count);
	return (matches);
}

/**
 * search_concatenations - Search for word concatenations in string
 * @result: Result array to store indices
 * @s: The string to scan
 * @words: Array of words to concatenate
 * @nb_words: Number of words in the array
 * @word_len: Length of each word
 * @s_len: Length of the string
 *
 * Return: Number of matches found
 */
static int search_concatenations(int *result, char const *s,
	char const **words, int nb_words, int word_len, int s_len)
{
	int count;
	int total_len;
	int i;
	int matches;

	total_len = word_len * nb_words;
	count = 0;
	for (i = 0; i <= s_len - total_len; i++)
	{
		matches = count_matching_words(s + i, words, nb_words, word_len);
		if (matches == nb_words)
			result[count++] = i;
	}
	return (count);
}

/**
 * find_substring - Find all substrings that are concatenations of given words
 * @s: The string to scan
 * @words: Array of words to concatenate
 * @nb_words: Number of words in the array
 * @n: Pointer to store the number of found indices
 *
 * Return: Allocated array of indices, or NULL if none found
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	int *result;
	int count;
	int capacity;
	int word_len;
	int total_len;
	int s_len;

	if (!s || !words || nb_words == 0 || !n)
		return (NULL);

	word_len = strlen(words[0]);
	total_len = word_len * nb_words;
	s_len = strlen(s);
	*n = 0;

	if (s_len < total_len)
		return (NULL);

	capacity = s_len - total_len + 1;
	result = malloc(sizeof(int) * capacity);
	if (!result)
		return (NULL);

	count = search_concatenations(result, s, words, nb_words, word_len, s_len);

	if (count == 0)
	{
		free(result);
		return (NULL);
	}

	*n = count;
	return (result);
}
