#include <stdio.h>
#include "doubly_linked_list.h"

int main() {
    printf("===== 이중 연결 리스트 테스트 시작 =====\n\n");

    // 1. 리스트 생성 테스트
    printf("1. 리스트 생성 테스트\n");
    DLLP list = dll_create();
    printf("리스트 생성 성공!\n");
    printf("초기 상태: ");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("비어있음 확인: %s\n", dll_is_empty(&list) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 2. 맨 앞 삽입 테스트
    printf("2. 맨 앞 삽입 테스트\n");
    dll_push_front(&list, 10);
    printf("10 삽입 후: ");
    dll_print_forward(&list);
    dll_print_backward(&list);

    dll_push_front(&list, 20);
    printf("20 삽입 후: ");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 3. 맨 뒤 삽입 테스트
    printf("3. 맨 뒤 삽입 테스트\n");
    dll_push_back(&list, 5);
    printf("5 삽입 후: ");
    dll_print_forward(&list);
    dll_print_backward(&list);

    dll_push_back(&list, 1);
    printf("1 삽입 후: ");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 4. 값 탐색 테스트
    printf("4. 값 탐색 테스트\n");
    DLLNode* found = dll_find(&list, 10);
    printf("10 탐색: %s\n", found ? "찾음" : "못 찾음");

    found = dll_find(&list, 5);
    printf("5 탐색: %s\n", found ? "찾음" : "못 찾음");

    found = dll_find(&list, 100);
    printf("100 탐색: %s\n", found ? "찾음" : "못 찾음");
    printf("\n");

    // 5. 맨 앞 삭제 테스트
    printf("5. 맨 앞 삭제 테스트\n");
    printf("현재 리스트: ");
    dll_print_forward(&list);

    int deleted_value;
    int result = dll_pop_front(&list, &deleted_value);
    if (result) {
        printf("삭제된 값: %d\n", deleted_value);
        printf("삭제 후: ");
        dll_print_forward(&list);
        dll_print_backward(&list);
    }
    else {
        printf("삭제 실패\n");
    }
    printf("\n");

    // 6. 맨 뒤 삭제 테스트
    printf("6. 맨 뒤 삭제 테스트\n");
    printf("현재 리스트: ");
    dll_print_forward(&list);

    result = dll_pop_back(&list, &deleted_value);
    if (result) {
        printf("삭제된 값: %d\n", deleted_value);
        printf("삭제 후: ");
        dll_print_forward(&list);
        dll_print_backward(&list);
    }
    else {
        printf("삭제 실패\n");
    }
    printf("\n");

    // 7. 양방향 출력 집중 테스트
    printf("7. 양방향 출력 집중 테스트\n");
    // 더 많은 데이터 추가
    dll_push_back(&list, 100);
    dll_push_back(&list, 200);
    dll_push_front(&list, 50);
    printf("50, 100, 200 추가 후:\n");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 8. 경계 조건 테스트 - 모든 요소 삭제
    printf("8. 경계 조건 테스트 - 모든 요소 삭제\n");
    printf("현재 리스트: ");
    dll_print_forward(&list);

    while (!dll_is_empty(&list)) {
        result = dll_pop_front(&list, &deleted_value);
        if (result) {
            printf("삭제된 값: %d\n", deleted_value);
            if (!dll_is_empty(&list)) {
                dll_print_forward(&list);
            }
        }
    }
    printf("모든 요소 삭제 완료\n");
    dll_print_forward(&list);
    printf("비어있음 확인: %s\n", dll_is_empty(&list) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 9. 에러 상황 테스트 - 빈 리스트에서 삭제
    printf("9. 에러 상황 테스트 - 빈 리스트에서 삭제 시도\n");
    printf("빈 리스트에서 맨 앞 삭제 시도:\n");
    result = dll_pop_front(&list, &deleted_value);
    printf("결과: %s\n", result ? "성공" : "실패");

    printf("빈 리스트에서 맨 뒤 삭제 시도:\n");
    result = dll_pop_back(&list, &deleted_value);
    printf("결과: %s\n", result ? "성공" : "실패");
    printf("\n");

    // 10. 단일 노드 테스트
    printf("10. 단일 노드 테스트\n");
    dll_push_front(&list, 99);
    printf("단일 노드 삽입 후: ");
    dll_print_forward(&list);
    dll_print_backward(&list);

    result = dll_pop_back(&list, &deleted_value);
    if (result) {
        printf("단일 노드 삭제: %d\n", deleted_value);
        dll_print_forward(&list);
        dll_print_backward(&list);
    }
    printf("\n");

    // 11. 이중 연결 특성 테스트
    printf("11. 이중 연결 특성 집중 테스트\n");
    // 앞뒤 삽입을 섞어서 테스트
    dll_push_front(&list, 30);
    dll_push_back(&list, 40);
    dll_push_front(&list, 20);
    dll_push_back(&list, 50);
    dll_push_front(&list, 10);

    printf("앞뒤 삽입 혼합 후:\n");
    dll_print_forward(&list);
    dll_print_backward(&list);

    // 앞뒤 삭제를 섞어서 테스트
    dll_pop_front(&list, &deleted_value);
    printf("앞 삭제(%d) 후: ", deleted_value);
    dll_print_forward(&list);

    dll_pop_back(&list, &deleted_value);
    printf("뒤 삭제(%d) 후: ", deleted_value);
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 12. 불변식 검사 테스트
    printf("12. 불변식 검사 테스트\n");
    printf("현재 리스트: ");
    dll_print_forward(&list);
    printf("불변식 검사 실행 중...\n");
    // 불변식 검사는 각 삽입/삭제 연산 후 자동으로 실행됨
    printf("불변식 검사 완료 (에러 메시지가 없으면 정상)\n");
    printf("\n");

    // 13. 메모리 해제
    printf("13. 메모리 해제\n");
    dll_free(&list);
    printf("리스트 메모리 해제 완료\n");
    dll_print_forward(&list);
    dll_print_backward(&list);
    printf("\n");

    // 14. NULL 포인터 안전성 테스트
    printf("14. NULL 포인터 안전성 테스트\n");
    dll_push_front(NULL, 10);
    dll_push_back(NULL, 10);
    result = dll_pop_front(NULL, &deleted_value);
    printf("NULL 리스트에서 pop_front 결과: %s\n", result ? "성공" : "실패");
    result = dll_pop_back(NULL, &deleted_value);
    printf("NULL 리스트에서 pop_back 결과: %s\n", result ? "성공" : "실패");
    dll_print_forward(NULL);
    dll_print_backward(NULL);
    printf("NULL 포인터 테스트 완료\n");

    printf("\n===== 이중 연결 리스트 테스트 완료 =====\n");
    return 0;
}