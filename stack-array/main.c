#include <stdio.h>
#include "stack_array.h"

int main() {
    printf("===== 배열 기반 스택 테스트 시작 =====\n\n");

    // 1. 스택 생성 테스트
    printf("1. 스택 생성 테스트\n");
    SAP stack = sa_create();
    if (stack) {
        printf("스택 생성 성공!\n");
        printf("초기 상태: ");
        sa_print(stack);
        printf("비어있음 확인: %s\n", sa_is_empty(stack) ? "비어있음" : "비어있지 않음");
        printf("가득참 확인: %s\n", sa_is_full(stack) ? "가득참" : "가득차지 않음");
    }
    else {
        printf("스택 생성 실패!\n");
        return 1;
    }
    printf("\n");

    // 2. push 기본 테스트
    printf("2. push 기본 테스트\n");
    int result = sa_push(stack, 10);
    printf("10 push 결과: %s\n", result ? "성공" : "실패");
    sa_print(stack);

    result = sa_push(stack, 20);
    printf("20 push 결과: %s\n", result ? "성공" : "실패");
    sa_print(stack);

    result = sa_push(stack, 30);
    printf("30 push 결과: %s\n", result ? "성공" : "실패");
    sa_print(stack);
    printf("\n");

    // 3. peek 테스트
    printf("3. peek 테스트\n");
    int peek_value;
    result = sa_peek(stack, &peek_value);
    if (result) {
        printf("peek 결과: %d\n", peek_value);
        sa_print(stack);
    }
    else {
        printf("peek 실패\n");
    }
    printf("\n");

    // 4. pop 기본 테스트
    printf("4. pop 기본 테스트\n");
    printf("pop 전 상태: ");
    sa_print(stack);

    int pop_value;
    result = sa_pop(stack, &pop_value);
    if (result) {
        printf("pop 결과: %d\n", pop_value);
        printf("pop 후 상태: ");
        sa_print(stack);
    }
    else {
        printf("pop 실패\n");
    }
    printf("\n");

    // 5. 스택 상태 확인 테스트
    printf("5. 스택 상태 확인 테스트\n");
    printf("현재 스택 크기: %d\n", sa_size(stack));
    printf("비어있음: %s\n", sa_is_empty(stack) ? "예" : "아니오");
    printf("가득참: %s\n", sa_is_full(stack) ? "예" : "아니오");
    sa_print(stack);
    printf("\n");

    // 6. 스택 가득 찰 때까지 push 테스트
    printf("6. 스택 가득 찰 때까지 push 테스트\n");
    printf("현재 크기: %d, 최대 크기: %d\n", sa_size(stack), STACK_MAX_SIZE);
    printf("남은 공간에 데이터 채우기...\n");

    int push_count = 0;
    for (int i = sa_size(stack); i < STACK_MAX_SIZE; i++) {
        result = sa_push(stack, i * 10);
        if (result) {
            push_count++;
        }
        else {
            printf("push 실패: %d\n", i * 10);
            break;
        }
    }
    printf("%d개 요소 추가 완료\n", push_count);
    printf("최종 크기: %d\n", sa_size(stack));
    printf("가득참 확인: %s\n", sa_is_full(stack) ? "가득참" : "가득차지 않음");
    printf("\n");

    // 7. 가득 찬 스택에 push 시도 (오버플로우 테스트)
    printf("7. 가득 찬 스택에 push 시도 (오버플로우 테스트)\n");
    result = sa_push(stack, 999);
    printf("오버플로우 push 결과: %s\n", result ? "성공" : "실패");
    printf("스택 크기 확인: %d\n", sa_size(stack));
    printf("\n");

    // 8. 모든 요소 pop (언더플로우까지)
    printf("8. 모든 요소 pop 테스트\n");
    printf("전체 요소 pop 시작...\n");

    int pop_count = 0;
    while (!sa_is_empty(stack)) {
        result = sa_pop(stack, &pop_value);
        if (result) {
            pop_count++;
            printf("pop[%d]: %d (남은 크기: %d)\n", pop_count, pop_value, sa_size(stack));
        }
        else {
            break;
        }
    }
    printf("총 %d개 요소 pop 완료\n", pop_count);
    printf("최종 상태: ");
    sa_print(stack);
    printf("비어있음 확인: %s\n", sa_is_empty(stack) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 9. 빈 스택에서 pop/peek 시도 (언더플로우 테스트)
    printf("9. 빈 스택에서 pop/peek 시도 (언더플로우 테스트)\n");
    result = sa_pop(stack, &pop_value);
    printf("빈 스택 pop 결과: %s\n", result ? "성공" : "실패");

    result = sa_peek(stack, &peek_value);
    printf("빈 스택 peek 결과: %s\n", result ? "성공" : "실패");
    printf("\n");

    // 10. LIFO(Last In First Out) 특성 테스트
    printf("10. LIFO 특성 테스트\n");
    printf("순서대로 push: 100, 200, 300\n");
    sa_push(stack, 100);
    sa_push(stack, 200);
    sa_push(stack, 300);
    sa_print(stack);

    printf("pop 순서 확인:\n");
    for (int i = 0; i < 3; i++) {
        result = sa_pop(stack, &pop_value);
        if (result) {
            printf("pop %d: %d\n", i + 1, pop_value);
        }
    }
    printf("LIFO 특성: 300 -> 200 -> 100 순서로 나와야 함\n");
    printf("\n");

    // 11. 불변식 검사 테스트
    printf("11. 불변식 검사 테스트\n");
    printf("몇 개 요소 추가 후 불변식 검사...\n");
    sa_push(stack, 50);
    sa_push(stack, 60);
    sa_push(stack, 70);
    sa_print(stack);
    printf("불변식 검사 완료 (에러 메시지가 없으면 정상)\n");
    printf("\n");

    // 12. 메모리 해제
    printf("12. 메모리 해제\n");
    sa_free(stack);
    printf("스택 메모리 해제 완료\n");
    printf("\n");

    // 13. NULL 포인터 안전성 테스트
    printf("13. NULL 포인터 안전성 테스트\n");
    result = sa_push(NULL, 10);
    printf("NULL 스택에 push 결과: %s\n", result ? "성공" : "실패");

    result = sa_pop(NULL, &pop_value);
    printf("NULL 스택에서 pop 결과: %s\n", result ? "성공" : "실패");

    result = sa_peek(NULL, &peek_value);
    printf("NULL 스택에서 peek 결과: %s\n", result ? "성공" : "실패");

    sa_print(NULL);
    printf("NULL 포인터 테스트 완료\n");

    printf("\n===== 배열 기반 스택 테스트 완료 =====\n");
}
