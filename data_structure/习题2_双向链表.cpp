#include "双向链表.h"

//包含第2章的习题37

void Cross_DuL(DuLinkList &L) {
	//不会
	DuLinkList p = L, q;
	while (p->next != L) {
		q = p->next; 
		p->next = p->next->next; 
	}
}

typedef struct FreqDuLNode {
	int data, freq;
	struct FreqDuLNode *prior;
	struct FreqDuLNode *next;
}FreqDuLNode, *FreqDuLinkList;

void CreateList_FreqDuL(FreqDuLinkList &L, int n) {
	L = (FreqDuLinkList)malloc(sizeof(FreqDuLNode));
	L->prior = NULL; L->next = NULL; L->freq = 0;
	FreqDuLinkList p = NULL, q = L;
	for (int i = 0; i < n; i++) {
		p = (FreqDuLinkList)malloc(sizeof(FreqDuLNode));
		scanf_s("%d", &p->data);
		q->next = p; p->prior = q;
		p->next = NULL; p->freq = 0;
		q = q->next;
	}
	p->next = L; L->prior = p;
}



int Locate_FreqDuL(FreqDuLinkList &L, int x) {
	//假设L的节点按freq降序排列
	int i = 1;
	FreqDuLinkList p = L->next, q, s; 
	while (p != L) {
		if (p->data == x) { 
			p->freq++;
			q = p->prior;
			while (q != L && q->freq < p->freq) q = q->prior;
			p->prior->next = p->next; p->next->prior = p->prior;
			s = q->next;
			p->prior = q; q->next = p;
			p->next = s; s->prior = p;
			return i; 
		}
		else { p = p->next; i++; }
	}
	return 0;
}

int exercise2_38() {
	FreqDuLinkList l, p;
	CreateList_FreqDuL(l, 10);
	p = l;
	while (p->next != l) { p = p->next; printf("%d\t", p->data); }
	printf("%d\t", Locate_FreqDuL(l, 4));
	printf("%d\t", Locate_FreqDuL(l, 4));
	printf("%d\t", Locate_FreqDuL(l, 4));
	printf("%d\t", Locate_FreqDuL(l, 2));
	printf("%d\t", Locate_FreqDuL(l, 2));
	p = l;
	printf("\n");
	while (p->next != l) { p = p->next; printf("%d\t", p->data); }
	system("pause");
	return 0;
}