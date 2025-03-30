#include "slide_line.h"


/**
 * slide_left - Slides and merges an array of integers to the left
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 *
 * Return: void
 */
void slide_left(int *line, size_t size)
{
size_t i, pos;

pos = 0;
for (i = 0; i < size; i++)
{
	if (line[i] != 0)
	{
		line[pos++] = line[i];
		if (i != pos - 1)
			line[i] = 0;
	}
}
for (i = 0; i < size - 1; i++)
{
	if (line[i] != 0 && line[i] == line[i + 1])
	{
		line[i] *= 2;
		line[i + 1] = 0;
	}
}
pos = 0;
for (i = 0; i < size; i++)
{
	if (line[i] != 0)
	{
		line[pos++] = line[i];
		if (i != pos - 1)
			line[i] = 0;
	}
}
}

 /**
 * slide_right - Slides and merges an array of integers to the right
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 *
 * Return: void
 */
void slide_right(int *line, size_t size)
{
size_t i, pos;

pos = size - 1;
for (i = size - 1; i < size; i--)
{
	if (line[i] != 0)
	{
		line[pos--] = line[i];
		if (i != pos + 1)
			line[i] = 0;
	}
}

for (i = size - 1; i > 0; i--)
{
	if (line[i] != 0 && line[i] == line[i - 1])
	{
		line[i] *= 2;
		line[i - 1] = 0;
	}
}

pos = size - 1;
for (i = size - 1; i < size; i--)
{
	if (line[i] != 0)
	{
		line[pos--] = line[i];
		if (i != pos + 1)
			line[i] = 0;
	}
}
}

 /**
 * slide_line - Slides and merges an array of integers
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 * @direction: Direction to slide (SLIDE_LEFT or SLIDE_RIGHT)
 *
 * Return: 1 upon success, 0 upon failure
 */
int slide_line(int *line, size_t size, int direction)
{
if (direction != SLIDE_LEFT && direction != SLIDE_RIGHT)
	return (0);

if (direction == SLIDE_LEFT)
	slide_left(line, size);
else
	slide_right(line, size);

return (1);
}
