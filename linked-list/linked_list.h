#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* ���� ���� ����Ʈ ��� */
typedef struct LLNode {
	int data;
	struct LLNode* next;
} LLNode;

/* === ����Ʈ ���� === */
// �� ����Ʈ�� ���� �ּ�(head) ��ȯ
LLNode* ll_create();

/* === ���� === */
/* ���ο� ��� ���� */
static LLNode* ll_new_node(int value);

/* ������ ����� next�� NULL���� �˻� */
static void ll_check_invariants(const LLNode* head);

/* �� �� ���� */
// head�� �ٲ� �� �����Ƿ�, ���� ������ ���
void ll_push_front(LLNode** head, int value);

/* �� �� ���� */
void ll_push_back(LLNode** head, int value);

/* === ���� === */
/* �� �� ���� */
// ���� �� *out�� ������ ���� & 1 ��ȯ / ����(�� ����Ʈ) �� 0 ��ȯ
int ll_pop_front(LLNode** head, int* out);

/* �� �� ����*/
// ���� �� *out�� ������ ���� & 1 ��ȯ / ����(�� ����Ʈ) �� 0 ��ȯ
int ll_pop_back(LLNode** head, int* out);

/* === �� Ž�� === */
// ù ��Ī ���� ������ ��ȯ, ������ NULL
LLNode* ll_find(LLNode* head, int target);

/* === ��ü ��� === */
// [a -> b -> c] �������� ���
void ll_print(const LLNode* head);

/* === ����Ʈ �޸� ���� === */
void ll_free(LLNode* head);

#endif