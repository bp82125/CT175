#include <stdio.h>

#define ElementType int

#define MAX_N 100

typedef struct List{
	ElementType data[100];
	int size;
}List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, ElementType x){
	pL->data[pL->size] = x;
	pL->size++;
}

ElementType element_at(List *pL, int i){
	return pL->data[i-1];
}

void copy_list(List *pL1, List *pL2){
	make_null(pL1);
	pL1->size = pL2->size;
	for(int i = 0; i < pL2->size; ++i){
		pL1->data[i] = pL2->data[i];
	}
}

void reverse(List *pL){
	for(int i = 0; i<pL->size/2;++i){
		ElementType temp = pL->data[i];
		pL->data[i] = pL->data[pL->size - 1 - i];
		pL->data[pL->size - 1 - i] = temp;
	}
}

void print_list(List *pL){
	for(int i=0;i<pL->size;++i){
		printf("%d ", pL->data[i]);
	}
	printf("\n");
}

int emptyList(List *pL){
	return pL->size == 0;
}
