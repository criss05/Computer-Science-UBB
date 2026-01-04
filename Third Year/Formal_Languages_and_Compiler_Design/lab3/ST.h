#ifndef ST_H
#define ST_H

typedef struct STNode {
	char* token;
	int index;
	struct STNode* left;
	struct STNode* right;
}STNode;

int insert_node(STNode** root, const char* token, int* index);
int search_node(STNode* root, const char* token);
void print_ST(STNode* root);
void free_ST(STNode* root);

#endif
