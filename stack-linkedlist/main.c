#include <stdio.h>
#include "stack_linkedlist.h"

int main() {
    printf("===== 연결 리스트 기반 스택 테스트 시작 =====\n\n");

    // 1. 스택 생성 테스트
    printf("1. 스택 생성 테스트\n");
    SLP stack = sl_create();
    printf("스택 생성 성공!\n");
    printf("초기 상태: ");
    sl_print(&stack);
    printf("비어있음 확인: %s\n", sl_is_empty(&stack) ? "비어있음" : "비어있지 않음");
    printf("초기 크기: %d\n", sl_size(&stack));
    printf("\n");

    // 2. push 기본 테스트
    printf("2. push 기본 테스트\n");
    int result = sl_push(&stack, 10);
    printf("10 push 결과: %s\n", result ? "성공" : "실패");
    sl_print(&stack);

    result = sl_push(&stack, 20);
    printf("20 push 결과: %s\n", result ? "성공" : "실패");
    sl_print(&stack);

    result = sl_push(&stack, 30);
    printf("30 push 결과: %s\n", result ? "성공" : "실패");
    sl_print(&stack);
    printf("\n");

    // 3. peek 테스트
    printf("3. peek 테스트\n");
    int peek_value;
    result = sl_peek(&stack, &peek_value);
    if (result) {
        printf("peek 결과: %d (스택은 변경되지 않음)\n", peek_value);
        sl_print(&stack);
    }
    else {
        printf("peek 실패\n");
    }
    printf("\n");

    // 4. pop 기본 테스트
    printf("4. pop 기본 테스트\n");
    printf("pop 전 상태: ");
    sl_print(&stack);

    int pop_value;
    result = sl_pop(&stack, &pop_value);
    if (result) {
        printf("pop 결과: %d\n", pop_value);
        printf("pop 후 상태: ");
        sl_print(&stack);
    }
    else {
        printf("pop 실패\n");
    }
    printf("\n");

    // 5. 스택 상태 확인 테스트
    printf("5. 스택 상태 확인 테스트\n");
    printf("현재 스택 크기: %d\n", sl_size(&stack));
    printf("비어있음: %s\n", sl_is_empty(&stack) ? "예" : "아니오");
    sl_print(&stack);
    printf("\n");

    // 6. 동적 확장 테스트 (배열과 달리 크기 제한 없음)
    printf("6. 동적 확장 테스트\n");
    printf("많은 요소 추가하기 (배열과 달리 크기 제한 없음)...\n");

    int push_count = 0;
    for (int i = 100; i <= 150; i += 5) {
        result = sl_push(&stack, i);
        if (result) {
            push_count++;
        }
        else {
            printf("push 실패: %d\n", i);
            break;
        }
    }
    printf("%d개 요소 추가 완료\n", push_count);
    printf("최종 크기: %d\n", sl_size(&stack));
    sl_print(&stack);
    printf("\n");

    // 7. 메모리 할당 확인 (연결 리스트의 장점)
    printf("7. 메모리 할당 확인\n");
    printf("더 많은 요소 추가 시도...\n");
    int large_push_count = 0;
    for (int i = 1000; i < 1020; i++) {
        result = sl_push(&stack, i);
        if (result) {
            large_push_count++;
        }
        else {
            printf("메모리 할당 실패: %d\n", i);
            break;
        }
    }
    printf("%d개 추가 요소 push 완료\n", large_push_count);
    printf("총 크기: %d\n", sl_size(&stack));
    printf("상위 5개 요소만 출력:\n");

    // 상위 몇 개만 출력 (전체 출력은 너무 길어서)
    SLNode* cur = stack.top;
    for (int i = 0; i < 5 && cur; i++) {
        printf("  [%d]: %d\n", i, cur->data);
        cur = cur->next;
    }
    printf("  ... (총 %d개)\n", sl_size(&stack));
    printf("\n");

    // 8. 모든 요소 pop 테스트
    printf("8. 모든 요소 pop 테스트\n");
    printf("전체 요소 pop 시작...\n");

    int pop_count = 0;
    while (!sl_is_empty(&stack)) {
        result = sl_pop(&stack, &pop_value);
        if (result) {
            pop_count++;
            if (pop_count <= 5 || pop_count % 10 == 0) { // 처음 5개와 10개마다 출력
                printf("pop[%d]: %d (남은 크기: %d)\n", pop_count, pop_value, sl_size(&stack));
            }
        }
        else {
            break;
        }
    }
    printf("총 %d개 요소 pop 완료\n", pop_count);
    printf("최종 상태: ");
    sl_print(&stack);
    printf("비어있음 확인: %s\n", sl_is_empty(&stack) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 9. 빈 스택에서 pop/peek 시도 (언더플로우 테스트)
    printf("9. 빈 스택에서 pop/peek 시도 (언더플로우 테스트)\n");
    result = sl_pop(&stack, &pop_value);
    printf("빈 스택 pop 결과: %s\n", result ? "성공" : "실패");

    result = sl_peek(&stack, &peek_value);
    printf("빈 스택 peek 결과: %s\n", result ? "성공" : "실패");
    printf("\n");

    // 10. LIFO(Last In First Out) 특성 테스트
    printf("10. LIFO 특성 테스트\n");
    printf("순서대로 push: 100, 200, 300\n");
    sl_push(&stack, 100);
    sl_push(&stack, 200);
    sl_push(&stack, 300);
    sl_print(&stack);

    printf("pop 순서 확인:\n");
    for (int i = 0; i < 3; i++) {
        result = sl_pop(&stack, &pop_value);
        if (result) {
            printf("pop %d: %d\n", i + 1, pop_value);
        }
    }
    printf("LIFO 특성: 300 -> 200 -> 100 순서로 나와야 함\n");
    printf("\n");

    // 11. 연결 리스트 특성 테스트 (크기 제한 없음)
    printf("11. 연결 리스트 특성 테스트\n");
    printf("배열 기반과 달리 이론적으로 크기 제한이 없음을 확인\n");

    // 적당한 크기로 테스트
    for (int i = 1; i <= 15; i++) {
        sl_push(&stack, i * 7); // 7의 배수들 추가
    }
    printf("15개 요소 추가 완료, 크기: %d\n", sl_size(&stack));
    sl_print(&stack);

    // 일부만 제거
    for (int i = 0; i < 5; i++) {
        sl_pop(&stack, &pop_value);
    }
    printf("5개 제거 후 크기: %d\n", sl_size(&stack));
    sl_print(&stack);
    printf("\n");

    // 12. 불변식 검사 테스트
    printf("12. 불변식 검사 테스트\n");
    printf("현재 스택 상태에서 불변식 검사...\n");
    sl_print(&stack);
    printf("불변식 검사 완료 (에러 메시지가 없으면 정상)\n");
    printf("\n");

    // 13. 메모리 해제
    printf("13. 메모리 해제\n");
    sl_free(&stack);
    printf("스택 메모리 해제 완료\n");
    sl_print(&stack);
    printf("해제 후 크기: %d\n", sl_size(&stack));
    printf("\n");

    // 14. NULL 포인터 안전성 테스트
    printf("14. NULL 포인터 안전성 테스트\n");
    result = sl_push(NULL, 10);
    printf("NULL 스택에 push 결과: %s\n", result ? "성공" : "실패");

    result = sl_pop(NULL, &pop_value);
    printf("NULL 스택에서 pop 결과: %s\n", result ? "성공" : "실패");

    result = sl_peek(NULL, &peek_value);
    printf("NULL 스택에서 peek 결과: %s\n", result ? "성공" : "실패");

    sl_print(NULL);
    printf("NULL 포인터 테스트 완료\n");

    printf("\n===== 연결 리스트 기반 스택 테스트 완료 =====\n");
    return 0;
}
