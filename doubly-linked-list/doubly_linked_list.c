#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free를 사용하기 위함

/* ===== 리스트 생성 ===== */

/* 빈 리스트 생성 */
DLLP dll_create() {
    DLLP list;
    list.head = NULL;
    list.tail = NULL;

    return list;
}

/* 새 노드 동적 생성 */
static DLLNode* dll_new_node(int value) {
    DLLNode* n = (DLLNode*)malloc(sizeof(DLLNode));

    if (!n) // 동적 할당 실패 시
        return NULL; // NULL 반환

    n->data = value;
    n->prev = NULL;
    n->next = NULL;

    return n;
}

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 리스트일 때 head==NULL && tail==NULL인지 검사
// 빈 리스트가 아닐 때 head->prev==NULL && tail->next==NULL인지 검사
// 양방향 연결이 올바른지 검사
void dll_check_invariants(const DLLP* list) {
    if (!list) { // 리스트가 존재하지 않을 때
        printf("invariant failed: list does not exist\n");
        return; // 함수 종료
    }

    // 1) 빈 리스트일 때: head/tail은 동시에 NULL이어야 함
    if (list->head == NULL || list->tail == NULL) {
        if (!(list->head == NULL && list->tail == NULL))
            printf("invariant failed: only one of head/tail is NULL (head=%p, tail=%p)\n", list->head, list->tail);
        return; // 빈 리스트면 추가 검사 불필요
    }

    // 2) 빈 리스트가 아닐 때: 양 끝 노드의 경계 포인터 검사
    if (list->head->prev != NULL)
        printf("invariant failed: head->prev must be NULL\n");
    if (list->tail->next != NULL)
        printf("invariant failed: tail->next must be NULL\n");

    // 3) 양방향 연결 일관성 검사
    DLLNode* cur = list->head;
    while (cur && cur->next) {
        if (cur->next->prev != cur) {
            printf("invariant failed: bidirectional link broken at node %d\n", cur->data);
        }
        cur = cur->next;
    }

    // 4) tail이 실제 마지막 노드인지 검사
    if (cur != list->tail) {
        printf("invariant failed: tail is not last (tail=%p, last=%p)\n", list->tail, cur);
    }
}

/* ===== 리스트가 비어있는지 확인 ===== */
int dll_is_empty(const DLLP* list) {
    if (!list) // 리스트가 존재하지 않으면
        return 1; // 비어있다고 간주
    return (list->head == NULL) ? 1 : 0;
}

/* ===== 맨 앞/뒤 삽입 ===== */

/* 맨 앞 삽입: 성공 시 1, 실패 시 0 반환 */
int dll_push_front(DLLP* list, int value) {
    if (!list) // 리스트가 존재하지 않으면
        return 0; // 실패

    DLLNode* n = dll_new_node(value);
    if (!n) // 메모리 부족 시
        return 0; // 실패

    if (!list->head) { // 빈 리스트일 때
        list->head = list->tail = n;
    }
    else {
        n->next = list->head;
        list->head->prev = n;
        list->head = n;
    }

    dll_check_invariants(list); // 불변식 검사
    return 1; // 성공
}

/* 맨 뒤 삽입: 성공 시 1, 실패 시 0 반환 */
int dll_push_back(DLLP* list, int value) {
    if (!list) // 리스트가 존재하지 않을 때
        return 0; // 실패

    DLLNode* n = dll_new_node(value);
    if (!n) // 메모리 부족 시
        return 0; // 실패

    if (!list->tail) { // 빈 리스트일 때
        list->head = list->tail = n;
    }
    else {
        n->prev = list->tail;
        list->tail->next = n;
        list->tail = n;
    }

    dll_check_invariants(list); // 불변식 검사
    return 1; // 성공
}

/* ===== 맨 앞/뒤 삭제 ===== */

/* 맨 앞 삭제: 성공 시 1, 실패 시 0 반환 */
int dll_pop_front(DLLP* list, int* out) {
    if (!list || dll_is_empty(list)) // 리스트가 존재하지 않거나 비었을 때
        return 0; // 실패

    DLLNode* first = list->head;
    if (out)
        *out = first->data;

    if (list->head == list->tail) { // 노드가 하나일 때
        list->head = list->tail = NULL;
    }
    else {
        list->head = first->next;
        list->head->prev = NULL;
    }

    free(first);
    first = NULL; // free 후 포인터를 NULL로 설정

    dll_check_invariants(list); // 불변식 검사
    return 1; // 성공
}

/* 맨 뒤 삭제: 성공 시 1, 실패 시 0 반환 */
int dll_pop_back(DLLP* list, int* out) {
    if (!list || dll_is_empty(list)) // 리스트가 존재하지 않거나 비었을 때
        return 0; // 실패

    DLLNode* last = list->tail;
    if (out)
        *out = last->data;

    if (list->head == list->tail) { // 노드가 하나일 때
        list->head = list->tail = NULL;
    }
    else {
        list->tail = last->prev;
        list->tail->next = NULL;
    }

    free(last);
    last = NULL; // free 후 포인터를 NULL로 설정

    dll_check_invariants(list); // 불변식 검사
    return 1; // 성공
}

/* ===== 값 탐색 ===== */
// 찾으면 노드 포인터, 못 찾으면 NULL 반환
DLLNode* dll_find(const DLLP* list, int target) {
    if (!list || dll_is_empty(list)) // 리스트가 존재하지 않거나 비었을 때
        return NULL; // 실패

    DLLNode* cur = list->head;
    while (cur) {
        if (cur->data == target)
            return cur; // 찾음
        cur = cur->next;
    }
    return NULL; // 못 찾음
}

/* ===== 출력 ===== */

/* 앞에서 뒤로 출력 */
void dll_print_forward(const DLLP* list) {
    if (!list || dll_is_empty(list)) { // 리스트가 존재하지 않거나 비었을 때
        printf("리스트가 비어있습니다 (앞→뒤)\n");
        return;
    }

    printf("앞→뒤: [ ");
    DLLNode* cur = list->head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" <-> ");
        }
        cur = cur->next;
    }
    printf(" ]\n");
}

/* 뒤에서 앞으로 출력 */
void dll_print_backward(const DLLP* list) {
    if (!list || dll_is_empty(list)) { // 리스트가 존재하지 않거나 비었을 때
        printf("리스트가 비어있습니다 (뒤→앞)\n");
        return;
    }

    printf("뒤→앞: [ ");
    DLLNode* cur = list->tail;
    while (cur) {
        printf("%d", cur->data);
        if (cur->prev) {
            printf(" <-> ");
        }
        cur = cur->prev;
    }
    printf(" ]\n");
}

/* ===== 메모리 해제 ===== */
void dll_free(DLLP* list) {
    if (!list)
        return;

    DLLNode* cur = list->head;
    while (cur) {
        DLLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free 후 포인터를 NULL로 설정
    }

    list->head = NULL;
    list->tail = NULL;
}
