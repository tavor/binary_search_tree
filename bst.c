#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
const char * USAGE_MESSAGE 		= "Usage: bst #\n";
const char * PARAM_GREATER_THAN_ZERO 	= "# must be greater than 0\n"; 
const char * PROMPT_NODE_VALUES		= "Enter %i integer values to place in tree:\n";

/**
 * Insert a value into the tree
 */
void insert(TreeNode ** root, int data)
{
	if (!*root)
	{
		*root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
		(*root)->data = data;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else if (data < (*root)->data)
	{
		insert(&((*root)->left), data);
	}
	else if (data > (*root)->data)
	{
		insert(&((*root)->right), data);
	}
}

/**
 * Goes through all elements and inserts, one by one, into the tree
 */
void build_tree(TreeNode** root, const int elements[], const int count)
{
	for (int e = 0; e < count; e++)
	{
		insert (root, elements[e]);
	}
}

/**
 * Traverses binary search tree depending on enum passed
 */
void traverse(TreeNode** root, const TraversalType type)
{
	if (*root)
	{
		switch (type)
		{
			case PREORDER:
				printf("%i\n", (*root)->data);
				traverse(&((*root)->left), PREORDER);
				traverse(&((*root)->right), PREORDER);
				break;
			case INORDER:
				traverse(&((*root)->left), INORDER);
				printf("%i\n", (*root)->data);
				traverse(&((*root)->right), INORDER);
				break;
			case POSTORDER: 
				traverse(&((*root)->left), POSTORDER);
				traverse(&((*root)->right), POSTORDER);
				printf("%i\n", (*root)->data);
				break;
		}
	}
} 

/**
 * Clean up mem, post-order
 */
void cleanup_tree(TreeNode** root)
{
	if (*root)
	{
		// Cleanup left subtree
		cleanup_tree(&((*root)->left));
		
		// Cleanup right subtree
		cleanup_tree(&((*root)->right));
		
		// Cleanup root
		free(*root);
	}
}

int main(int argc, char *argv[])
{
	/* Initialize variables */
	int numNodes = 0;
	int * nodeValues;
	
	// Check for correct number of args
	if (argc != 2) printf(USAGE_MESSAGE);
	
	// Convert argument to integer
	sscanf(argv[1], "%i", &numNodes);

	// Check that integer passed in is int greater than zero
	if (numNodes <= 0) printf(PARAM_GREATER_THAN_ZERO);

	// Allocate mem on the heap for all of the node values
	nodeValues = (int *)malloc(sizeof(int) * numNodes);

	// Prompt to get that number of node values
	printf(PROMPT_NODE_VALUES, numNodes);

	// Read values from stdin
	for(int i = 0; i < numNodes; i++)
	{
		scanf("%i", &nodeValues[i]);
	}

	// Display values to stdout
	printf("Input values: \n");
	for(int i = 0; i < numNodes; i++)
	{
		printf("%i\n", nodeValues[i]);
	}

	TreeNode * root = NULL;
	build_tree(&root, nodeValues, numNodes);
	
	free(nodeValues);

	// Display pre-order
	printf("Preorder:\n");
	traverse(&root, PREORDER);

	// Display in-order
	printf("Inorder:\n");
	traverse(&root, INORDER);

	// Postorder
	printf("Postorder:\n");
	traverse(&root, POSTORDER);

	cleanup_tree(&root);
}
