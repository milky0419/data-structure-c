#ifndef DOUBLY_LINKED_LIST_H // �ߺ� ���� ���� ����
#define DOUBLY_LINKED_LIST_H

/* ===== ���� ���� ����Ʈ�� ��� ===== */
typedef struct DLLNode {
    int data; // ������ ������ ����
    struct DLLNode* prev; // ���� ��带 ����ų ������
    struct DLLNode* next; // ���� ��带 ����ų ������
} DLLNode;

/* ===== ����Ʈ �����̳�: head�� tail ������ ���� ===== */
typedef struct DLLP {
    DLLNode* head; // head pointer
    DLLNode* tail; // tail pointer
} DLLP;

/* ===== ����Ʈ ���� ===== */
DLLP dll_create();

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ����Ʈ�� �� head==NULL && tail==NULL���� �˻�
// �� ����Ʈ�� �ƴ� �� head->prev==NULL && tail->next==NULL���� �˻�
// ����� ������ �ùٸ��� �˻� (node->next->prev == node)
void dll_check_invariants(const DLLP* list);

/* ===== ����Ʈ�� ����ִ��� Ȯ�� ===== */
int dll_is_empty(const DLLP* list); // ��������� 1, �ƴϸ� 0

/* ===== �� ��/�� ���� ===== */
int dll_push_front(DLLP* list, int value); // �� �� ����: ���� �� 1, ���� �� 0 ��ȯ
int dll_push_back(DLLP* list, int value); // �� �� ����: ���� �� 1, ���� �� 0 ��ȯ

/* ===== �� ��/�� ���� ===== */
int dll_pop_front(DLLP* list, int* out); // �� �� ����: ���� �� 1, ���� �� 0 ��ȯ
int dll_pop_back(DLLP* list, int* out); // �� �� ����: ���� �� 1, ���� �� 0 ��ȯ

/* ===== �� Ž�� ===== */
DLLNode* dll_find(const DLLP* list, int target); // ������ NULL ��ȯ

/* ===== ��ü ���: �ա��, �ڡ�� ����� ��� ===== */
void dll_print_forward(const DLLP* list); // �տ��� �ڷ� ���
void dll_print_backward(const DLLP* list); // �ڿ��� ������ ���

/* ===== �޸� ����: ��� ��� ���� + ���/���� �ʱ�ȭ ===== */
void dll_free(DLLP* list);

#endif
