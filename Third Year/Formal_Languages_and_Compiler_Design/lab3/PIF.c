#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "PIF.h"

#define PIF_CAP 100

void init_pif(PIF* pif) {
	pif->elements = (PIFElement*)malloc(PIF_CAP * sizeof(PIFElement));
	pif->size = 0;
	pif->capacity = PIF_CAP;
}

void add_token(PIF* pif, const char* token, int index)
{
	if (pif->size >= pif->capacity) {
		pif->capacity *= 2;
		pif->elements = realloc(pif->elements, pif->capacity * sizeof(PIFElement));
	}

	pif->elements[pif->size].token = strdup(token);
	pif->elements[pif->size].index = index;
	pif->size++;
}

void print_pif(const PIF* pif)
{
	printf("\n PIF \n");
	for (int i = 0; i < pif->size; i++) {
		printf("%s => %d\n", pif->elements[i].token, pif->elements[i].index);
	}
}

void free_pif(PIF* pif)
{
	for (int i = 0; i < pif->size; i++) {
		free(pif->elements[i].token);
	}
	free(pif->elements);
	pif->size = 0;
	pif->capacity = 0;
}