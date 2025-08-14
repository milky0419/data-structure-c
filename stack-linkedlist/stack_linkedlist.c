#include "stack_linkedlist.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free를 사용하기 위함

/* ===== 스택 생성 ===== */

/* 빈 스택 생성 및 초기화 */
SLP sl_create() {
    SLP stack;
    stack.top = NULL;

    return stack;
}

/* 새 노드 동적 생성 */
static SLNode* sl_new_node(int value) {
    SLNode* n = (SLNode*)malloc(sizeof(SLNode));

    if (!n) // 동적 할당 실패 시
        return NULL; // NULL 반환

    n->data = value;
    n->next = NULL;

    return n;
}

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 스택일 때 top==NULL인지 검사
// 연결 리스트의 무결성 검사
static void sl_check_invariants(const SLP* stack) {
    if (!stack) { // 스택이 NULL일 때
        printf("invariant failed: stack is NULL\n");
        return; // 함수 종료
    }

    // 1) 빈 스택일 때: top == NULL인지 검사
    if (stack->top == NULL) {
        // 빈 스택 상태: 정상
        return;
    }

    // 2) 빈 스택이 아닐 때: 연결 리스트 무결성 검사
    SLNode* cur = stack->top;
    int count = 0;
    while (cur && count < 10000) { // 무한 루프 방지
        cur = cur->next;
        count++;
    }

    if (count >= 10000) {
        printf("invariant failed: possible circular reference in stack\n");
    }
}

/* ===== 스택 기본 연산 ===== */

/* 데이터 삽입: 성공 시 1, 실패 시 0 */
int sl_push(SLP* stack, int value) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return 0; // 실패
    }

    SLNode* n = sl_new_node(value);
    if (!n) { // 메모리 부족 시
        printf("메모리 할당 실패\n");
        return 0; // 실패
    }

    n->next = stack->top;
    stack->top = n;

    sl_check_invariants(stack); // 불변식 검사
    return 1; // 성공
}

/* 데이터 제거 및 반환: 성공 시 1, 실패 시 0 */
int sl_pop(SLP* stack, int* out) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return 0; // 실패
    }

    if (sl_is_empty(stack)) {
        printf("스택이 비어있습니다\n");
        return 0; // 실패
    }

    SLNode* top_node = stack->top;
    if (out) {
        *out = top_node->data;
    }

    stack->top = top_node->next;
    free(top_node);
    top_node = NULL; // free 후 포인터를 NULL로 설정

    sl_check_invariants(stack); // 불변식 검사
    return 1; // 성공
}

/* 최상단 확인: 성공 시 1, 실패 시 0 */
int sl_peek(const SLP* stack, int* out) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return 0; // 실패
    }

    if (sl_is_empty(stack)) {
        printf("스택이 비어있습니다\n");
        return 0; // 실패
    }

    if (out) {
        *out = stack->top->data;
    }

    return 1; // 성공
}

/* ===== 스택 상태 확인 ===== */

/* 비어 있는지 확인 */
int sl_is_empty(const SLP* stack) {
    if (!stack) {
        return 1; // NULL이면 비어있다고 간주
    }
    return (stack->top == NULL) ? 1 : 0;
}

/* 현재 스택에 저장된 요소 개수 반환 */
int sl_size(const SLP* stack) {
    if (!stack || !stack->top) {
        return 0;
    }

    int count = 0;
    SLNode* cur = stack->top;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

/* ===== 스택 출력 ===== */
void sl_print(const SLP* stack) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return;
    }

    if (sl_is_empty(stack)) {
        printf("스택이 비어있습니다\n");
        return;
    }

    printf("스택 [top -> bottom]: ");
    SLNode* cur = stack->top;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
    printf("크기: %d\n", sl_size(stack));
}

/* ===== 메모리 해제 ===== */
void sl_free(SLP* stack) {
    if (!stack) {
        return;
    }

    SLNode* cur = stack->top;
    while (cur) {
        SLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free 후 포인터를 NULL로 설정
    }

    stack->top = NULL;
}