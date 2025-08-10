#include <stdio.h>
#include "linked_list.h"

int main() {
    printf("===== ���� ���� ����Ʈ �׽�Ʈ ���� =====\n\n");

    // 1. ����Ʈ ���� �׽�Ʈ
    printf("1. ����Ʈ ���� �׽�Ʈ\n");
    LLP list = ll_create();
    printf("����Ʈ ���� ����!\n");
    printf("�ʱ� ����: ");
    ll_print(&list);
    printf("������� Ȯ��: %s\n", ll_is_empty(&list) ? "�������" : "������� ����");
    ll_print(&list);
    printf("\n");

    // 2. �� �� ���� �׽�Ʈ
    printf("2. �� �� ���� �׽�Ʈ\n");
    ll_push_front(&list, 10);
    printf("10 ���� ��: ");
    ll_print(&list);

    ll_push_front(&list, 20);
    printf("20 ���� ��: ");
    ll_print(&list);
    printf("\n");

    // 3. �� �� ���� �׽�Ʈ
    printf("3. �� �� ���� �׽�Ʈ\n");
    ll_push_back(&list, 5);
    printf("5 ���� ��: ");
    ll_print(&list);

    ll_push_back(&list, 1);
    printf("1 ���� ��: ");
    ll_print(&list);
    printf("\n");

    // 4. �� Ž�� �׽�Ʈ
    printf("4. �� Ž�� �׽�Ʈ\n");
    LLNode* found = ll_find(&list, 10);
    printf("10 Ž��: %s\n", found ? "ã��" : "�� ã��");

    found = ll_find(&list, 5);
    printf("5 Ž��: %s\n", found ? "ã��" : "�� ã��");

    found = ll_find(&list, 100);
    printf("100 Ž��: %s\n", found ? "ã��" : "�� ã��");
    printf("\n");

    // 5. �� �� ���� �׽�Ʈ
    printf("5. �� �� ���� �׽�Ʈ\n");
    printf("���� ����Ʈ: ");
    ll_print(&list);

    int deleted_value;
    int result = ll_pop_front(&list, &deleted_value);
    if (result) {
        printf("������ ��: %d\n", deleted_value);
        printf("���� ��: ");
        ll_print(&list);
    }
    else {
        printf("���� ����\n");
    }
    printf("\n");

    // 6. �� �� ���� �׽�Ʈ
    printf("6. �� �� ���� �׽�Ʈ\n");
    printf("���� ����Ʈ: ");
    ll_print(&list);

    result = ll_pop_back(&list, &deleted_value);
    if (result) {
        printf("������ ��: %d\n", deleted_value);
        printf("���� ��: ");
        ll_print(&list);
    }
    else {
        printf("���� ����\n");
    }
    printf("\n");

    // 7. ��� ���� �׽�Ʈ - ��� ��� ����
    printf("7. ��� ���� �׽�Ʈ - ��� ��� ����\n");
    printf("���� ����Ʈ: ");
    ll_print(&list);

    while (!ll_is_empty(&list)) {
        result = ll_pop_front(&list, &deleted_value);
        if (result) {
            printf("������ ��: %d\n", deleted_value);
            if (!ll_is_empty(&list)) {
                ll_print(&list);
            }
        }
    }
    printf("��� ��� ���� �Ϸ�\n");
    ll_print(&list);
    printf("������� Ȯ��: %s\n", ll_is_empty(&list) ? "�������" : "������� ����");
    printf("\n");

    // 8. ���� ��Ȳ �׽�Ʈ - �� ����Ʈ���� ���� �õ�
    printf("8. ���� ��Ȳ �׽�Ʈ - �� ����Ʈ���� ���� �õ�\n");
    printf("�� ����Ʈ���� �� �� ���� �õ�:\n");
    result = ll_pop_front(&list, &deleted_value);
    printf("���: %s\n", result ? "����" : "����");

    printf("�� ����Ʈ���� �� �� ���� �õ�:\n");
    result = ll_pop_back(&list, &deleted_value);
    printf("���: %s\n", result ? "����" : "����");
    printf("\n");

    // 9. ���� ��� �׽�Ʈ
    printf("9. ���� ��� �׽�Ʈ\n");
    ll_push_front(&list, 99);
    printf("���� ��� ���� ��: ");
    ll_print(&list);

    result = ll_pop_back(&list, &deleted_value);
    if (result) {
        printf("���� ��� ����: %d\n", deleted_value);
        ll_print(&list);
    }
    printf("\n");

    // 10. ���� �׽�Ʈ - �پ��� ���� ����
    printf("10. ���� �׽�Ʈ - �پ��� ���� ����\n");
    for (int i = 1; i <= 5; i++) {
        ll_push_back(&list, i * 10);
    }
    printf("1-5���� 10��� ���� ��: ");
    ll_print(&list);

    ll_push_front(&list, 100);
    ll_push_front(&list, 200);
    printf("���ʿ� 100, 200 ���� ��: ");
    ll_print(&list);

    printf("Ž�� �׽�Ʈ:\n");
    found = ll_find(&list, 30);
    printf("30 Ž��: %s\n", found ? "ã��" : "�� ã��");
    found = ll_find(&list, 200);
    printf("200 Ž��: %s\n", found ? "ã��" : "�� ã��");
    found = ll_find(&list, 999);
    printf("999 Ž��: %s\n", found ? "ã��" : "�� ã��");
    printf("\n");

    // 11. �Һ��� �˻� �׽�Ʈ
    printf("11. �Һ��� �˻� �׽�Ʈ\n");
    printf("���� ����Ʈ: ");
    ll_print(&list);
    printf("�Һ��� �˻� ���� ��...\n");
    // �Һ��� �˻�� �� ����/���� ���� �� �ڵ����� �����
    printf("�Һ��� �˻� �Ϸ� (���� �޽����� ������ ����)\n");
    printf("\n");

    // 12. �޸� ����
    printf("12. �޸� ����\n");
    ll_free(&list);
    printf("����Ʈ �޸� ���� �Ϸ�\n");
    ll_print(&list);
    printf("\n");

    // 13. NULL ������ �׽�Ʈ
    printf("13. NULL ������ ������ �׽�Ʈ\n");
    ll_push_front(NULL, 10);
    ll_push_back(NULL, 10);
    result = ll_pop_front(NULL, &deleted_value);
    printf("NULL ����Ʈ���� pop_front ���: %s\n", result ? "����" : "����");
    result = ll_pop_back(NULL, &deleted_value);
    printf("NULL ����Ʈ���� pop_back ���: %s\n", result ? "����" : "����");
    ll_print(NULL);
    printf("NULL ������ �׽�Ʈ �Ϸ�\n");

    printf("\n===== ���� ���� ����Ʈ �׽�Ʈ �Ϸ� =====\n");
    return 0;
}