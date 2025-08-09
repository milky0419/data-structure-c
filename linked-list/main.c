#include <stdio.h>
#include "linked_list.h"

int main() {
	LLNode* head = ll_create();
	int out;

	/* 빈 리스트에서 삭제(pop) 시도 */
	printf("===== 빈 리스트에서 삭제(pop) 시도 =====\n");
	printf("pop_front(empty)=%d\n", ll_pop_front(&head, &out));
	printf("pop_back(empty)=%d\n", ll_pop_back(&head, &out));
	printf("\n");

	/* 앞/뒤 삽입 후 출력 확인 */
	printf("===== 앞/뒤 삽입 후 출력 확인 =====\n");
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

	/* 존재/비존재 값 탐색 */
	printf("===== 존재/비존재 값 탐색 =====\n");
	printf("find(2)=%p\n", (void*)ll_find(head, 2));
	printf("find(100)=%p\n", (void*)ll_find(head, 100));
	printf("\n");

	/* 앞/뒤 삭제 후 리스트 상태 검증 */
	printf("===== 앞/뒤 삭제 후 리스트 상태 검증 =====\n");
	if (ll_pop_front(&head, &out))
		printf("pop_front=%d\n", out);
	ll_print(head); // 리스트 상태 검증
	if (ll_pop_back(&head, &out))
		printf("pop_back=%d\n", out);
	ll_print(head); // 리스트 상태 검증

	/* 리스트 메모리 해제 */
	ll_free(head);
	head = NULL;
	return 0;
}