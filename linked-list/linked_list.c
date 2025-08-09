#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/* === 리스트 생성 === */
/* 빈 리스트 생성 */
LLNode* ll_create() {
	return NULL; // head가 아무 노드도 가리키지 않는 상태
}

/* === 삽입 === */
/* 새로운 노드 생성 */
static LLNode* ll_new_node(int value) { 
	LLNode* n = (LLNode*)malloc(sizeof(LLNode));
	if (!n) // 메모리 부족 시
		return NULL; // NULL로 반환
	
	n->data = value; // 값 결정 후
	n->next = NULL; // next = NULL로 초기화
	return n;
}

/* 마지막 노드의 next가 NULL인지 검사 */
static void ll_check_invariants(const LLNode* head) { 
	if (!head)
		return;
	
	const LLNode* cur = head;
	while (cur->next)
		cur = cur->next;
	
	if (cur->next != NULL)
		printf("invariant failed: last->next must be NULL\n");
}

/* 맨 앞 삽입 */
void ll_push_front(LLNode** head, int value) {
	if (!head)
		return;
	
	LLNode* n = ll_new_node(value);
	
	if (!n)
		return;
	
	n->next = *head; // 새 노드의 next를 기존 head로 연결
	*head = n; // head 변경
	
	ll_check_invariants(*head);
}

/* 맨 뒤 삽입 */
void ll_push_back(LLNode** head, int value) {
	if (!head)
		return;

	LLNode* n = ll_new_node(value);

	if (!n)
		return;

	if (!*head) { // 빈 리스트일 경우 새 노드가 head
		*head = n;
		ll_check_invariants(*head);
		return;
	}

	LLNode* cur = *head;
	while (cur->next) // 마지막 노드 찾을 때까지 반복
		cur = cur->next;

	cur->next = n;

	ll_check_invariants(*head);
}

/* === 삭제 === */
/* 맨 앞 삭제 */
int ll_pop_front(LLNode** head, int* out) {
	if (!head || !*head) // 빈 리스트면
		return 0; // 실패 -> 0 반환

	LLNode* first = *head;

	if (out) 
		*out = first->data;
	
	*head = first->next; // 다음 노드를 head로 설정
	
	free(first);
	
	ll_check_invariants(*head);
	return 1;
}

/* 맨 뒤 삭제 */
int ll_pop_back(LLNode** head, int* out) {
	if (!head || !*head)
		return 0;

	if (!(*head)->next) { // 노드가 하나뿐인 경우
		if (out)
			*out = (*head)->data;
		
		free(*head);
		
		*head = NULL;
		
		return 1;
	}

	LLNode* prev = *head;

	while (prev->next && prev->next->next) { // 마지막 노드까지 반복
		prev = prev->next;
	}

	LLNode* last = prev->next;

	if (out)
		*out = last->data;

	free(last);

	prev->next = NULL;

	ll_check_invariants(*head);
	return 1;
}

/* === 값 탐색 === */
LLNode* ll_find(LLNode* head, int target) {
	LLNode* cur = head;

	while (cur) { // 순차적으로 탐색해서 일치하는 첫 번째 노드 반환
		if (cur->data == target)
			return cur;
		cur = cur->next;
	}

	return NULL;
}

/* === 전체 출력 === */
void ll_print(const LLNode* head) { // [a -> b -> c] 형식으로 출력
	const LLNode* cur = head;
	printf("[");
	while (cur) {
		printf("%d", cur->data);
		if (cur->next)
			printf(" -> ");
		cur = cur->next;
	}
	printf("]\n");
}

/* === 리스트 메모리 해제 === */
void ll_free(LLNode* head) {
	while (head) {
		LLNode* next = head->next;
		free(head);
		head = next;
	}
}
