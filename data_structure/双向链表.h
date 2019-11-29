#pragma once
#include "data_structure.h"

typedef struct DuLNode {
	int data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;
