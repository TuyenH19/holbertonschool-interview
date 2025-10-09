#include "binary_trees.h"

/**
 * tree_size - measures the size of a binary tree
 * @tree: tree to measure the size of
 *
 * Return: size of the tree
 *         0 if tree is NULL
 */
size_t tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (tree_size(tree->left) + tree_size(tree->right) + 1);
}

/**
 * tree_last - finds the last node in level order of a complete binary tree
 * @root: pointer to the root of the tree
 * @index: index of the node
 * @size: number of nodes in the tree
 *
 * Return: pointer to the last node
 */
heap_t *tree_last(heap_t *root, size_t index, size_t size)
{
	heap_t *left, *right;

	if (!root || index > size)
		return (NULL);

	if (index == size)
		return (root);

	left = tree_last(root->left, 2 * index, size);
	if (left)
		return (left);
	right = tree_last(root->right, 2 * index + 1, size);
	return (right);
}

/**
 * heapify - rebuilds a max heap
 * @root: pointer to root of heap
 */
void heapify(heap_t *root)
{
	int value;
	heap_t *largest_child;

	if (!root)
		return;

	largest_child = root;

	if (root->left && root->left->n > largest_child->n)
		largest_child = root->left;

	if (root->right && root->right->n > largest_child->n)
		largest_child = root->right;

	if (largest_child != root)
	{
		value = root->n;
		root->n = largest_child->n;
		largest_child->n = value;
		heapify(largest_child);
	}
}

/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: double pointer to the root node of the heap
 *
 * Return: value stored in the root node
 *         0 if function fails
 */
int heap_extract(heap_t **root)
{
	int value;
	heap_t *heap_r, *last;

	if (!root || !*root)
		return (0);

	heap_r = *root;
	value = heap_r->n;

	if (!heap_r->left && !heap_r->right)
	{
		*root = NULL;
		free(heap_r);
		return (value);
	}

	last = tree_last(heap_r, 1, tree_size(heap_r));

	heap_r->n = last->n;

	if (last->parent->right)
		last->parent->right = NULL;
	else
		last->parent->left = NULL;

	free(last);
	heapify(heap_r);
	return (value);
}
