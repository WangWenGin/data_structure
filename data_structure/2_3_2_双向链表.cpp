#include "Ë«ÏòÁ´±í.h"

void CreateList_DuL(DuLinkList &L, int n) {
	L = (DuLinkList)malloc(sizeof(DuLNode));
	L->prior = NULL; L->next = NULL;
	for (int i = 0; i < n; i++) {
		DuLinkList p = (DuLinkList)malloc(sizeof(DuLNode));
		scanf_s("%d", &p->data);
		p->next = L->next; 
		if (L->next) L->next->prior = p;
		p->prior = L; L->next = p;
	}
}

Status GetElem_DuL(DuLinkList L, int i, int &e) {
	DuLinkList p = L->next; int j = 1;
	while (p && j < i) {
		p = p->next; j++;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}

DuLinkList GetElemP_DuL(DuLinkList L, int i) {
	DuLinkList p = L->next; int j = 1;
	while (p && j < i) {
		p = p->next; j++;
	}
	return p;
}

Status ListInsert_DuL(DuLinkList &L, int i, int e) {
	DuLinkList p = GetElemP_DuL(L, i);
	if (!p) return ERROR;
	DuLinkList s = (DuLinkList)malloc(sizeof(DuLNode));
	s->data = e;
	s->prior = p->prior; 
	if (p->prior) p->prior->next = s;
	s->next = p; p->prior = s;
	return OK;
}

Status LinkDelete_DuL(DuLinkList &L, int i, int &e) {
	DuLinkList p = GetElemP_DuL(L, i);
	if (!p) return ERROR;
	e = p->data;
	p->prior->next = p->next; 
	if (p->next) p->next->prior = p->prior;
	free(p);
	return OK;
}

int practice2_3_2() {
	DuLinkList l;
	CreateList_DuL(l, 5);
	ListInsert_DuL(l, 2, 20);
	for (int i = 1; i <= 10; i++) {
		int e;
		GetElem_DuL(l, i, e);
		printf("%d\t", e);
	}
	int d;
	LinkDelete_DuL(l, 1, d);
	printf("%d\n", d);
	for (int i = 1; i <= 10; i++) {
		int e;
		GetElem_DuL(l, i, e);
		printf("%d\t", e);
	}
	system("pause");
	return 0;
}