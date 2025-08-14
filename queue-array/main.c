#include <stdio.h>
#include "queue_array.h"

int main() {
    printf("===== 배열 기반 원형 큐 테스트 시작 =====\n\n");

    // 1. 큐 생성 테스트
    printf("1. 큐 생성 테스트\n");
    QAP queue = qa_create();
    if (queue) {
        printf("큐 생성 성공!\n");
        printf("초기 상태: ");
        qa_print(queue);
        printf("비어있음 확인: %s\n", qa_is_empty(queue) ? "비어있음" : "비어있지 않음");
        printf("가득참 확인: %s\n", qa_is_full(queue) ? "가득참" : "가득차지 않음");
    }
    else {
        printf("큐 생성 실패!\n");
        return -1;
    }
    printf("\n");

    // 2. enqueue 기본 테스트
    printf("2. enqueue 기본 테스트\n");
    int result = qa_enqueue(queue, 10);
    printf("10 enqueue 결과: %s\n", result ? "성공" : "실패");
    qa_print(queue);

    result = qa_enqueue(queue, 20);
    printf("20 enqueue 결과: %s\n", result ? "성공" : "실패");
    qa_print(queue);

    result = qa_enqueue(queue, 30);
    printf("30 enqueue 결과: %s\n", result ? "성공" : "실패");
    qa_print(queue);
    printf("\n");

    // 3. dequeue 기본 테스트
    printf("3. dequeue 기본 테스트\n");
    printf("dequeue 전 상태: ");
    qa_print(queue);

    int dequeue_value;
    result = qa_dequeue(queue, &dequeue_value);
    if (result) {
        printf("dequeue 결과: %d\n", dequeue_value);
        printf("dequeue 후 상태: ");
        qa_print(queue);
    }
    else {
        printf("dequeue 실패\n");
    }
    printf("\n");

    // 4. FIFO(First In First Out) 특성 테스트
    printf("4. FIFO 특성 테스트\n");
    printf("현재 큐 상태: ");
    qa_print(queue);

    printf("순서대로 enqueue: 40, 50\n");
    qa_enqueue(queue, 40);
    qa_enqueue(queue, 50);
    qa_print(queue);

    printf("dequeue 순서 확인:\n");
    for (int i = 0; i < 4; i++) {
        result = qa_dequeue(queue, &dequeue_value);
        if (result) {
            printf("dequeue %d: %d\n", i + 1, dequeue_value);
        }
    }
    printf("FIFO 특성: 20 -> 30 -> 40 -> 50 순서로 나와야 함\n");
    printf("\n");

    // 5. 큐 상태 확인 테스트
    printf("5. 큐 상태 확인 테스트\n");
    printf("현재 큐 크기: %d\n", qa_size(queue));
    printf("비어있음: %s\n", qa_is_empty(queue) ? "예" : "아니오");
    printf("가득참: %s\n", qa_is_full(queue) ? "예" : "아니오");
    qa_print(queue);
    printf("\n");

    // 6. 큐 가득 찰 때까지 enqueue 테스트
    printf("6. 큐 가득 찰 때까지 enqueue 테스트\n");
    printf("최대 크기: %d\n", QUEUE_MAX_SIZE);
    printf("남은 공간에 데이터 채우기...\n");

    int enqueue_count = 0;
    for (int i = 100; i < 200; i += 10) {
        result = qa_enqueue(queue, i);
        if (result) {
            enqueue_count++;
            printf("enqueue %d: 성공\n", i);
        }
        else {
            printf("enqueue %d: 실패 (큐 가득참)\n", i);
            break;
        }
    }
    printf("%d개 요소 추가 완료\n", enqueue_count);
    printf("최종 크기: %d\n", qa_size(queue));
    printf("가득참 확인: %s\n", qa_is_full(queue) ? "가득함" : "가득차지 않음");
    qa_print(queue);
    printf("\n");

    // 7. 가득 찬 큐에 enqueue 시도 (오버플로우 테스트)
    printf("7. 가득 찬 큐에 enqueue 시도 (오버플로우 테스트)\n");
    result = qa_enqueue(queue, 999);
    printf("오버플로우 enqueue 결과: %s\n", result ? "성공" : "실패");
    printf("큐 크기 확인: %d\n", qa_size(queue));
    printf("\n");

    // 8. 원형 큐 특성 테스트 (부분 dequeue 후 enqueue)
    printf("8. 원형 큐 특성 테스트\n");
    printf("몇 개 dequeue 후 다시 enqueue하여 원형 특성 확인\n");

    // 몇 개 dequeue
    printf("3개 dequeue:\n");
    for (int i = 0; i < 3; i++) {
        result = qa_dequeue(queue, &dequeue_value);
        if (result) {
            printf("dequeue: %d\n", dequeue_value);
        }
    }
    qa_print(queue);

    // 다시 enqueue
    printf("2개 enqueue (500, 600):\n");
    qa_enqueue(queue, 500);
    qa_enqueue(queue, 600);
    qa_print(queue);
    printf("원형 큐 동작: rear가 배열 처음 부분으로 순환했는지 확인\n");
    printf("\n");

    // 9. 모든 요소 dequeue (언더플로우까지)
    printf("9. 모든 요소 dequeue 테스트\n");
    printf("전체 요소 dequeue 시작...\n");

    int dequeue_count = 0;
    while (!qa_is_empty(queue)) {
        result = qa_dequeue(queue, &dequeue_value);
        if (result) {
            dequeue_count++;
            printf("dequeue[%d]: %d (남은 크기: %d)\n",
                dequeue_count, dequeue_value, qa_size(queue));
        }
        else {
            break;
        }
    }
    printf("총 %d개 요소 dequeue 완료\n", dequeue_count);
    printf("최종 상태: ");
    qa_print(queue);
    printf("비어있음 확인: %s\n", qa_is_empty(queue) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 10. 빈 큐에서 dequeue 시도 (언더플로우 테스트)
    printf("10. 빈 큐에서 dequeue 시도 (언더플로우 테스트)\n");
    result = qa_dequeue(queue, &dequeue_value);
    printf("빈 큐 dequeue 결과: %s\n", result ? "성공" : "실패");
    printf("\n");

    // 11. 큐 재사용 테스트 (빈 큐 상태에서 다시 채우기)
    printf("11. 큐 재사용 테스트\n");
    printf("빈 큐 상태에서 다시 데이터 추가\n");

    for (int i = 1; i <= 5; i++) {
        qa_enqueue(queue, i * 11); // 11의 배수들 추가
    }
    printf("5개 요소 추가 후: ");
    qa_print(queue);

    // 일부 dequeue
    qa_dequeue(queue, &dequeue_value);
    qa_dequeue(queue, &dequeue_value);
    printf("2개 dequeue 후: ");
    qa_print(queue);

    // 다시 추가
    qa_enqueue(queue, 77);
    qa_enqueue(queue, 88);
    printf("2개 추가 후: ");
    qa_print(queue);
    printf("\n");

    // 12. 불변식 검사 테스트
    printf("12. 불변식 검사 테스트\n");
    printf("현재 큐 상태에서 불변식 검사...\n");
    qa_print(queue);
    printf("불변식 검사 완료 (에러 메시지가 없으면 정상)\n");
    printf("\n");

    // 13. 메모리 해제
    printf("13. 메모리 해제\n");
    qa_free(queue);
    printf("큐 메모리 해제 완료\n");
    printf("\n");

    // 14. NULL 포인터 안전성 테스트
    printf("14. NULL 포인터 안전성 테스트\n");
    result = qa_enqueue(NULL, 10);
    printf("NULL 큐에 enqueue 결과: %s\n", result ? "성공" : "실패");

    result = qa_dequeue(NULL, &dequeue_value);
    printf("NULL 큐에서 dequeue 결과: %s\n", result ? "성공" : "실패");

    qa_print(NULL);
    printf("NULL 포인터 테스트 완료\n");

    printf("\n===== 배열 기반 원형 큐 테스트 완료 =====\n");
    return 0;
}