#include "lists.h"
#include <stddef.h>

/**
 * reverse_list - reverses a linked list
 * @head: pointer to the head of the list
 * Return: pointer to the new head
 */
listint_t *reverse_list(listint_t *head)
{
listint_t *prev = NULL, *current = head, *next;

while (current != NULL)
{
	next = current->next;
	current->next = prev;
	prev = current;
	current = next;
}
return (prev);
}

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: pointer to pointer of first node of listint_t list
 * Return: 1 if it is a palindrome, 0 if it is not
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow, *fast, *first_half, *second_half;

	if (*head == NULL || (*head)->next == NULL)
		return (1);

	slow = fast = *head;
	first_half = *head;

	/* Find middle of list */
	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}

	/* Skip middle element for odd length */
	if (fast != NULL)
		slow = slow->next;

	/* Reverse second half */
	second_half = reverse_list(slow);

	/* Compare halves */
	while (second_half != NULL)
	{
		if (first_half->n != second_half->n)
		{
			reverse_list(second_half);
			return (0);
		}
		first_half = first_half->next;
		second_half = second_half->next;
	}

	/* Restore list */
	reverse_list(slow);
	return (1);
}
