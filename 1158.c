#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
typedef struct _node {
	int data;
	struct _node* next;
} Node;
 
typedef struct _List {
	Node* head;
	Node* tail;
	Node* cur;
	Node* before;
} CList;
 
typedef CList List;
 
void Init(List* plist);
void Insert(List* plist, int data);
void Cur_Init(List* plist);		// Shift를 하기 전 cur과 before가 tail을 가리키도록 초기화
int Shift(List* plist, int K);	// cur과 before을 이동시키는 함수
void Remove(List* plist);	// Shift 함수가 호출된 뒤 cur이 가리키는 node를 삭제
 
int main() {
	int N, K, i;
	scanf("%d %d", &N, &K);
 
	List list;
	Init(&list);
 
	for (i = 1; i <= N; i++) {
		Insert(&list, i);
	}
 
	Cur_Init(&list);
 
	printf("<%d", Shift(&list, K));
	Remove(&list);
 
	for (i = 0; i < N - 1; i++) {
		printf(", %d", Shift(&list, K));
		Remove(&list);
	}
	printf(">");
	return 0;
}
 
void Init(List* plist) {
	plist->head = NULL;
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
}
 
void Insert(List* plist, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
 
	if (plist->head == NULL) {	// 큐가 비어있는 상황
		plist->head = newNode;
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
		plist->tail = newNode;
	}
}
 
void Cur_Init(List* plist) {
	plist->cur = plist->tail;
	plist->before = plist->tail;
}
 
int Shift(List* plist, int K) {
	plist->cur = plist->cur->next;	// before과 한 칸 차이를 만들기 위해 cur을 따로 한 번 이동시킴
	for (int i = 0; i < K - 1; i++) {	// K > 1인 경우 cur과 before 이동
		plist->before = plist->cur;
		plist->cur = plist->cur->next;
	}
	return plist->cur->data;
}
 
void Remove(List* plist) {
	Node* rpos = plist->cur;
	if (rpos == plist->tail) {	// tail을 삭제하는 경우
		if (plist->tail == plist->tail->next) {	// 큐에 원소가 단 하나만 남았을 때 (사실 이 경우는 노드를 또 추가하지 않을 것이기 때문에 이 문제에선 불필요함)
			plist->head = NULL;
			plist->tail = NULL;
		}
		else
			plist->tail = plist->before;	// tail을 삭제하므로 tail의 위치를 옮겨줌
	}
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;
	free(rpos);
}