#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free�� ����ϱ� ����

/* ===== ����Ʈ ���� ===== */

/* �� ����Ʈ ���� */
LLP ll_create() {
    LLP list;
    list.head = NULL;
    list.tail = NULL;

    return list;
}

/* �� ��� ���� ���� */
static LLNode* ll_new_node(int value) {
    LLNode* n = (LLNode*)malloc(sizeof(LLNode));

    if (!n) // ���� �Ҵ� ���� ��
        return NULL; // NULL ��ȯ

    n->data = value;
    n->next = NULL;

    return n;
}

/* ===== �Һ��� �˻�(�߰� ���) ===== */
// �� ����Ʈ�� �� head==NULL && tail==NULL���� �˻�
// �� ����Ʈ�� �ƴ� �� tail�� ������ ����̰�, tail->next==NULL���� �˻�
static void ll_check_invariants(const LLP* list) {
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

    // 2) �� ����Ʈ�� �ƴ� ��: tail�� ������ ������� �˻�
    const LLNode* cur = list->head;
    while (cur->next) // ������ ��忡 ������ ������ �ݺ�
        cur = cur->next;
    if (cur != list->tail) {
        printf("invariant failed: tail is not last (tail=%p, last=%p)\n",
            (void*)list->tail, (void*)cur);
    }
    if (list->tail->next != NULL)
        printf("invariant failed: tail->next must be NULL\n");
}

/* ===== �� ��/�� ���� ===== */

/* �� �� ���� */
void ll_push_front(LLP* list, int value) {
    if (!list) // �� ����Ʈ�� ��
        return; // �Լ� ����

    LLNode* n = ll_new_node(value);
    if (!n) // �޸� ���� ��
        return;

    n->next = list->head;
    list->head = n;
    if (list->tail == NULL) // ù ������ ��
        list->tail = n; // tail ����ȭ

    ll_check_invariants(list); // �Һ��� �˻�
}

/* �� �� ���� */
void ll_push_back(LLP* list, int value) {
    if (!list) // �� ����Ʈ�� ��
        return;

    LLNode* n = ll_new_node(value);
    if (!n) // �޸� ���� ��
        return; // ����

    if (!list->head) // �� ����Ʈ�� ��
        list->head = list->tail = n;
    else {
        list->tail->next = n;
        list->tail = n;
    }

    ll_check_invariants(list); // �Һ��� �˻�
}

/* ===== �� ��/�� ���� ===== */

/* �� �� ����: ���� �� 1, ���� �� 0 */
int ll_pop_front(LLP* list, int* out) {
    if (!list || !list->head)
        return 0; // ����

    LLNode* first = list->head;
    if (out)
        *out = first->data;
    list->head = first->next;

    if (list->head == NULL) // ����Ʈ�� ���
        list->tail = NULL; // tail�� NULL

    free(first);

    ll_check_invariants(list); // �Һ��� �˻�
    return 1; // ����
}

/* �� �� ����: ���� �� 1, ���� �� 0 */
int ll_pop_back(LLP* list, int* out) {
    if (!list || !list->head)
        return 0; // ����

    // ��尡 �� ���� ��: ll_pop_front�� ����ϰ� ����
    if (list->head == list->tail) {
        if (out)
            *out = list->head->data;

        free(list->head);
        list->head = list->tail = NULL;

        ll_check_invariants(list);
        return 1; // ����
    }

    // ��尡 ���� ���� ��: tail �������� �ݺ�
    LLNode* cur = list->head;
    while (cur->next != list->tail)
        cur = cur->next;
    if (out)
        *out = list->tail->data;

    free(list->tail);

    list->tail = cur;
    list->tail->next = NULL;

    ll_check_invariants(list); // �Һ��� �˻�
    return 1; // ����
}

/* ===== �� Ž�� ===== */
/* �� Ž��: ã���� ��� ������, �� ã���� NULL ��ȯ */
LLNode* ll_find(const LLP* list, int target) {
    if (!list || !list->head)
        return NULL; // ����

    LLNode* cur = list->head;
    while (cur) {
        if (cur->data == target)
            return cur; // ã��
        cur = cur->next;
    }
    return NULL; // �� ã��
}

/* ===== ��ü ��� ===== */
void ll_print(const LLP* list) {
    if (!list || !list->head) {
        printf("����Ʈ�� ����ֽ��ϴ�\n");
        return;
    }

    printf("����Ʈ: ");
    LLNode* cur = list->head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
}

/* ===== �޸� ���� ===== */
void ll_free(LLP* list) {
    if (!list)
        return;

    LLNode* cur = list->head;
    while (cur) {
        LLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free �� �����͸� NULL�� ����
    }

    list->head = NULL;
    list->tail = NULL;
}

/* ===== ����Ʈ�� ����ִ��� Ȯ�� ===== */
int ll_is_empty(const LLP* list) {
    if (!list)
        return 1; // NULL�̸� ����ִٰ� ����
    return (list->head == NULL) ? 1 : 0;
}