#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free�� ����ϱ� ����

/* ===== ����Ʈ ���� ===== */

/* �� ����Ʈ ���� */
DLLP dll_create() {
    DLLP list;
    list.head = NULL;
    list.tail = NULL;

    return list;
}

/* �� ��� ���� ���� */
static DLLNode* dll_new_node(int value) {
    DLLNode* n = (DLLNode*)malloc(sizeof(DLLNode));

    if (!n) // ���� �Ҵ� ���� ��
        return NULL; // NULL ��ȯ

    n->data = value;
    n->prev = NULL;
    n->next = NULL;

    return n;
}

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ����Ʈ�� �� head==NULL && tail==NULL���� �˻�
// �� ����Ʈ�� �ƴ� �� head->prev==NULL && tail->next==NULL���� �˻�
// ����� ������ �ùٸ��� �˻�
static void dll_check_invariants(const DLLP* list) {
    if (!list) { // ����Ʈ�� NULL�� ��
        printf("invariant failed: list is NULL\n");
        return; // �Լ� ����
    }

    // 1) �� ����Ʈ�� ��: head/tail�� ���ÿ� NULL�̾�� ��
    if (list->head == NULL || list->tail == NULL) {
        if (!(list->head == NULL && list->tail == NULL))
            printf("invariant failed: only one of head/tail is NULL (head=%p, tail=%p)\n",
                (void*)list->head, (void*)list->tail);
        return; // �� ����Ʈ�� �߰� �˻� ���ʿ�
    }

    // 2) �� ����Ʈ�� �ƴ� ��: �� �� ����� ��� ������ �˻�
    if (list->head->prev != NULL)
        printf("invariant failed: head->prev must be NULL\n");
    if (list->tail->next != NULL)
        printf("invariant failed: tail->next must be NULL\n");

    // 3) ����� ���� �ϰ��� �˻�
    DLLNode* cur = list->head;
    while (cur && cur->next) {
        if (cur->next->prev != cur) {
            printf("invariant failed: bidirectional link broken at node %d\n", cur->data);
        }
        cur = cur->next;
    }

    // 4) tail�� ���� ������ ������� �˻�
    if (cur != list->tail) {
        printf("invariant failed: tail is not last (tail=%p, last=%p)\n",
            (void*)list->tail, (void*)cur);
    }
}

/* ===== �� ��/�� ���� ===== */

/* �� �� ���� */
void dll_push_front(DLLP* list, int value) {
    if (!list) // �� ����Ʈ�� ��
        return; // �Լ� ����

    DLLNode* n = dll_new_node(value);
    if (!n) // �޸� ���� ��
        return;

    if (!list->head) { // �� ����Ʈ�� ��
        list->head = list->tail = n;
    }
    else {
        n->next = list->head;
        list->head->prev = n;
        list->head = n;
    }

    dll_check_invariants(list); // �Һ��� �˻�
}

/* �� �� ���� */
void dll_push_back(DLLP* list, int value) {
    if (!list) // �� ����Ʈ�� ��
        return;

    DLLNode* n = dll_new_node(value);
    if (!n) // �޸� ���� ��
        return;

    if (!list->tail) { // �� ����Ʈ�� ��
        list->head = list->tail = n;
    }
    else {
        n->prev = list->tail;
        list->tail->next = n;
        list->tail = n;
    }

    dll_check_invariants(list); // �Һ��� �˻�
}

/* ===== �� ��/�� ���� ===== */

/* �� �� ����: ���� �� 1, ���� �� 0 */
int dll_pop_front(DLLP* list, int* out) {
    if (!list || !list->head)
        return 0; // ����

    DLLNode* first = list->head;
    if (out)
        *out = first->data;

    if (list->head == list->tail) { // ��尡 �ϳ��� ��
        list->head = list->tail = NULL;
    }
    else {
        list->head = first->next;
        list->head->prev = NULL;
    }

    free(first);
    first = NULL; // free �� �����͸� NULL�� ����

    dll_check_invariants(list); // �Һ��� �˻�
    return 1; // ����
}

/* �� �� ����: ���� �� 1, ���� �� 0 */
int dll_pop_back(DLLP* list, int* out) {
    if (!list || !list->tail)
        return 0; // ����

    DLLNode* last = list->tail;
    if (out)
        *out = last->data;

    if (list->head == list->tail) { // ��尡 �ϳ��� ��
        list->head = list->tail = NULL;
    }
    else {
        list->tail = last->prev;
        list->tail->next = NULL;
    }

    free(last);
    last = NULL; // free �� �����͸� NULL�� ����

    dll_check_invariants(list); // �Һ��� �˻�
    return 1; // ����
}

/* ===== �� Ž�� ===== */
/* �� Ž��: ã���� ��� ������, �� ã���� NULL ��ȯ */
DLLNode* dll_find(const DLLP* list, int target) {
    if (!list || !list->head)
        return NULL; // ����

    DLLNode* cur = list->head;
    while (cur) {
        if (cur->data == target)
            return cur; // ã��
        cur = cur->next;
    }
    return NULL; // �� ã��
}

/* ===== ��� ===== */

/* �տ��� �ڷ� ��� */
void dll_print_forward(const DLLP* list) {
    if (!list || !list->head) {
        printf("����Ʈ�� ����ֽ��ϴ� (�ա��)\n");
        return;
    }

    printf("�ա��: ");
    DLLNode* cur = list->head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" <-> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
}

/* �ڿ��� ������ ��� */
void dll_print_backward(const DLLP* list) {
    if (!list || !list->tail) {
        printf("����Ʈ�� ����ֽ��ϴ� (�ڡ��)\n");
        return;
    }

    printf("�ڡ��: ");
    DLLNode* cur = list->tail;
    while (cur) {
        printf("%d", cur->data);
        if (cur->prev) {
            printf(" <-> ");
        }
        cur = cur->prev;
    }
    printf(" -> NULL\n");
}

/* ===== �޸� ���� ===== */
void dll_free(DLLP* list) {
    if (!list)
        return;

    DLLNode* cur = list->head;
    while (cur) {
        DLLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free �� �����͸� NULL�� ����
    }

    list->head = NULL;
    list->tail = NULL;
}

/* ===== ����Ʈ�� ����ִ��� Ȯ�� ===== */
int dll_is_empty(const DLLP* list) {
    if (!list)
        return 1; // NULL�̸� ����ִٰ� ����
    return (list->head == NULL) ? 1 : 0;
}