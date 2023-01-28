#include <stdio.h>

#define MAX_LENGTH 100

typedef struct List{
	int data[MAX_LENGTH];
	int size;
}List;

//tao rong
void make_null_list(List *L){
	L->size=0;
}

//chen cuoi
void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}

//lay 1 ptu trong ds tai vtri i
int element_at(List L, int i){
	return L.data[i-1];
}

void print_list(List N){
	for(int i=1;i<=N.size;++i){
		printf("%d ", element_at(N, i));
	}
	printf("\n");
}

void sort(List *pL){
	if(pL->size == 0){
		return;
	}
	for(int i= element_at(*pL, 1); i<pL->size-1;++i){
		for(int j = i+1; j<pL->size;++j){
			if(element_at(*pL,i)>element_at(*pL,j)){
				int temp = element_at(*pL, i);
				pL->data[i] = pL->data[j];
				pL->data[j] = temp;
			}
		}
	}
}
