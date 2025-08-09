#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/* === ����Ʈ ���� === */
/* �� ����Ʈ ���� */
LLNode* ll_create() {
	return NULL; // head�� �ƹ� ��嵵 ����Ű�� �ʴ� ����
}

/* === ���� === */
/* ���ο� ��� ���� */
static LLNode* ll_new_node(int value) { 
	LLNode* n = (LLNode*)malloc(sizeof(LLNode));
	if (!n) // �޸� ���� ��
		return NULL; // NULL�� ��ȯ
	
	n->data = value; // �� ���� ��
	n->next = NULL; // next = NULL�� �ʱ�ȭ
	return n;
}

/* ������ ����� next�� NULL���� �˻� */
static void ll_check_invariants(const LLNode* head) { 
	if (!head)
		return;
	
	const LLNode* cur = head;
	while (cur->next)
		cur = cur->next;
	
	if (cur->next != NULL)
		printf("invariant failed: last->next must be NULL\n");
}

/* �� �� ���� */
void ll_push_front(LLNode** head, int value) {
	if (!head)
		return;
	
	LLNode* n = ll_new_node(value);
	
	if (!n)
		return;
	
	n->next = *head; // �� ����� next�� ���� head�� ����
	*head = n; // head ����
	
	ll_check_invariants(*head);
}

/* �� �� ���� */
void ll_push_back(LLNode** head, int value) {
	if (!head)
		return;

	LLNode* n = ll_new_node(value);

	if (!n)
		return;

	if (!*head) { // �� ����Ʈ�� ��� �� ��尡 head
		*head = n;
		ll_check_invariants(*head);
		return;
	}

	LLNode* cur = *head;
	while (cur->next) // ������ ��� ã�� ������ �ݺ�
		cur = cur->next;

	cur->next = n;

	ll_check_invariants(*head);
}

/* === ���� === */
/* �� �� ���� */
int ll_pop_front(LLNode** head, int* out) {
	if (!head || !*head) // �� ����Ʈ��
		return 0; // ���� -> 0 ��ȯ

	LLNode* first = *head;

	if (out) 
		*out = first->data;
	
	*head = first->next; // ���� ��带 head�� ����
	
	free(first);
	
	ll_check_invariants(*head);
	return 1;
}

/* �� �� ���� */
int ll_pop_back(LLNode** head, int* out) {
	if (!head || !*head)
		return 0;

	if (!(*head)->next) { // ��尡 �ϳ����� ���
		if (out)
			*out = (*head)->data;
		
		free(*head);
		
		*head = NULL;
		
		return 1;
	}

	LLNode* prev = *head;

	while (prev->next && prev->next->next) { // ������ ������ �ݺ�
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

/* === �� Ž�� === */
LLNode* ll_find(LLNode* head, int target) {
	LLNode* cur = head;

	while (cur) { // ���������� Ž���ؼ� ��ġ�ϴ� ù ��° ��� ��ȯ
		if (cur->data == target)
			return cur;
		cur = cur->next;
	}

	return NULL;
}

/* === ��ü ��� === */
void ll_print(const LLNode* head) { // [a -> b -> c] �������� ���
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

/* === ����Ʈ �޸� ���� === */
void ll_free(LLNode* head) {
	while (head) {
		LLNode* next = head->next;
		free(head);
		head = next;
	}
}
