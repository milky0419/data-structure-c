#include <stdio.h>
#include "stack_linkedlist.h"

int main() {
    printf("===== ���� ����Ʈ ��� ���� �׽�Ʈ ���� =====\n\n");

    // 1. ���� ���� �׽�Ʈ
    printf("1. ���� ���� �׽�Ʈ\n");
    SLP stack = sl_create();
    printf("���� ���� ����!\n");
    printf("�ʱ� ����: ");
    sl_print(&stack);
    printf("������� Ȯ��: %s\n", sl_is_empty(&stack) ? "�������" : "������� ����");
    printf("�ʱ� ũ��: %d\n", sl_size(&stack));
    printf("\n");

    // 2. push �⺻ �׽�Ʈ
    printf("2. push �⺻ �׽�Ʈ\n");
    int result = sl_push(&stack, 10);
    printf("10 push ���: %s\n", result ? "����" : "����");
    sl_print(&stack);

    result = sl_push(&stack, 20);
    printf("20 push ���: %s\n", result ? "����" : "����");
    sl_print(&stack);

    result = sl_push(&stack, 30);
    printf("30 push ���: %s\n", result ? "����" : "����");
    sl_print(&stack);
    printf("\n");

    // 3. peek �׽�Ʈ
    printf("3. peek �׽�Ʈ\n");
    int peek_value;
    result = sl_peek(&stack, &peek_value);
    if (result) {
        printf("peek ���: %d (������ ������� ����)\n", peek_value);
        sl_print(&stack);
    }
    else {
        printf("peek ����\n");
    }
    printf("\n");

    // 4. pop �⺻ �׽�Ʈ
    printf("4. pop �⺻ �׽�Ʈ\n");
    printf("pop �� ����: ");
    sl_print(&stack);

    int pop_value;
    result = sl_pop(&stack, &pop_value);
    if (result) {
        printf("pop ���: %d\n", pop_value);
        printf("pop �� ����: ");
        sl_print(&stack);
    }
    else {
        printf("pop ����\n");
    }
    printf("\n");

    // 5. ���� ���� Ȯ�� �׽�Ʈ
    printf("5. ���� ���� Ȯ�� �׽�Ʈ\n");
    printf("���� ���� ũ��: %d\n", sl_size(&stack));
    printf("�������: %s\n", sl_is_empty(&stack) ? "��" : "�ƴϿ�");
    sl_print(&stack);
    printf("\n");

    // 6. ���� Ȯ�� �׽�Ʈ (�迭�� �޸� ũ�� ���� ����)
    printf("6. ���� Ȯ�� �׽�Ʈ\n");
    printf("���� ��� �߰��ϱ� (�迭�� �޸� ũ�� ���� ����)...\n");

    int push_count = 0;
    for (int i = 100; i <= 150; i += 5) {
        result = sl_push(&stack, i);
        if (result) {
            push_count++;
        }
        else {
            printf("push ����: %d\n", i);
            break;
        }
    }
    printf("%d�� ��� �߰� �Ϸ�\n", push_count);
    printf("���� ũ��: %d\n", sl_size(&stack));
    sl_print(&stack);
    printf("\n");

    // 7. �޸� �Ҵ� Ȯ�� (���� ����Ʈ�� ����)
    printf("7. �޸� �Ҵ� Ȯ��\n");
    printf("�� ���� ��� �߰� �õ�...\n");
    int large_push_count = 0;
    for (int i = 1000; i < 1020; i++) {
        result = sl_push(&stack, i);
        if (result) {
            large_push_count++;
        }
        else {
            printf("�޸� �Ҵ� ����: %d\n", i);
            break;
        }
    }
    printf("%d�� �߰� ��� push �Ϸ�\n", large_push_count);
    printf("�� ũ��: %d\n", sl_size(&stack));
    printf("���� 5�� ��Ҹ� ���:\n");

    // ���� �� ���� ��� (��ü ����� �ʹ� ��)
    SLNode* cur = stack.top;
    for (int i = 0; i < 5 && cur; i++) {
        printf("  [%d]: %d\n", i, cur->data);
        cur = cur->next;
    }
    printf("  ... (�� %d��)\n", sl_size(&stack));
    printf("\n");

    // 8. ��� ��� pop �׽�Ʈ
    printf("8. ��� ��� pop �׽�Ʈ\n");
    printf("��ü ��� pop ����...\n");

    int pop_count = 0;
    while (!sl_is_empty(&stack)) {
        result = sl_pop(&stack, &pop_value);
        if (result) {
            pop_count++;
            if (pop_count <= 5 || pop_count % 10 == 0) { // ó�� 5���� 10������ ���
                printf("pop[%d]: %d (���� ũ��: %d)\n", pop_count, pop_value, sl_size(&stack));
            }
        }
        else {
            break;
        }
    }
    printf("�� %d�� ��� pop �Ϸ�\n", pop_count);
    printf("���� ����: ");
    sl_print(&stack);
    printf("������� Ȯ��: %s\n", sl_is_empty(&stack) ? "�������" : "������� ����");
    printf("\n");

    // 9. �� ���ÿ��� pop/peek �õ� (����÷ο� �׽�Ʈ)
    printf("9. �� ���ÿ��� pop/peek �õ� (����÷ο� �׽�Ʈ)\n");
    result = sl_pop(&stack, &pop_value);
    printf("�� ���� pop ���: %s\n", result ? "����" : "����");

    result = sl_peek(&stack, &peek_value);
    printf("�� ���� peek ���: %s\n", result ? "����" : "����");
    printf("\n");

    // 10. LIFO(Last In First Out) Ư�� �׽�Ʈ
    printf("10. LIFO Ư�� �׽�Ʈ\n");
    printf("������� push: 100, 200, 300\n");
    sl_push(&stack, 100);
    sl_push(&stack, 200);
    sl_push(&stack, 300);
    sl_print(&stack);

    printf("pop ���� Ȯ��:\n");
    for (int i = 0; i < 3; i++) {
        result = sl_pop(&stack, &pop_value);
        if (result) {
            printf("pop %d: %d\n", i + 1, pop_value);
        }
    }
    printf("LIFO Ư��: 300 -> 200 -> 100 ������ ���;� ��\n");
    printf("\n");

    // 11. ���� ����Ʈ Ư�� �׽�Ʈ (ũ�� ���� ����)
    printf("11. ���� ����Ʈ Ư�� �׽�Ʈ\n");
    printf("�迭 ��ݰ� �޸� �̷������� ũ�� ������ ������ Ȯ��\n");

    // ������ ũ��� �׽�Ʈ
    for (int i = 1; i <= 15; i++) {
        sl_push(&stack, i * 7); // 7�� ����� �߰�
    }
    printf("15�� ��� �߰� �Ϸ�, ũ��: %d\n", sl_size(&stack));
    sl_print(&stack);

    // �Ϻθ� ����
    for (int i = 0; i < 5; i++) {
        sl_pop(&stack, &pop_value);
    }
    printf("5�� ���� �� ũ��: %d\n", sl_size(&stack));
    sl_print(&stack);
    printf("\n");

    // 12. �Һ��� �˻� �׽�Ʈ
    printf("12. �Һ��� �˻� �׽�Ʈ\n");
    printf("���� ���� ���¿��� �Һ��� �˻�...\n");
    sl_print(&stack);
    printf("�Һ��� �˻� �Ϸ� (���� �޽����� ������ ����)\n");
    printf("\n");

    // 13. �޸� ����
    printf("13. �޸� ����\n");
    sl_free(&stack);
    printf("���� �޸� ���� �Ϸ�\n");
    sl_print(&stack);
    printf("���� �� ũ��: %d\n", sl_size(&stack));
    printf("\n");

    // 14. NULL ������ ������ �׽�Ʈ
    printf("14. NULL ������ ������ �׽�Ʈ\n");
    result = sl_push(NULL, 10);
    printf("NULL ���ÿ� push ���: %s\n", result ? "����" : "����");

    result = sl_pop(NULL, &pop_value);
    printf("NULL ���ÿ��� pop ���: %s\n", result ? "����" : "����");

    result = sl_peek(NULL, &peek_value);
    printf("NULL ���ÿ��� peek ���: %s\n", result ? "����" : "����");

    sl_print(NULL);
    printf("NULL ������ �׽�Ʈ �Ϸ�\n");

    printf("\n===== ���� ����Ʈ ��� ���� �׽�Ʈ �Ϸ� =====\n");
    return 0;
}