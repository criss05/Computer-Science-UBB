#pragma once
#include "Service.h"

typedef struct {
	Service* service;
	int length;
}Ui;

Ui* CreateUi(int length);
void DestroyUi(Ui* ui);

void Start(Ui* ui);