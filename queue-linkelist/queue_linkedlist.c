#include "queue_linkedlist.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free�� ����ϱ� ����

/* ===== ť ���� ===== */

/* �� ť ���� �� �ʱ�ȭ */
QLP ql_create() {
    QLP queue;
    queue.front = NULL;
    queue.rear = NULL;

    return queue;
}

/* �� ��� ���� ���� */
static QLNode* ql_new_node(int value) {
    QLNode* n = (QLNode*)malloc(sizeof(QLNode));

    if (!n) // ���� �Ҵ� ���� ��
        return NULL; // NULL ��ȯ

    n->data = value;
    n->next = NULL;

    return n;
}

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ť�� �� front==NULL && rear==NULL���� �˻�
// �� ť�� �ƴ� �� front�� rear ���� ���� �˻�
// ���� ����� �� front==rear���� �˻�
static void ql_check_invariants(const QLP* queue) {
    if (!queue) { // ť�� NULL�� ��
        printf("invariant failed: queue is NULL\n");
        return; // �Լ� ����
    }

    // 1) �� ť�� ��: front/rear�� ���ÿ� NULL�̾�� ��
    if (queue->front == NULL || queue->rear == NULL) {
        if (!(queue->front == NULL && queue->rear == NULL))
            printf("invariant failed: only one of front/rear is NULL (front=%p, rear=%p)\n",
                (void*)queue->front, (void*)queue->rear);
        return; // �� ť�� �߰� �˻� ���ʿ�
    }

    // 2) ���� ����� ��: front == rear���� �˻�
    if (queue->front == queue->rear) {
        if (queue->front->next != NULL) {
            printf("invariant failed: single node should have next==NULL\n");
        }
        return; // ���� ���� �߰� �˻� ���ʿ�
    }

    // 3) ���� ����� ��: rear->next == NULL���� �˻�
    if (queue->rear->next != NULL) {
        printf("invariant failed: rear->next must be NULL\n");
    }

    // 4) front���� rear���� ���� Ȯ��
    QLNode* cur = queue->front;
    int count = 0;
    while (cur && cur != queue->rear && count < 10000) { // ���� ���� ����
        cur = cur->next;
        count++;
    }

    if (count >= 10000) {
        printf("invariant failed: possible circular reference in queue\n");
    }
    else if (cur != queue->rear) {
        printf("invariant failed: rear is not reachable from front\n");
    }
}

/* ===== ť �⺻ ���� ===== */

/* ������ ����: ���� �� 1, ���� �� 0 */
int ql_enqueue(QLP* queue, int value) {
    if (!queue) {
        printf("ť�� NULL�Դϴ�\n");
        return 0; // ����
    }

    QLNode* n = ql_new_node(value);
    if (!n) { // �޸� ���� ��
        printf("�޸� �Ҵ� ����\n");
        return 0; // ����
    }

    if (ql_is_empty(queue)) { // �� ť�� ��
        queue->front = queue->rear = n;
    }
    else {
        queue->rear->next = n;
        queue->rear = n;
    }

    ql_check_invariants(queue); // �Һ��� �˻�
    return 1; // ����
}

/* ������ ���� �� ��ȯ: ���� �� 1, ���� �� 0 */
int ql_dequeue(QLP* queue, int* out) {
    if (!queue) {
        printf("ť�� NULL�Դϴ�\n");
        return 0; // ����
    }

    if (ql_is_empty(queue)) {
        printf("ť�� ����ֽ��ϴ�\n");
        return 0; // ����
    }

    QLNode* front_node = queue->front;
    if (out) {
        *out = front_node->data;
    }

    queue->front = front_node->next;

    // ť�� ������� rear�� NULL�� ����
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(front_node);
    front_node = NULL; // free �� �����͸� NULL�� ����

    ql_check_invariants(queue); // �Һ��� �˻�
    return 1; // ����
}

/* ===== ť ���� Ȯ�� ===== */

/* ��� �ִ��� Ȯ�� */
int ql_is_empty(const QLP* queue) {
    if (!queue) {
        return 1; // NULL�̸� ����ִٰ� ����
    }
    return (queue->front == NULL) ? 1 : 0;
}

/* ���� ť�� ����� ��� ���� ��ȯ */
int ql_size(const QLP* queue) {
    if (!queue || !queue->front) {
        return 0;
    }

    int count = 0;
    QLNode* cur = queue->front;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

/* ===== ť ��� ===== */
// front->rear ����
void ql_print(const QLP* queue) {
    if (!queue) {
        printf("ť�� NULL�Դϴ�\n");
        return;
    }

    if (ql_is_empty(queue)) {
        printf("ť�� ����ֽ��ϴ�\n");
        return;
    }

    printf("ť [front -> rear]: ");
    QLNode* cur = queue->front;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
    printf("ũ��: %d\n", ql_size(queue));
}

/* ===== �޸� ���� ===== */
void ql_free(QLP* queue) {
    if (!queue) {
        return;
    }

    QLNode* cur = queue->front;
    while (cur) {
        QLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free �� �����͸� NULL�� ����
    }

    queue->front = NULL;
    queue->rear = NULL;
}