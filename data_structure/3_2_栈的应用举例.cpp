#include "3_2_栈的应用举例.h"

//void convertion()
//{
//	SqStack S; int N, e;
//	InitStack(S);
//	scanf_s("%d", &N);
//	while (N) {
//		Push(S, N % 8);
//		N = N / 8;
//	}
//	while (!StackEmpty(S)) {
//		Pop(S, e);
//		printf("%d", e);
//	}
//}

void LineEdit()
{
	SqStack S; char c,e;
	InitStack(S);
	char ch = getchar();
	while (ch != EOF) {
		while (ch != EOF && ch != '\n') {
			switch (ch) {
			case '#': Pop(S, c); break;
			case '@': ClearStack(S); break;
			default: Push(S, ch); break;
			}
			ch = getchar();
		}
		while (!StackEmpty(S)) {
			Pop(S, e);
			printf("%c", e);
		}
		printf("\n");
		ClearStack(S);
		if (ch != EOF) ch = getchar();
	}
	DestroyStack(S);
}

int practice3_2_1() {
	//convertion();
	system("pause");
	return 0;
}

int practice3_2_2() {
	LineEdit();
	system("pause");
	return 0;
}
