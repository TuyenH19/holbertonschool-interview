#include <stdlib.h>
#include "binary_trees.h"

/* ---- Helpers ---- */

/**
 * binary_tree_size - Computes the number of nodes in a binary tree.
 * @tree: Pointer to root.
 * Return: Size (node count).
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (!tree)
        return (0);
    return 1 + binary_tree_size(tree->left) + binary_tree_size(tree->right);
}

/**
 * last_level_order_node - Returns pointer to the last node in level order.
 * @root: Pointer to heap root.
 * Return: Pointer to deepest, rightmost node (last visited in BFS), or NULL.
 *
 * Implementation detail: uses a simple array as a queue sized to the tree.
 */
static heap_t *last_level_order_node(heap_t *root)
{
    size_t size, front = 0, back = 0;
    heap_t **q, *curr = NULL;

    if (!root)
        return (NULL);

    size = binary_tree_size(root);
    q = malloc(sizeof(*q) * size);
    if (!q)
        return (NULL);

    q[back++] = root;
    while (front < back)
    {
        curr = q[front++];
        if (curr->left)
            q[back++] = curr->left;
        if (curr->right)
            q[back++] = curr->right;
    }
    free(q);
    return (curr);
}

/**
 * heapify_down - Restores max-heap property by sifting down from @node.
 * @node: Pointer to start node.
 */
static void heapify_down(heap_t *node)
{
    heap_t *largest;
    int tmp;

    if (!node)
        return;

    while (node)
    {
        largest = node;
        if (node->left && node->left->n > largest->n)
            largest = node->left;
        if (node->right && node->right->n > largest->n)
            largest = node->right;

        if (largest == node)
            break;

        /* swap values only */
        tmp = node->n;
        node->n = largest->n;
        largest->n = tmp;

        node = largest;
    }
}

/* ---- Main task ---- */

/**
 * heap_extract - Extracts the root value of a Max Binary Heap.
 * @root: Double pointer to heap root.
 * Return: The value stored in the root node, or 0 on failure.
 *
 * Behavior:
 * - Return the root's value.
 * - Free the root node and replace it with the last level-order node.
 * - Rebuild heap if necessary.
 */
int heap_extract(heap_t **root)
{
    heap_t *old_root, *last, *lchild, *rchild, *parent;
    int value;

    if (!root || !*root)
        return (0);

    old_root = *root;
    value = old_root->n;

    /* If the heap has a single node */
    if (!old_root->left && !old_root->right)
    {
        free(old_root);
        *root = NULL;
        return (value);
    }

    /* Find last level-order node */
    last = last_level_order_node(old_root);
    if (!last) /* allocation failure in BFS */
        return (0);

    /* Detach last from its parent */
    parent = last->parent;
    if (parent)
    {
        if (parent->left == last)
            parent->left = NULL;
        else
            parent->right = NULL;
    }

    /* Save old root's children */
    lchild = old_root->left;
    rchild = old_root->right;

    /* Transplant last into root position */
    last->parent = NULL;
    last->left = lchild;
    last->right = rchild;
    if (lchild)
        lchild->parent = last;
    if (rchild)
        rchild->parent = last;

    /* Free the old root and update the root pointer */
    free(old_root);
    *root = last;

    /* Restore max-heap property */
    heapify_down(*root);

    return (value);
}
