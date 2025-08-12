#include <stdio.h>
#include "doubly_linked_list.h"

int main() {
    printf("===== ���� ���� ����Ʈ �׽�Ʈ ���� =====\n\n");

    // 1. ����Ʈ ���� �׽�Ʈ
    printf("1. ����Ʈ ���� �׽�Ʈ\n");
    DLLP list = dll_create();
    printf("����Ʈ ���� ����!\n");
    printf("�ʱ� ����: ");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("������� Ȯ��: %s\n", dll_is_empty(&list) ? "�������" : "������� ����");
    printf("\n");

    // 2. �� �� ���� �׽�Ʈ
    printf("2. �� �� ���� �׽�Ʈ\n");
    dll_push_front(&list, 10);
    printf("10 ���� ��: ");
    dll_print_forward(&list);
    dll_print_backward(&list);

    dll_push_front(&list, 20);
    printf("20 ���� ��: ");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 3. �� �� ���� �׽�Ʈ
    printf("3. �� �� ���� �׽�Ʈ\n");
    dll_push_back(&list, 5);
    printf("5 ���� ��: ");
    dll_print_forward(&list);
    dll_print_backward(&list);

    dll_push_back(&list, 1);
    printf("1 ���� ��: ");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 4. �� Ž�� �׽�Ʈ
    printf("4. �� Ž�� �׽�Ʈ\n");
    DLLNode* found = dll_find(&list, 10);
    printf("10 Ž��: %s\n", found ? "ã��" : "�� ã��");

    found = dll_find(&list, 5);
    printf("5 Ž��: %s\n", found ? "ã��" : "�� ã��");

    found = dll_find(&list, 100);
    printf("100 Ž��: %s\n", found ? "ã��" : "�� ã��");
    printf("\n");

    // 5. �� �� ���� �׽�Ʈ
    printf("5. �� �� ���� �׽�Ʈ\n");
    printf("���� ����Ʈ: ");
    dll_print_forward(&list);

    int deleted_value;
    int result = dll_pop_front(&list, &deleted_value);
    if (result) {
        printf("������ ��: %d\n", deleted_value);
        printf("���� ��: ");
        dll_print_forward(&list);
        dll_print_backward(&list);
    }
    else {
        printf("���� ����\n");
    }
    printf("\n");

    // 6. �� �� ���� �׽�Ʈ
    printf("6. �� �� ���� �׽�Ʈ\n");
    printf("���� ����Ʈ: ");
    dll_print_forward(&list);

    result = dll_pop_back(&list, &deleted_value);
    if (result) {
        printf("������ ��: %d\n", deleted_value);
        printf("���� ��: ");
        dll_print_forward(&list);
        dll_print_backward(&list);
    }
    else {
        printf("���� ����\n");
    }
    printf("\n");

    // 7. ����� ��� ���� �׽�Ʈ
    printf("7. ����� ��� ���� �׽�Ʈ\n");
    // �� ���� ������ �߰�
    dll_push_back(&list, 100);
    dll_push_back(&list, 200);
    dll_push_front(&list, 50);
    printf("50, 100, 200 �߰� ��:\n");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 8. ��� ���� �׽�Ʈ - ��� ��� ����
    printf("8. ��� ���� �׽�Ʈ - ��� ��� ����\n");
    printf("���� ����Ʈ: ");
    dll_print_forward(&list);

    while (!dll_is_empty(&list)) {
        result = dll_pop_front(&list, &deleted_value);
        if (result) {
            printf("������ ��: %d\n", deleted_value);
            if (!dll_is_empty(&list)) {
                dll_print_forward(&list);
            }
        }
    }
    printf("��� ��� ���� �Ϸ�\n");
    dll_print_forward(&list);
    printf("������� Ȯ��: %s\n", dll_is_empty(&list) ? "�������" : "������� ����");
    printf("\n");

    // 9. ���� ��Ȳ �׽�Ʈ - �� ����Ʈ���� ����
    printf("9. ���� ��Ȳ �׽�Ʈ - �� ����Ʈ���� ���� �õ�\n");
    printf("�� ����Ʈ���� �� �� ���� �õ�:\n");
    result = dll_pop_front(&list, &deleted_value);
    printf("���: %s\n", result ? "����" : "����");

    printf("�� ����Ʈ���� �� �� ���� �õ�:\n");
    result = dll_pop_back(&list, &deleted_value);
    printf("���: %s\n", result ? "����" : "����");
    printf("\n");

    // 10. ���� ��� �׽�Ʈ
    printf("10. ���� ��� �׽�Ʈ\n");
    dll_push_front(&list, 99);
    printf("���� ��� ���� ��: ");
    dll_print_forward(&list);
    dll_print_backward(&list);

    result = dll_pop_back(&list, &deleted_value);
    if (result) {
        printf("���� ��� ����: %d\n", deleted_value);
        dll_print_forward(&list);
        dll_print_backward(&list);
    }
    printf("\n");

    // 11. ���� ���� Ư�� �׽�Ʈ
    printf("11. ���� ���� Ư�� ���� �׽�Ʈ\n");
    // �յ� ������ ��� �׽�Ʈ
    dll_push_front(&list, 30);
    dll_push_back(&list, 40);
    dll_push_front(&list, 20);
    dll_push_back(&list, 50);
    dll_push_front(&list, 10);

    printf("�յ� ���� ȥ�� ��:\n");
    dll_print_forward(&list);
    dll_print_backward(&list);

    // �յ� ������ ��� �׽�Ʈ
    dll_pop_front(&list, &deleted_value);
    printf("�� ����(%d) ��: ", deleted_value);
    dll_print_forward(&list);

    dll_pop_back(&list, &deleted_value);
    printf("�� ����(%d) ��: ", deleted_value);
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 12. �Һ��� �˻� �׽�Ʈ
    printf("12. �Һ��� �˻� �׽�Ʈ\n");
    printf("���� ����Ʈ: ");
    dll_print_forward(&list);
    printf("�Һ��� �˻� ���� ��...\n");
    // �Һ��� �˻�� �� ����/���� ���� �� �ڵ����� �����
    printf("�Һ��� �˻� �Ϸ� (���� �޽����� ������ ����)\n");
    printf("\n");

    // 13. �޸� ����
    printf("13. �޸� ����\n");
    dll_free(&list);
    printf("����Ʈ �޸� ���� �Ϸ�\n");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 14. NULL ������ ������ �׽�Ʈ
    printf("14. NULL ������ ������ �׽�Ʈ\n");
    dll_push_front(NULL, 10);
    dll_push_back(NULL, 10);
    result = dll_pop_front(NULL, &deleted_value);
    printf("NULL ����Ʈ���� pop_front ���: %s\n", result ? "����" : "����");
    result = dll_pop_back(NULL, &deleted_value);
    printf("NULL ����Ʈ���� pop_back ���: %s\n", result ? "����" : "����");
    dll_print_forward(NULL);
    dll_print_backward(NULL);
    printf("NULL ������ �׽�Ʈ �Ϸ�\n");

    printf("\n===== ���� ���� ����Ʈ �׽�Ʈ �Ϸ� =====\n");
    return 0;
}