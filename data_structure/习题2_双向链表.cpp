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