#ifndef LINKED_LIST_H // �ߺ� ���� ���� ����
#define LINKED_LIST_H

/* ===== ���� ���� ����Ʈ�� ��� ===== */
typedef struct LLNode {
    int data; // ���� ������ ����
    struct LLNode* next; // ���� ��带 ����ų ������
} LLNode;

/* ===== ����Ʈ �����̳�: head�� tail ������ ���� ===== */
typedef struct LLP {
    LLNode* head; // head pointer
    LLNode* tail; // tail pointer
} LLP;

/* ===== ����Ʈ ���� ===== */
LLP ll_create();

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ����Ʈ�� �� head==NULL && tail==NULL���� �˻�
// �� ����Ʈ�� �ƴ� �� tail�� ������ ����̰�, tail->next==NULL���� �˻�
static void ll_check_invariants(const LLP* list);

/* ===== �� ��/�� ���� ===== */
void ll_push_front(LLP* list, int value); // �� �� ����
void ll_push_back(LLP* list, int value); // �� �� ����

/* ===== �� ��/�� ���� ===== */
int ll_pop_front(LLP* list, int* out); // �� �� ����: ���� �� 1, ���� �� 0
int ll_pop_back(LLP* list, int* out); // �� �� ����: ���� �� 1, ���� �� 0

/* ===== �� Ž�� ===== */
LLNode* ll_find(const LLP* list, int target); // ������ NULL ��ȯ

/* ===== ��ü ���: [a -> b -> c]\n �������� ��� ===== */
void ll_print(const LLP* list);

/* ===== �޸� ����: ��� ��� ���� + ���/���� �ʱ�ȭ ===== */
void ll_free(LLP* list);

/* ===== ����Ʈ�� ����ִ��� Ȯ��: main.c���� ��� ===== */
int ll_is_empty(const LLP* list); // ��������� 1, �ƴϸ� 0

#endif