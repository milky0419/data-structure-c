#include <stdio.h>
#include "linked_list.h"

int main() {
	LLNode* head = ll_create();
	int out;

	/* �� ����Ʈ���� ����(pop) �õ� */
	printf("===== �� ����Ʈ���� ����(pop) �õ� =====\n");
	printf("pop_front(empty)=%d\n", ll_pop_front(&head, &out));
	printf("pop_back(empty)=%d\n", ll_pop_back(&head, &out));
	printf("\n");

	/* ��/�� ���� �� ��� Ȯ�� */
	printf("===== ��/�� ���� �� ��� Ȯ�� =====\n");
	ll_push_front(&head, 2);
	printf("push_front(2): ");
	ll_print(head);
	ll_push_front(&head, 1);
	printf("push_front(1): ");
	ll_print(head);
	ll_push_back(&head, 3);
	printf("push_back(3): ");
	ll_print(head);
	printf("\n");

	/* ����/������ �� Ž�� */
	printf("===== ����/������ �� Ž�� =====\n");
	printf("find(2)=%p\n", (void*)ll_find(head, 2));
	printf("find(100)=%p\n", (void*)ll_find(head, 100));
	printf("\n");

	/* ��/�� ���� �� ����Ʈ ���� ���� */
	printf("===== ��/�� ���� �� ����Ʈ ���� ���� =====\n");
	if (ll_pop_front(&head, &out))
		printf("pop_front=%d\n", out);
	ll_print(head); // ����Ʈ ���� ����
	if (ll_pop_back(&head, &out))
		printf("pop_back=%d\n", out);
	ll_print(head); // ����Ʈ ���� ����

	/* ����Ʈ �޸� ���� */
	ll_free(head);
	head = NULL;
	return 0;
}