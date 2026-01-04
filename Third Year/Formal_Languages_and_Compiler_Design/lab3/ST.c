#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ST.h"

static STNode* create_node(const char* token, int index) {
	STNode* newNode = (STNode*)malloc(sizeof(STNode));
	newNode->index = index;
	newNode->token = strdup(token);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int insert_node(STNode** root, const char* token, int* index)
{
	if (*root == NULL) {
		*root = create_node(token, *index);
		(*index)++;
		return (*root)->index;
	}

	int chars = strcmp((*root)->token, token);
	if (chars == 0) {
		return (*root)->index;
	}
	else if (chars < 0) {
		return insert_node(&((*root)->left), token, index);
	}
	else {
		return insert_node(&((*root)->right), token, index);
	}
}

int search_node(STNode* root, const char* token)
{
	if (root == NULL) 
		return -1;

	int chars = strcmp(token, root->token);
	if (chars == 0) {
		return root->index;
	}
	else if (chars < 0) {
		return search_node(root->left, token);
	}
	else {
		return search_node(root->right, token);
	}
}

void print_ST(STNode* root)
{
	if (root == NULL)
		return;

	print_ST(root->left);
	printf("%s => %d\n", root->token, root->index);
	print_ST(root->right);
}

void free_ST(STNode* root)
{
	if (root == NULL)
		return;
	free_ST(root->left);
	free_ST(root->right);
	free(root->token);
	free(root);
}
