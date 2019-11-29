#include "单链表.h"

void CreateList_L(LinkList &L, int n) {
	L = (LinkList)malloc(sizeof(LNode));
	scanf_s("%d", &L->data);
	LinkList p = L;
	for (int i = 1; i < n; i++) {
		LinkList q = (LinkList)malloc(sizeof(LNode));
		scanf_s("%d", &q->data);
		p->next = q; p = q;
	}
	p->next = NULL;
}

Status GetElem_L(LinkList L, int i, int &e) {
	LinkList p = L; int j = 0;
	while (p && j < i) {
		p = p->next; j++;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}

Status ListInsert_L(LinkList &L, int i, int e) {
	//习题2.17不带头结点的Insert算法
	if (i == 0) { 
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->data = e; s->next = L;
		L = s;
		return OK; }
	LinkList p = L; int j = 0;
	while (p && j < i - 1) {p = p->next; j++;}
	if (!p || j > i - 1) return ERROR;
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e; s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList &L, int i, int &e) {
	//习题2.18不带头结点的Delete算法
	LinkList p = L; 
	if (i == 0) { e = L->data; L = L->next; free(p); return OK; }
	int j = 0;
	while (p && j < i - 1) {p = p->next; j++;}
	if (!p || j > i - 1) return ERROR;
	else {
		LinkList q = p->next;
		e = q->data; p->next = q->next;
		free(q);
	}
	return OK;
}

int practice2_3_1(){
	LinkList l;
	CreateList_L(l, 5);
	ListInsert_L(l, 2, 20);
	for (int i = 0; i <= 10; i++) {
		int e;
		GetElem_L(l, i, e);
		printf("%d\t", e);
	}
	int d;
	ListDelete_L(l, 2, d);
	printf("\n%d\n", d);
	for (int i = 0; i <= 10; i++) {
		int e;
		GetElem_L(l, i, e);
		printf("%d\t", e);
	}
	system("pause");
	return 0;
}