#ifndef QUEUE_LINKEDLIST_H // �ߺ� ���� ���� ����
#define QUEUE_LINKEDLIST_H

/* ===== ���� ����Ʈ ��� ť�� ��� ===== */
typedef struct QLNode {
    int data; // ������ ������ ����
    struct QLNode* next; // ���� ��带 ����ų ������
} QLNode;

/* ===== ť �����̳�: front�� rear ������ ���� ===== */
typedef struct QLP {
    QLNode* front; // ť�� ���� ��带 ����Ű�� ������ (dequeue ��ġ)
    QLNode* rear; // ť�� ���� ��带 ����Ű�� ������ (enqueue ��ġ)
} QLP;

/* ===== ť ���� ===== */
QLP ql_create(); // �� ť ���� �� �ʱ�ȭ

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ť�� �� front==NULL && rear==NULL���� �˻�
// �� ť�� �ƴ� �� front�� rear�� �ùٸ��� ����Ǿ� �ִ��� �˻�
// ���� ����� �� front==rear���� �˻�
static void ql_check_invariants(const QLP* queue);

/* ===== ť �⺻ ���� ===== */
int ql_enqueue(QLP* queue, int value); // ������ ����: ���� �� 1, ���� �� 0
int ql_dequeue(QLP* queue, int* out); // ������ ���� �� ��ȯ: ���� �� 1, ���� �� 0

/* ===== ť ���� Ȯ�� ===== */
int ql_is_empty(const QLP* queue); // ��� ������ 1, �ƴϸ� 0
int ql_size(const QLP* queue); // ���� ť�� ����� ��� ���� ��ȯ

/* ===== ť ��� ===== */
void ql_print(const QLP* queue); // ť ���� ��� (front -> rear ����)

/* ===== �޸� ����: ��� ��� ���� + front/rear �ʱ�ȭ ===== */
void ql_free(QLP* queue);

#endif