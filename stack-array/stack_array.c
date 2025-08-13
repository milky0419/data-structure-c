#include "stack_array.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free를 사용하기 위함

/* ===== 스택 생성 ===== */
SAP sa_create() {
    SAP stack = (SAP)malloc(sizeof(StackArray));

    if (!stack) { // 동적 할당 실패 시
        printf("메모리 할당 실패\n");
        return NULL;
    }

    stack->top = -1; // 빈 스택 상태
    stack->capacity = STACK_MAX_SIZE;

    return stack;
}

/* ===== 불변식 검사(추가 기능) ===== */
// top이 유효한 범위에 있는지 검사
// 스택 상태의 일관성 검사
static void sa_check_invariants(const SAP stack) {
    if (!stack) { // 스택이 NULL일 때
        printf("invariant failed: stack is NULL\n");
        return;
    }

    // 1) top 인덱스가 유효한 범위에 있는지 검사
    if (stack->top < -1 || stack->top >= stack->capacity) {
        printf("invariant failed: top index out of range (top=%d, capacity=%d)\n",
            stack->top, stack->capacity);
    }

    // 2) 빈 스택일 때 top == -1인지 검사
    if (stack->top == -1) {
        // 빈 스택 상태: 추가 검사 없음
        return;
    }

    // 3) 가득 찬 스택일 때 top == capacity-1인지 검사
    if (stack->top >= stack->capacity - 1) {
        if (stack->top != stack->capacity - 1) {
            printf("invariant failed: full stack top mismatch (top=%d, should be %d)\n",
                stack->top, stack->capacity - 1);
        }
    }
}

/* ===== 스택 기본 연산 ===== */

/* 데이터 삽입: 성공 시 1, 실패 시 0 */
int sa_push(SAP stack, int value) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return 0; // 실패
    }

    if (sa_is_full(stack)) {
        printf("스택이 가득 찼습니다\n");
        return 0; // 실패
    }

    stack->top++;
    stack->data[stack->top] = value;

    sa_check_invariants(stack); // 불변식 검사
    return 1; // 성공
}

/* 데이터 제거 및 반환: 성공 시 1, 실패 시 0 */
int sa_pop(SAP stack, int* out) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return 0; // 실패
    }

    if (sa_is_empty(stack)) {
        printf("스택이 비어있습니다\n");
        return 0; // 실패
    }

    if (out) {
        *out = stack->data[stack->top];
    }
    stack->top--;

    sa_check_invariants(stack); // 불변식 검사
    return 1; // 성공
}

/* 최상단 확인: 성공 시 1, 실패 시 0 */
int sa_peek(SAP stack, int* out) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return 0; // 실패
    }

    if (sa_is_empty(stack)) {
        printf("스택이 비어있습니다\n");
        return 0; // 실패
    }

    if (out) {
        *out = stack->data[stack->top];
    }

    return 1; // 성공
}

/* ===== 스택 상태 확인 ===== */

/* 비어 있는지 확인 */
int sa_is_empty(const SAP stack) {
    if (!stack) {
        return 1; // NULL이면 비어있다고 간주
    }
    return (stack->top == -1) ? 1 : 0;
}

/* 가득 찼는지 확인 */
int sa_is_full(const SAP stack) {
    if (!stack) {
        return 0; // NULL이면 가득 차지 않았다고 간주
    }
    return (stack->top == stack->capacity - 1) ? 1 : 0;
}

/* 현재 스택에 저장된 요소 개수 반환 */
int sa_size(const SAP stack) {
    if (!stack) {
        return 0;
    }
    return stack->top + 1;
}

/* ===== 메모리 해제 ===== */
void sa_free(SAP stack) {
    if (!stack) {
        return;
    }

    free(stack);
    stack = NULL; // free 후 포인터를 NULL로 설정
}

/* ===== 스택 출력 ===== */
// bottom->top 순서로 출력
void sa_print(const SAP stack) {
    if (!stack) {
        printf("스택이 NULL입니다\n");
        return;
    }

    if (sa_is_empty(stack)) {
        printf("스택이 비어있습니다\n");
        return;
    }

    printf("스택 [bottom -> top]: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d", stack->data[i]);
        if (i < stack->top) {
            printf(" -> ");
        }
    }
    printf(" (top)\n");
    printf("크기: %d/%d\n", sa_size(stack), stack->capacity);
}
