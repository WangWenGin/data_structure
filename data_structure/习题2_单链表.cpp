#include "单链表.h"

//包含第2章的习题13-15、17-20、22-24、26、28、30

void CreateList_L_InBook(LinkList &L, int n) {
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = 0; i < n; i++) {
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf_s("%d", &p->data);
		p->next = L->next; L->next = p;
	}
}

Status GetElem_L_InBook(LinkList L, int i, int &e) {
	LinkList p = L->next; int j = 0;
	while (p && j < i) {
		p = p->next; j++;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}

Status ListInsert_L_InBook(LinkList &L, int i, int e) {
	//习题2.17带头结点的Insert算法，不带头结点的见2_3_1_单链表
	LinkList p = L; int j = 0;
	while (p && j < i - 1) { p = p->next; j++; }
	if (!p || j > i - 1) return ERROR;
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e; s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L_InBook(LinkList &L, int i, int &e) {
	//习题2.18带头结点的Delete算法，不带头结点的见2_3_1_单链表
	LinkList p = L; int j = 0;
	while (p->next && j < i - 1) { p = p->next; j++; }
	if (!(p->next) || j > i - 1) return ERROR;
	LinkList q = p->next; p->next = q->next;
	e = q->data; free(q);
	return OK;
}

int ListLocate_L(LinkList L, int x) {
	//习题2.13
	LinkList p = L->next; int i = 0;
	while (p) {
		i++;
		if (p->data == x) return i;
		p = p->next;
	}
	return 0;
}

int ListLength_L(LinkList L) {
	//习题2.14
	LinkList p = L->next; int i = 0;
	while (p) {i++; p = p->next;}
	return i;
}

Status ListExtend_L(LinkList ha, LinkList hb, LinkList &hc) {
	//习题2.15
	//假设m和n为L1和L2的正确长度且已知，时间复杂度为min(m, n)
	hc = (LinkList)malloc(sizeof(LNode));
	LinkList p, q;
	int m = ListLength_L(ha);
	int n = ListLength_L(hb);
	if (m <= n) { p = hc->next = ha->next; q = hb; }
	else {p = hc->next = hb->next, q = ha; }
	while (p->next) p = p->next;
	p->next = q->next; //ha改变了
	return OK;
}

int ListDeleteRange_IncrementalL(LinkList &L, int mink, int maxk) {
	//习题2.19，假设L为递增，返回删除元素的个数
	//时间复杂度O(n)，n为小于maxk的元素个数
	LinkList p = L, q, s; 
	int num = 0;
	while (p->next && p->next->data <= mink) p = p->next;
	if (!p->next) return 0;
	q = p->next;
	while (q && q->data < maxk) { 
		s = q; q = q->next; 
		p->next = q; free(s);
		num++;
	}
	return num;
}

int ListDuplicate_IncrementalL(LinkList &L) {
	//习题2.20，假设L为递增或递减，返回删除元素的个数
	//时间复杂度O(n)，n为元素个数
	LinkList p = L->next, q, s;
	int num = 0;
	while (p) {	
		q = p->next;
		while (q && p->data == q->data) {
			s = q; q = q->next;
			p->next = q; free(s);
			num++;
		}
		p = q;
	}
	return num;
}

void ListReverse_L(LinkList &L) {
	//习题2.22
	LinkList p = L->next, q = NULL, s;
	if (p) {
		q = p->next;
		p->next = NULL;
	}
	while (q) {
		s = q->next; q->next = p;
		p = q; q = s;
		
	}
	L->next = p;
}

void ListInterdigitate_L(LinkList L1, LinkList L2, LinkList &L3) {
	//习题2.23
	L3 = (LinkList)malloc(sizeof(LNode));
	L3->next = L2->next;
	LinkList p = L2, q = L1->next, s;
	while (q) { //L1和L2均发生了改变
		s = p->next; p->next = q;
		p = q; q = s;
	}
}

void ListMergeAndReverse_IncrementalL(LinkList L1, LinkList L2, LinkList &L3) {
	//习题2.24，假设L1和L2递增
	L3 = (LinkList)malloc(sizeof(LNode));
	LinkList p1 = L1->next, p2 = L2->next, q = NULL, s, t;
	while (p1 && p2) {
		if (p1->data <= p2->data) { s = p1->next; p1->next = q; q = p1; p1 = s; }
		else { s = p2->next; p2->next = q; q = p2; p2 = s; }
	}
	s = p1 ? p1 : p2;
	while (s) {
		t = s->next; s->next = q;
		q = s; s = t;
	}
	L3->next = q;
}

void ListIntersection_MonotoneIncrementalL(LinkList La, LinkList Lb, LinkList &Lc) {
	//习题2.26，假设La和Lb单调递增且无重复值
	Lc = (LinkList)malloc(sizeof(LNode)); Lc->next = NULL;
	LinkList pa = La->next, pb = Lb->next, q = Lc, s;
	while (pa && pb) {
		if (pa->data == pb->data) {
			s = (LinkList)malloc(sizeof(LNode));
			s->data = pa->data; s->next = NULL;
			q->next = s; q = s;
			pa = pa->next; pb = pb->next;
		}
		else {
			if (pa->data < pb->data) pa = pa->next;
			else pb = pb->next;
		}
	}
}

void ListIntersection_IncrementalL(LinkList La, LinkList Lb, LinkList &Lc) {
	//习题2.28，假设La和Lb递增且无重复值
	Lc = (LinkList)malloc(sizeof(LNode));
	LinkList pa = La, pb = Lb, s;
	int n = pa->next ? pa->next->data - 1 : NULL;
	while (pa->next && pb->next) {
		if (pa->next->data < pb->next->data || pa->next->data == n) {
			s = pa->next; pa->next = pa->next->next;
			free(s);
		}
		else{
			if (pa->next->data == pb->next->data) { n = pa->next->data; pa = pa->next; }
			else pb = pb->next;
		}
	}
	while (pa->next) { s = pa->next; pa->next = pa->next->next; }
	Lc = La;
}

void ListDeleteIntersection_IncrementalL(LinkList &La, LinkList Lb, LinkList Lc) {
	//习题2.30，假设La、Lb和Lc递增
	//时间复杂度O(n)
	LinkList pa = La, pb = Lb->next, pc = Lc->next, s;
	while (pb && pc) {
		if (pb->data == pc->data) {
			while (pa->next && pa->next->data < pb->data) pa = pa->next;
			if (!pa->next) break;
			while (pa->next->data == pb->data) {
				s = pa->next; pa->next = pa->next->next;
				free(s);
			}
			if (!pa->next) break;
			pb = pb->next; pc = pc->next;
		}
		else {
			if (pb->data < pc->data) pb = pb->next;
			else pc = pc->next;
		}
	}
}

int exercise2_13() {
	LinkList l;
	CreateList_L_InBook(l, 5);
	int e;
	for (int i = 0; i < 5; i++) { GetElem_L_InBook(l, i, e); printf("%d\t", e); }
	printf("\n%d\n", ListLocate_L(l, 1));
	system("pause");
	return 0;
}

int exercise2_14() {
	LinkList l;
	CreateList_L_InBook(l, 5);
	printf("\n%d\n", ListLength_L(l));
	system("pause");
	return 0;
}

int exercise2_15() {
	LinkList l1, l2, l3, p;
	CreateList_L_InBook(l1, 5);
	CreateList_L_InBook(l2, 4);
	ListExtend_L(l1, l2, l3);
	p = l3;
	while (p->next) {p = p->next; printf("\n%d", p->data);}
	system("pause");
	return 0;
}

int exercise2_19() {
	LinkList l, p;
	CreateList_L_InBook(l, 5);
	printf("\n%d\n", ListDeleteRange_IncrementalL(l, 1, 7));
	p = l;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}

int exercise2_20() {
	LinkList l, p;
	CreateList_L_InBook(l, 10);
	printf("\n%d\n", ListDuplicate_IncrementalL(l));
	p = l;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}

int exercise2_22() {
	LinkList l, p;
	CreateList_L_InBook(l, 5);	
	p = l;
	while (p->next) { p = p->next; printf("%d\t", p->data); }
	ListReverse_L(l); printf("\n");
	p = l;
	while (p->next) { p = p->next; printf("%d\t", p->data); }
	system("pause");
	return 0;
}

int exercise2_23() {
	LinkList l1, l2, l3, p;
	CreateList_L_InBook(l1, 5);
	CreateList_L_InBook(l2, 4);
	ListInterdigitate_L(l1, l2, l3);
	p = l3;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}

int exercise2_24() {
	LinkList l1, l2, l3, p;
	CreateList_L_InBook(l1, 5);
	CreateList_L_InBook(l2, 4);
	ListMergeAndReverse_IncrementalL(l1, l2, l3);
	p = l3;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}

int exercise2_26() {
	LinkList l1, l2, l3, p;
	CreateList_L_InBook(l1, 5);
	CreateList_L_InBook(l2, 4);
	ListIntersection_MonotoneIncrementalL(l1, l2, l3);
	p = l3;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}

int exercise2_28() {
	LinkList l1, l2, l3, p;
	CreateList_L_InBook(l1, 5);
	CreateList_L_InBook(l2, 4);
	ListIntersection_IncrementalL(l1, l2, l3);
	p = l3;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}

int exercise2_30() {
	LinkList l1, l2, l3, p;
	CreateList_L_InBook(l1, 5);
	CreateList_L_InBook(l2, 5);
	CreateList_L_InBook(l3, 5);
	ListDeleteIntersection_IncrementalL(l1, l2, l3);
	p = l1;
	while (p->next) { p = p->next; printf("\n%d", p->data); }
	system("pause");
	return 0;
}
