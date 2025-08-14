#include "stack_linkedlist.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free�� ����ϱ� ����

/* ===== ���� ���� ===== */

/* �� ���� ���� �� �ʱ�ȭ */
SLP sl_create() {
    SLP stack;
    stack.top = NULL;

    return stack;
}

/* �� ��� ���� ���� */
static SLNode* sl_new_node(int value) {
    SLNode* n = (SLNode*)malloc(sizeof(SLNode));

    if (!n) // ���� �Ҵ� ���� ��
        return NULL; // NULL ��ȯ

    n->data = value;
    n->next = NULL;

    return n;
}

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ������ �� top==NULL���� �˻�
// ���� ����Ʈ�� ���Ἲ �˻�
static void sl_check_invariants(const SLP* stack) {
    if (!stack) { // ������ NULL�� ��
        printf("invariant failed: stack is NULL\n");
        return; // �Լ� ����
    }

    // 1) �� ������ ��: top == NULL���� �˻�
    if (stack->top == NULL) {
        // �� ���� ����: ����
        return;
    }

    // 2) �� ������ �ƴ� ��: ���� ����Ʈ ���Ἲ �˻�
    SLNode* cur = stack->top;
    int count = 0;
    while (cur && count < 10000) { // ���� ���� ����
        cur = cur->next;
        count++;
    }

    if (count >= 10000) {
        printf("invariant failed: possible circular reference in stack\n");
    }
}

/* ===== ���� �⺻ ���� ===== */

/* ������ ����: ���� �� 1, ���� �� 0 */
int sl_push(SLP* stack, int value) {
    if (!stack) {
        printf("������ NULL�Դϴ�\n");
        return 0; // ����
    }

    SLNode* n = sl_new_node(value);
    if (!n) { // �޸� ���� ��
        printf("�޸� �Ҵ� ����\n");
        return 0; // ����
    }

    n->next = stack->top;
    stack->top = n;

    sl_check_invariants(stack); // �Һ��� �˻�
    return 1; // ����
}

/* ������ ���� �� ��ȯ: ���� �� 1, ���� �� 0 */
int sl_pop(SLP* stack, int* out) {
    if (!stack) {
        printf("������ NULL�Դϴ�\n");
        return 0; // ����
    }

    if (sl_is_empty(stack)) {
        printf("������ ����ֽ��ϴ�\n");
        return 0; // ����
    }

    SLNode* top_node = stack->top;
    if (out) {
        *out = top_node->data;
    }

    stack->top = top_node->next;
    free(top_node);
    top_node = NULL; // free �� �����͸� NULL�� ����

    sl_check_invariants(stack); // �Һ��� �˻�
    return 1; // ����
}

/* �ֻ�� Ȯ��: ���� �� 1, ���� �� 0 */
int sl_peek(const SLP* stack, int* out) {
    if (!stack) {
        printf("������ NULL�Դϴ�\n");
        return 0; // ����
    }

    if (sl_is_empty(stack)) {
        printf("������ ����ֽ��ϴ�\n");
        return 0; // ����
    }

    if (out) {
        *out = stack->top->data;
    }

    return 1; // ����
}

/* ===== ���� ���� Ȯ�� ===== */

/* ��� �ִ��� Ȯ�� */
int sl_is_empty(const SLP* stack) {
    if (!stack) {
        return 1; // NULL�̸� ����ִٰ� ����
    }
    return (stack->top == NULL) ? 1 : 0;
}

/* ���� ���ÿ� ����� ��� ���� ��ȯ */
int sl_size(const SLP* stack) {
    if (!stack || !stack->top) {
        return 0;
    }

    int count = 0;
    SLNode* cur = stack->top;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

/* ===== ���� ��� ===== */
void sl_print(const SLP* stack) {
    if (!stack) {
        printf("������ NULL�Դϴ�\n");
        return;
    }

    if (sl_is_empty(stack)) {
        printf("������ ����ֽ��ϴ�\n");
        return;
    }

    printf("���� [top -> bottom]: ");
    SLNode* cur = stack->top;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
    printf("ũ��: %d\n", sl_size(stack));
}

/* ===== �޸� ���� ===== */
void sl_free(SLP* stack) {
    if (!stack) {
        return;
    }

    SLNode* cur = stack->top;
    while (cur) {
        SLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free �� �����͸� NULL�� ����
    }

    stack->top = NULL;
}