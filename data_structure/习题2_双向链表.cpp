#include "˫������.h"

//������2�µ�ϰ��37

void Cross_DuL(DuLinkList &L) {
	//����
	DuLinkList p = L, q;
	while (p->next != L) {
		q = p->next; 
		p->next = p->next->next; 
	}
}