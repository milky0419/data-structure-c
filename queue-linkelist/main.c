#include <stdio.h>
#include "queue_linkedlist.h"

int main() {
    printf("===== ���� ����Ʈ ��� ť �׽�Ʈ ���� =====\n\n");

    // 1. ť ���� �׽�Ʈ
    printf("1. ť ���� �׽�Ʈ\n");
    QLP queue = ql_create();
    printf("ť ���� ����!\n");
    printf("�ʱ� ����: ");
    ql_print(&queue);
    printf("������� Ȯ��: %s\n", ql_is_empty(&queue) ? "�������" : "������� ����");
    printf("�ʱ� ũ��: %d\n", ql_size(&queue));
    printf("\n");

    // 2. enqueue �⺻ �׽�Ʈ
    printf("2. enqueue �⺻ �׽�Ʈ\n");
    int result = ql_enqueue(&queue, 10);
    printf("10 enqueue ���: %s\n", result ? "����" : "����");
    ql_print(&queue);

    result = ql_enqueue(&queue, 20);
    printf("20 enqueue ���: %s\n", result ? "����" : "����");
    ql_print(&queue);

    result = ql_enqueue(&queue, 30);
    printf("30 enqueue ���: %s\n", result ? "����" : "����");
    ql_print(&queue);
    printf("\n");

    // 3. dequeue �⺻ �׽�Ʈ
    printf("3. dequeue �⺻ �׽�Ʈ\n");
    printf("dequeue �� ����: ");
    ql_print(&queue);

    int dequeue_value;
    result = ql_dequeue(&queue, &dequeue_value);
    if (result) {
        printf("dequeue ���: %d\n", dequeue_value);
        printf("dequeue �� ����: ");
        ql_print(&queue);
    }
    else {
        printf("dequeue ����\n");
    }
    printf("\n");

    // 4. FIFO(First In First Out) Ư�� �׽�Ʈ
    printf("4. FIFO Ư�� �׽�Ʈ\n");
    printf("���� ť ����: ");
    ql_print(&queue);

    printf("������� enqueue: 40, 50\n");
    ql_enqueue(&queue, 40);
    ql_enqueue(&queue, 50);
    ql_print(&queue);

    printf("dequeue ���� Ȯ��:\n");
    for (int i = 0; i < 4; i++) {
        result = ql_dequeue(&queue, &dequeue_value);
        if (result) {
            printf("dequeue %d: %d\n", i + 1, dequeue_value);
        }
    }
    printf("FIFO Ư��: 20 -> 30 -> 40 -> 50 ������ ���;� ��\n");
    printf("\n");

    // 5. ť ���� Ȯ�� �׽�Ʈ
    printf("5. ť ���� Ȯ�� �׽�Ʈ\n");
    printf("���� ť ũ��: %d\n", ql_size(&queue));
    printf("�������: %s\n", ql_is_empty(&queue) ? "��" : "�ƴϿ�");
    ql_print(&queue);
    printf("\n");

    // 6. ���� Ȯ�� �׽�Ʈ (�迭�� �޸� ũ�� ���� ����)
    printf("6. ���� Ȯ�� �׽�Ʈ\n");
    printf("���� ��� �߰��ϱ� (�迭�� �޸� ũ�� ���� ����)...\n");

    int enqueue_count = 0;
    for (int i = 100; i <= 150; i += 5) {
        result = ql_enqueue(&queue, i);
        if (result) {
            enqueue_count++;
        }
        else {
            printf("enqueue ����: %d\n", i);
            break;
        }
    }
    printf("%d�� ��� �߰� �Ϸ�\n", enqueue_count);
    printf("���� ũ��: %d\n", ql_size(&queue));
    ql_print(&queue);
    printf("\n");

    // 7. �޸� �Ҵ� Ȯ�� (���� ����Ʈ�� ����)
    printf("7. �޸� �Ҵ� Ȯ��\n");
    printf("�� ���� ��� �߰� �õ�...\n");
    int large_enqueue_count = 0;
    for (int i = 1000; i < 1020; i++) {
        result = ql_enqueue(&queue, i);
        if (result) {
            large_enqueue_count++;
        }
        else {
            printf("�޸� �Ҵ� ����: %d\n", i);
            break;
        }
    }
    printf("%d�� �߰� ��� enqueue �Ϸ�\n", large_enqueue_count);
    printf("�� ũ��: %d\n", ql_size(&queue));
    printf("���� 5�� ��Ҹ� ���:\n");

    // ���� �� ���� ��� (��ü ����� �ʹ� ��)
    QLNode* cur = queue.front;
    for (int i = 0; i < 5 && cur; i++) {
        printf("  [%d]: %d\n", i, cur->data);
        cur = cur->next;
    }
    printf("  ... (�� %d��)\n", ql_size(&queue));
    printf("\n");

    // 8. �κ� dequeue �� enqueue �׽�Ʈ
    printf("8. �κ� dequeue �� enqueue �׽�Ʈ\n");
    printf("10�� dequeue �� ���ο� ��� �߰�\n");

    for (int i = 0; i < 10; i++) {
        ql_dequeue(&queue, &dequeue_value);
    }
    printf("10�� dequeue �� ũ��: %d\n", ql_size(&queue));

    // ���ο� ��ҵ� �߰�
    for (int i = 200; i < 205; i++) {
        ql_enqueue(&queue, i);
    }
    printf("5�� �� ��� �߰� �� ũ��: %d\n", ql_size(&queue));

    // ���ʰ� ���� Ȯ��
    printf("���� front 5��: ");
    cur = queue.front;
    for (int i = 0; i < 5 && cur; i++) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    printf("\n");

    // 9. ��� ��� dequeue �׽�Ʈ
    printf("9. ��� ��� dequeue �׽�Ʈ\n");
    printf("��ü ��� dequeue ����...\n");

    int dequeue_count = 0;
    while (!ql_is_empty(&queue)) {
        result = ql_dequeue(&queue, &dequeue_value);
        if (result) {
            dequeue_count++;
            if (dequeue_count <= 5 || dequeue_count % 10 == 0) { // ó�� 5���� 10������ ���
                printf("dequeue[%d]: %d (���� ũ��: %d)\n",
                    dequeue_count, dequeue_value, ql_size(&queue));
            }
        }
        else {
            break;
        }
    }
    printf("�� %d�� ��� dequeue �Ϸ�\n", dequeue_count);
    printf("���� ����: ");
    ql_print(&queue);
    printf("������� Ȯ��: %s\n", ql_is_empty(&queue) ? "�������" : "������� ����");
    printf("\n");

    // 10. �� ť���� dequeue �õ� (����÷ο� �׽�Ʈ)
    printf("10. �� ť���� dequeue �õ� (����÷ο� �׽�Ʈ)\n");
    result = ql_dequeue(&queue, &dequeue_value);
    printf("�� ť dequeue ���: %s\n", result ? "����" : "����");
    printf("\n");

    // 11. ���� ��� �׽�Ʈ
    printf("11. ���� ��� �׽�Ʈ\n");
    printf("���� ��� enqueue �� dequeue\n");
    ql_enqueue(&queue, 99);
    printf("99 enqueue ��: ");
    ql_print(&queue);

    result = ql_dequeue(&queue, &dequeue_value);
    if (result) {
        printf("���� ��� dequeue: %d\n", dequeue_value);
        ql_print(&queue);
    }
    printf("���� ��忡�� front==rear ���� Ȯ�� �Ϸ�\n");
    printf("\n");

    // 12. ���� ����Ʈ Ư�� �׽�Ʈ (ũ�� ���� ����)
    printf("12. ���� ����Ʈ Ư�� �׽�Ʈ\n");
    printf("�迭 ��ݰ� �޸� �̷������� ũ�� ������ ������ Ȯ��\n");

    // ������ ũ��� �׽�Ʈ
    for (int i = 1; i <= 15; i++) {
        ql_enqueue(&queue, i * 3); // 3�� ����� �߰�
    }
    printf("15�� ��� �߰� �Ϸ�, ũ��: %d\n", ql_size(&queue));
    ql_print(&queue);

    // ���� ���� ����
    for (int i = 0; i < 7; i++) {
        ql_dequeue(&queue, &dequeue_value);
    }
    printf("7�� ���� �� ũ��: %d\n", ql_size(&queue));
    ql_print(&queue);

    // ���ʿ� ���ο� ��� �߰�
    for (int i = 50; i < 53; i++) {
        ql_enqueue(&queue, i);
    }
    printf("3�� �߰� ��: ");
    ql_print(&queue);
    printf("\n");

    // 13. �Һ��� �˻� �׽�Ʈ
    printf("13. �Һ��� �˻� �׽�Ʈ\n");
    printf("���� ť ���¿��� �Һ��� �˻�...\n");
    ql_print(&queue);
    printf("�Һ��� �˻� �Ϸ� (���� �޽����� ������ ����)\n");
    printf("\n");

    // 14. �޸� ����
    printf("14. �޸� ����\n");
    ql_free(&queue);
    printf("ť �޸� ���� �Ϸ�\n");
    ql_print(&queue);
    printf("���� �� ũ��: %d\n", ql_size(&queue));
    printf("\n");

    // 15. NULL ������ ������ �׽�Ʈ
    printf("15. NULL ������ ������ �׽�Ʈ\n");
    result = ql_enqueue(NULL, 10);
    printf("NULL ť�� enqueue ���: %s\n", result ? "����" : "����");

    result = ql_dequeue(NULL, &dequeue_value);
    printf("NULL ť���� dequeue ���: %s\n", result ? "����" : "����");

    ql_print(NULL);
    printf("NULL ������ �׽�Ʈ �Ϸ�\n");

    printf("\n===== ���� ����Ʈ ��� ť �׽�Ʈ �Ϸ� =====\n");
    return 0;
}