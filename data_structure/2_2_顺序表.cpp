#include "Ë³Ðò±í.h"

Status InitList_Sq(SqList &L) {
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status ListInsert_Sq(SqList &L, int i, int e) {
	if (i < 0 || i > L.length) return ERROR;
	if (L.length >= L.listsize) {
		int *newbase = (int *)realloc(L.elem, 
			(L.listsize + LISTINCREMENT) * sizeof(int));
		if (!newbase) exit(OVERFLOW);
		L.listsize += LISTINCREMENT;
	}
	int *q = &(L.elem[i]);
	for(int *p = &(L.elem[L.length - 1]); p >= q; p--) *(p + 1) = *p;
	*q = e;
	L.length++;
	return OK;
}

Status ListDelete_Sq(SqList &L, int i, int &e) {
	if (i < 0 || i >= L.length) return ERROR;
	e = L.elem[i];
	for (int *p = &(L.elem[i + 1]); p  <= &(L.elem[L.length - 1]); p++) *(p - 1) = *p;
	L.length--;
	return OK;
}

int practice2_2(){
	SqList l;
	if (InitList_Sq(l)) printf("%p\n", l.elem);
	ListInsert_Sq(l, 0, 10);
	for (int i = 0; i < l.length; i++) printf("%p: %d\n", &l.elem[i], l.elem[i]);
	ListInsert_Sq(l, 1, 100);
	for (int i = 0; i < l.length; i++) printf("%p: %d\n", &l.elem[i], l.elem[i]);
	int e;
	ListDelete_Sq(l, 0, e);
	for (int i = 0; i < l.length; i++) printf("%p: %d\n", &l.elem[i], l.elem[i]);
	system("pause");
	return 0;
}