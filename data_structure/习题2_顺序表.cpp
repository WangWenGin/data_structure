#include "顺序表.h"

//包含第2章的习题10-12、21、25、27、29

Status InitList_Sq_InBook(SqList &L) {
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status ListInsert_Sq_InBook(SqList &L, int i, int e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length >= L.listsize) {
		int *newbase = (int *)realloc(L.elem,
			(L.listsize + LISTINCREMENT) * sizeof(int));
		if (!newbase) exit(OVERFLOW);
		L.listsize += LISTINCREMENT;
	}
	int *q = &(L.elem[i - 1]);
	for (int *p = &(L.elem[L.length - 1]); p >= q; p--) *(p + 1) = *p;
	*q = e;
	L.length++;
	return OK;
}

Status ListDelete_Sq_InBook(SqList &L, int i, int &e) {
	if (i < 1 || i >= L.length) return ERROR;
	int *p = &(L.elem[i - 1]);
	e = *p;
	int *q = L.elem + L.length - 1;
	for (++p; p <= q; ++p) *(p - 1) = *p;
	L.length--;
	return OK;
}

Status DeleteK_Sq(SqList &a, int i, int k) {
	//习题2.10
	if (i < 1 || k < 0 || i + k > a.length) return INFEASIBIE;
	int *p = &(a.elem[i - 1]);
	int *q = a.elem + a.length - k;
	for (; p <= q; p++) *p = *(p + k);
	a.length -= k;
	return OK;
}

Status ListInsert_IncrementalSq(SqList &L, int e) {
	//习题2.11，假设L递增，先用二分法确定位置，再调ListInsert_Sq_InBook
	if (e <= L.elem[0]) return ListInsert_Sq_InBook(L, 1, e);
	if (e >= L.elem[L.length - 1]) return ListInsert_Sq_InBook(L, L.length + 1, e);
	int lower = 0, higher = L.length - 1, avg;
	while (higher - lower != 1) {
		avg = (lower + higher) / 2;
		if (e >= L.elem[avg]) lower = avg;
		else higher = avg;
	}
	return ListInsert_Sq_InBook(L, higher, e);
}

int ListCompare_Sq(SqList &L1, SqList & L2) {
	//习题2.12，若L1>L2，返回1，若L1=L2，返回0，否则返回-1。
	for (int i = 0; i < L1.length; i++) {
		if (i == L2.length) return 1; //A`不为空，B`为空
		if (L1.elem[i] == L2.elem[i]) continue;
		if (L1.elem[i] < L2.elem[i]) return -1; //均不为空，比较首元
		else return 1;
	}
	if (L1.length == L2.length) return 0; //均为空
	else return -1; //A`为空，B`不为空
}

void ListReverse_Sq(SqList &L) {
	//习题2.21
	int i, temp;
	for (i = 0; i < L.length / 2; i++) {
		temp = L.elem[i]; 
		L.elem[i] = L.elem[L.length - i - 1]; 
		L.elem[L.length - i - 1] = temp;
	}
}

void ListIntersection_MonotoneIncrementalSq(SqList La, SqList Lb, SqList &Lc) {
	//习题2.25，假设La和Lb单调递增且无重复值
	Lc.listsize = La.listsize <= Lb.listsize ? La.listsize : Lb.listsize;
	int *pc = Lc.elem = (int *)malloc(Lc.listsize * sizeof(int));
	if (!Lc.elem) exit(OVERFLOW);
	Lc.length = 0;
	int *pa = La.elem, *pa_last = La.elem + La.length - 1;
	int *pb = Lb.elem, *pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb) { 
			if (*pa == *pb) { *pc++ = *pb++; Lc.length++; }
			pa++;
		}
		else pb++;
	}
}

void ListIntersection_IncrementalSq(SqList La, SqList Lb, SqList &Lc) {
	//习题2.27，假设La和Lb递增且无重复值
	Lc.listsize = La.listsize <= Lb.listsize ? La.listsize : Lb.listsize;
	Lc.length = 0;
	int *pa = La.elem, *pa_last = La.elem + La.length - 1;
	int *pb = Lb.elem, *pb_last = Lb.elem + Lb.length - 1;
	int *q;
	int n = La.length > 0 ? *pa - 1 : NULL;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa < *pb || *pa == n) { 
			for (q = pa + 1; q <= pa_last; q++) *(q - 1) = *q; 
			La.length--; pa_last--;
		}
		else {
			if (*pa == *pb) { pa++; n = *pa; }
			else pb++;
		}
	}
	Lc = La;
}

void ListDeleteIntersection_IncrementalSq(SqList &La, SqList Lb, SqList Lc) {
	//习题2.29，假设La、Lb和Lc递增
	//时间复杂度O(n^2)
	int *pa = La.elem, *pa_last = La.elem + La.length - 1;
	int *pb = Lb.elem, *pb_last = Lb.elem + Lb.length - 1;
	int *pc = Lc.elem, *pc_last = Lc.elem + Lc.length - 1;
	int *q;
	while (pb <= pb_last && pc <= pc_last) {
		if (*pb == *pc) {
			while (*pa < *pb && pa <= pa_last) pa++;
			if (pa > pa_last) break;
			while (*pa == *pb) {
				for (q = pa + 1; q <= pa_last; q++) *(q - 1) = *q;
				La.length--; pa_last--;
			}
			if (pa > pa_last) break;
			pb++; pc++;
		}
		else {
			if (*pb < *pc) pb++;
			else pc++;
		}
	}
}

int exercise2_10() {
	SqList l;
	InitList_Sq_InBook(l);
	for (int i = 1; i <= 10; i++) ListInsert_Sq_InBook(l, 1, i);
	for (int i = 0; i < l.length; i++) printf("%d\t", l.elem[i]);
	DeleteK_Sq(l, 4, 3);
	for (int i = 0; i < l.length; i++) printf("%d\t", l.elem[i]);
	system("pause");
	return 0;
}

int exercise2_11() {
	SqList l;
	InitList_Sq_InBook(l);
	for (int i = 10; i > 0; i--) ListInsert_Sq_InBook(l, 1, i);
	ListInsert_IncrementalSq(l, -5);
	for (int i = 0; i < l.length; i++) printf("%d\t", l.elem[i]);
	system("pause");
	return 0;
}

int exercise2_12() {
	SqList l1, l2;
	InitList_Sq_InBook(l1);
	InitList_Sq_InBook(l2);
	for (int i = 10; i > 0; i--) ListInsert_Sq_InBook(l1, 1, i);
	for (int i = 10; i > 0; i--) ListInsert_Sq_InBook(l2, 1, i);
	printf("%d\n", ListCompare_Sq(l2, l1));
	system("pause");
	return 0;
}

int exercise2_21() {
	SqList l;
	InitList_Sq_InBook(l);
	for (int i = 9; i > 0; i--) ListInsert_Sq_InBook(l, 1, i);
	for (int i = 0; i < l.length; i++) printf("%d\t", l.elem[i]);
	ListReverse_Sq(l);
	for (int i = 0; i < l.length; i++) printf("%d\t", l.elem[i]);
	system("pause");
	return 0;
}

int exercise2_25() {
	SqList la, lb, lc;
	InitList_Sq_InBook(la);
	for (int i = 9; i > -5; i--) ListInsert_Sq_InBook(la, 1, i);
	InitList_Sq_InBook(lb);
	for (int i = 19; i > 0; i-=2) ListInsert_Sq_InBook(lb, 1, i);
	ListIntersection_MonotoneIncrementalSq(la, lb, lc);
	printf("%d\n", lc.length);
	for (int i = 0; i < lc.length; i++) printf("%d\t", lc.elem[i]);
	system("pause");
	return 0;
}

int exercise2_27() {
	SqList la, lb, lc;
	InitList_Sq_InBook(la);
	for (int i = 9; i > -5; i--) ListInsert_Sq_InBook(la, 1, i / 2);
	InitList_Sq_InBook(lb);
	for (int i = 19; i > 0; i -= 2) ListInsert_Sq_InBook(lb, 1, i / 2);
	ListIntersection_IncrementalSq(la, lb, lc);
	printf("%d\n", lc.length);
	for (int i = 0; i < lc.length; i++) printf("%d\t", lc.elem[i]);
	system("pause");
	return 0;
}

int exercise2_29() {
	SqList la, lb, lc;
	InitList_Sq_InBook(la);
	for (int i = 19; i > -5; i--) ListInsert_Sq_InBook(la, 1, i / 2);
	for (int i = 0; i < la.length; i++) printf("%d\t", la.elem[i]);
	printf("\n");
	InitList_Sq_InBook(lb);
	for (int i = 19; i > 0; i -= 2) ListInsert_Sq_InBook(lb, 1, i / 2);
	for (int i = 0; i < lb.length; i++) printf("%d\t", lb.elem[i]);
	printf("\n");
	InitList_Sq_InBook(lc);
	for (int i = 9; i > -10; i -= 1) ListInsert_Sq_InBook(lc, 1, i / 2);
	for (int i = 0; i < lc.length; i++) printf("%d\t", lc.elem[i]);
	printf("\n");
	ListDeleteIntersection_IncrementalSq(la, lb, lc);
	printf("%d\n", la.length);
	for (int i = 0; i < la.length; i++) printf("%d\t", la.elem[i]);
	system("pause");
	return 0;
}
