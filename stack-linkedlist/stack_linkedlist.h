#ifndef STACK_LINKEDLIST_H // �ߺ� ���� ���� ����
#define STACK_LINKEDLIST_H

/* ===== ���� ����Ʈ ��� ������ ��� ===== */
typedef struct SLNode {
    int data; // ������ ������ ����
    struct SLNode* next; // ���� ��带 ����ų ������
} SLNode;

/* ===== ���� �����̳�: top ������ ���� ===== */
typedef struct SLP {
    SLNode* top; // ������ �ֻ�� ��带 ����Ű�� ������
} SLP;

/* ===== ���� ���� ===== */
SLP sl_create(); // �� ���� ���� �� �ʱ�ȭ

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ������ �� top==NULL���� �˻�
// ���� ����Ʈ�� ���Ἲ �˻� (NULL üũ)
static void sl_check_invariants(const SLP* stack);

/* ===== ���� �⺻ ���� ===== */
int sl_push(SLP* stack, int value); // ������ ����: ���� �� 1, ���� �� 0
int sl_pop(SLP* stack, int* out); // ������ ���� �� ��ȯ: ���� �� 1, ���� �� 0
int sl_peek(const SLP* stack, int* out); // �ֻ�� Ȯ��: ���� �� 1, ���� �� 0

/* ===== ���� ���� Ȯ�� ===== */
int sl_is_empty(const SLP* stack); // ��� ������ 1, �ƴϸ� 0
int sl_size(const SLP* stack); // ���� ���ÿ� ����� ��� ���� ��ȯ

/* ===== ���� ��� ===== */
void sl_print(const SLP* stack); // ���� ���� ��� (top -> bottom ����)

/* ===== �޸� ����: ��� ��� ���� + top �ʱ�ȭ ===== */
void sl_free(SLP* stack);

#endif