#ifndef PIF_H
#define PIF_H

typedef struct {
	char* token;
	int index;
}PIFElement;

typedef struct {
	PIFElement* elements;
	int size;
	int capacity;
}PIF;

void init_pif(PIF* pif);
void add_token(PIF* pif, const char* token, int index);
void print_pif(const PIF* pif);
void free_pif(PIF* pif);

#endif



