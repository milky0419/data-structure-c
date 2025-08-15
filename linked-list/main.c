#include <stdio.h>
#include "linked_list.h"

int main() {
    printf("===== 단일 연결 리스트 테스트 시작 =====\n\n");

    // 1. 리스트 생성 테스트
    printf("1. 리스트 생성 테스트\n");
    LLP list = ll_create();
    printf("리스트 생성 성공!\n");
    printf("초기 상태: ");
    ll_print(&list);
    printf("비어있음 확인: %s\n", ll_is_empty(&list) ? "비어있음" : "비어있지 않음");
    ll_print(&list);
    printf("\n");

    // 2. 맨 앞 삽입 테스트
    printf("2. 맨 앞 삽입 테스트\n");
    ll_push_front(&list, 10);
    printf("10 삽입 후: ");
    ll_print(&list);

    ll_push_front(&list, 20);
    printf("20 삽입 후: ");
    ll_print(&list);
    printf("\n");

    // 3. 맨 뒤 삽입 테스트
    printf("3. 맨 뒤 삽입 테스트\n");
    ll_push_back(&list, 5);
    printf("5 삽입 후: ");
    ll_print(&list);

    ll_push_back(&list, 1);
    printf("1 삽입 후: ");
    ll_print(&list);
    printf("\n");

    // 4. 값 탐색 테스트
    printf("4. 값 탐색 테스트\n");
    LLNode* found = ll_find(&list, 10);
    printf("10 탐색: %s\n", found ? "찾음" : "못 찾음");

    found = ll_find(&list, 5);
    printf("5 탐색: %s\n", found ? "찾음" : "못 찾음");

    found = ll_find(&list, 100);
    printf("100 탐색: %s\n", found ? "찾음" : "못 찾음");
    printf("\n");

    // 5. 맨 앞 삭제 테스트
    printf("5. 맨 앞 삭제 테스트\n");
    printf("현재 리스트: ");
    ll_print(&list);

    int deleted_value;
    int result = ll_pop_front(&list, &deleted_value);
    if (result) {
        printf("삭제된 값: %d\n", deleted_value);
        printf("삭제 후: ");
        ll_print(&list);
    }
    else {
        printf("삭제 실패\n");
    }
    printf("\n");

    // 6. 맨 뒤 삭제 테스트
    printf("6. 맨 뒤 삭제 테스트\n");
    printf("현재 리스트: ");
    ll_print(&list);

    result = ll_pop_back(&list, &deleted_value);
    if (result) {
        printf("삭제된 값: %d\n", deleted_value);
        printf("삭제 후: ");
        ll_print(&list);
    }
    else {
        printf("삭제 실패\n");
    }
    printf("\n");

    // 7. 경계 조건 테스트 - 모든 요소 삭제
    printf("7. 경계 조건 테스트 - 모든 요소 삭제\n");
    printf("현재 리스트: ");
    ll_print(&list);

    while (!ll_is_empty(&list)) {
        result = ll_pop_front(&list, &deleted_value);
        if (result) {
            printf("삭제된 값: %d\n", deleted_value);
            if (!ll_is_empty(&list)) {
                ll_print(&list);
            }
        }
    }
    printf("모든 요소 삭제 완료\n");
    ll_print(&list);
    printf("비어있음 확인: %s\n", ll_is_empty(&list) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 8. 에러 상황 테스트 - 빈 리스트에서 삭제 시도
    printf("8. 에러 상황 테스트 - 빈 리스트에서 삭제 시도\n");
    printf("빈 리스트에서 맨 앞 삭제 시도:\n");
    result = ll_pop_front(&list, &deleted_value);
    printf("결과: %s\n", result ? "성공" : "실패");

    printf("빈 리스트에서 맨 뒤 삭제 시도:\n");
    result = ll_pop_back(&list, &deleted_value);
    printf("결과: %s\n", result ? "성공" : "실패");
    printf("\n");

    // 9. 단일 노드 테스트
    printf("9. 단일 노드 테스트\n");
    ll_push_front(&list, 99);
    printf("단일 노드 삽입 후: ");
    ll_print(&list);

    result = ll_pop_back(&list, &deleted_value);
    if (result) {
        printf("단일 노드 삭제: %d\n", deleted_value);
        ll_print(&list);
    }
    printf("\n");

    // 10. 최종 테스트 - 다양한 연산 조합
    printf("10. 최종 테스트 - 다양한 연산 조합\n");
    for (int i = 1; i <= 5; i++) {
        ll_push_back(&list, i * 10);
    }
    printf("1-5까지 10배수 삽입 후: ");
    ll_print(&list);

    ll_push_front(&list, 100);
    ll_push_front(&list, 200);
    printf("앞쪽에 100, 200 삽입 후: ");
    ll_print(&list);

    printf("탐색 테스트:\n");
    found = ll_find(&list, 30);
    printf("30 탐색: %s\n", found ? "찾음" : "못 찾음");
    found = ll_find(&list, 200);
    printf("200 탐색: %s\n", found ? "찾음" : "못 찾음");
    found = ll_find(&list, 999);
    printf("999 탐색: %s\n", found ? "찾음" : "못 찾음");
    printf("\n");

    // 11. 불변식 검사 테스트
    printf("11. 불변식 검사 테스트\n");
    printf("현재 리스트: ");
    ll_print(&list);
    printf("불변식 검사 실행 중...\n");
    // 불변식 검사는 각 삽입/삭제 연산 후 자동으로 실행됨
    printf("불변식 검사 완료 (에러 메시지가 없으면 정상)\n");
    printf("\n");

    // 12. 메모리 해제
    printf("12. 메모리 해제\n");
    ll_free(&list);
    printf("리스트 메모리 해제 완료\n");
    ll_print(&list);
    printf("\n");

    // 13. NULL 포인터 테스트
    printf("13. NULL 포인터 안전성 테스트\n");
    ll_push_front(NULL, 10);
    ll_push_back(NULL, 10);
    result = ll_pop_front(NULL, &deleted_value);
    printf("NULL 리스트에서 pop_front 결과: %s\n", result ? "성공" : "실패");
    result = ll_pop_back(NULL, &deleted_value);
    printf("NULL 리스트에서 pop_back 결과: %s\n", result ? "성공" : "실패");
    ll_print(NULL);
    printf("NULL 포인터 테스트 완료\n");

    printf("\n===== 단일 연결 리스트 테스트 완료 =====\n");
    return 0;
}