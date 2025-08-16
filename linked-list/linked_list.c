#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free를 사용하기 위함

/* ===== 리스트 생성 ===== */

/* 빈 리스트 생성 */
LLP ll_create() {
    LLP list;
    list.head = NULL;
    list.tail = NULL;

    return list;
}

/* 새 노드 동적 생성 */
static LLNode* ll_new_node(int value) {
    LLNode* n = (LLNode*)malloc(sizeof(LLNode)); // 동적 할당 및 주소 저장

    if (!n) // 동적 할당 실패 시
        return NULL; // NULL 반환

    n->data = value;
    n->next = NULL;

    return n;
}

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 리스트일 때 head==NULL && tail==NULL인지 검사
// 빈 리스트가 아닐 때 tail이 마지막 노드이고, tail->next==NULL인지 검사
static void ll_check_invariants(const LLP* list) {
    if (!list) { // 리스트가 없을 때
        printf("invariant failed: list is NULL\n");
        return; // 함수 종료
    }

    // 1) 빈 리스트일 때: head/tail은 동시에 NULL이어야 함
    if (list->head == NULL || list->tail == NULL) {
        if (!(list->head == NULL && list->tail == NULL))
            printf("invariant failed: only one of head/tail is NULL (head=%p, tail=%p)\n",
                (void*)list->head, (void*)list->tail);
        return; // 빈 리스트면 추가 검사 불필요
    }

    // 2) 빈 리스트가 아닐 때: tail이 마지막 노드인지 검사
    const LLNode* cur = list->head;
    while (cur->next) // 마지막 노드에 도달할 때까지 반복
        cur = cur->next;
    if (cur != list->tail) {
        printf("invariant failed: tail is not last (tail=%p, last=%p)\n",
            (void*)list->tail, (void*)cur);
    }
    if (list->tail->next != NULL)
        printf("invariant failed: tail->next must be NULL\n");
}

/* ===== 리스트가 비어있는지 확인 ===== */
int ll_is_empty(const LLP* list) {
    if (!list)
        return 1; // NULL이면 비어있다고 간주
    return (list->head == NULL) ? 1 : 0;
}

/* ===== 맨 앞/뒤 삽입 ===== */

/* 맨 앞 삽입: 성공 시 1, 실패 시 0 반환 */
int ll_push_front(LLP* list, int value) {
    if (!list) // 빈 리스트일 때
        return 0;
    
    LLNode* n = ll_new_node(value);
    if (!n) // 메모리 부족 시
        return 0;

    n->next = list->head;
    list->head = n;
    if (!list->tail) // 첫 삽입일 때
        list->tail = n; // tail을 head와 동기화
    
    ll_check_invariants(list); // 불변식 검사
    return 1;
}

/* 맨 뒤 삽입: 성공 시 1, 실패 시 0 반환 */
int ll_push_back(LLP* list, int value) {
    if (!list) // 리스트가 없을 때
        return 0;
    
    LLNode* n = ll_new_node(value);
    if (!n) // 메모리가 부족할 때
        return 0;

    if (!list->head) // 빈 리스트일 때
        list->head = list->tail = n;
    else {
        list->tail->next = n;
        list->tail = n;
    }

    ll_check_invariants(list); // 불변식 검사
    return 1;
}

/* ===== 맨 앞/뒤 삭제 ===== */

/* 맨 앞 삭제: 성공 시 1, 실패 시 0 반환 */
int ll_pop_front(LLP* list, int* out) {
    if (ll_is_empty(list))
        return 0; // 실패

    LLNode* first = list->head;
    if (out)
        *out = first->data;
    list->head = first->next;

    if (list->head == NULL) // 리스트가 비면
        list->tail = NULL; // tail도 NULL

    free(first);

    ll_check_invariants(list); // 불변식 검사
    return 1; // 성공
}

/* 맨 뒤 삭제: 성공 시 1, 실패 시 0 반환 */
int ll_pop_back(LLP* list, int* out) {
    if (ll_is_empty(list))
        return 0; // 실패

    // 노드가 한 개일 때: ll_pop_front와 비슷하게 실행
    if (list->head == list->tail) {
        if (out)
            *out = list->head->data;

        free(list->head);
        list->head = list->tail = NULL;

        ll_check_invariants(list);
        return 1; // 성공
    }

    // 노드가 여러 개일 때: tail 직전까지 반복
    LLNode* cur = list->head;
    while (cur->next != list->tail)
        cur = cur->next;
    if (out)
        *out = list->tail->data;

    free(list->tail);

    list->tail = cur;
    list->tail->next = NULL;

    ll_check_invariants(list); // 불변식 검사
    return 1; // 성공
}

/* ===== 값 탐색 ===== */
/* 값 탐색: 찾으면 노드 포인터, 못 찾으면 NULL 반환 */
LLNode* ll_find(const LLP* list, int target) {
    if (ll_is_empty(list))
        return NULL; // 실패

    LLNode* cur = list->head;
    while (cur) {
        if (cur->data == target)
            return cur; // 찾음
        cur = cur->next;
    }
    return NULL; // 못 찾음
}

/* ===== 전체 출력 ===== */
void ll_print(const LLP* list) {
    if (ll_is_empty(list)) {
        printf("리스트가 비어있습니다\n");
        return;
    }

    LLNode* cur = list->head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

/* ===== 메모리 해제 ===== */
void ll_free(LLP* list) {
    if (!list)
        return;

    LLNode* cur = list->head;
    while (cur) {
        LLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free 후 포인터를 NULL로 설정
    }

    list->head = NULL;
    list->tail = NULL;
}
