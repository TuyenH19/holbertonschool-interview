#include <stdlib.h>
#include "binary_trees.h"

/**
 * heap_size - Gets the size of a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Size of the tree
 */
static size_t heap_size(binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (1 + heap_size(tree->left) + heap_size(tree->right));
}

/**
 * get_node_at_index_helper - Helper to find node at specific index
 * @tree: Pointer to the current node
 * @target: Target index to find
 * @current: Current index in complete binary tree
 * @size: Size of the tree
 *
 * Return: Pointer to the node at target index
 */
static binary_tree_t *get_node_at_index_helper(binary_tree_t *tree,
	size_t target, size_t current, size_t size)
{
	if (!tree || current >= size)
		return (NULL);
	if (current == target)
		return (tree);

	binary_tree_t *left_result = get_node_at_index_helper(tree->left, target,
		2 * current + 1, size);
	if (left_result)
		return (left_result);

	return (get_node_at_index_helper(tree->right, target, 2 * current + 2, size));
}

/**
 * get_node_at_index - Get a node at a specific index in a complete binary tree
 * @tree: Pointer to the root node
 * @index: Target index (0-based)
 * @size: Size of the tree
 *
 * Return: Pointer to the node at the index, or NULL if not found
 */
static binary_tree_t *get_node_at_index(binary_tree_t *tree,
	size_t index, size_t size)
{
	return (get_node_at_index_helper(tree, index, 0, size));
}

/**
 * swap_values - Swaps the values of two nodes
 * @a: First node
 * @b: Second node
 */
static void swap_values(binary_tree_t *a, binary_tree_t *b)
{
	int tmp;

	tmp = a->n;
	a->n = b->n;
	b->n = tmp;
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root of the heap
 * @value: Value to insert
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent_node;
	size_t size;

	if (!root)
		return (NULL);

	size = heap_size(*root);
	new_node = binary_tree_node(NULL, value);
	if (!new_node)
		return (NULL);

	if (!(*root))
	{
		*root = new_node;
		return (new_node);
	}

	parent_node = get_node_at_index(*root, (size - 1) / 2, size);
	if (size % 2 == 1)
		parent_node->left = new_node;
	else
		parent_node->right = new_node;
	new_node->parent = parent_node;

	/* Bubble up the new node to maintain max heap property */
	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		swap_values(new_node, new_node->parent);
		new_node = new_node->parent;
	}

	return (new_node);
}
