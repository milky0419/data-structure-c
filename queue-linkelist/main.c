#include <stdio.h>
#include "queue_linkedlist.h"

int main() {
    printf("===== 연결 리스트 기반 큐 테스트 시작 =====\n\n");

    // 1. 큐 생성 테스트
    printf("1. 큐 생성 테스트\n");
    QLP queue = ql_create();
    printf("큐 생성 성공!\n");
    printf("초기 상태: ");
    ql_print(&queue);
    printf("비어있음 확인: %s\n", ql_is_empty(&queue) ? "비어있음" : "비어있지 않음");
    printf("초기 크기: %d\n", ql_size(&queue));
    printf("\n");

    // 2. enqueue 기본 테스트
    printf("2. enqueue 기본 테스트\n");
    int result = ql_enqueue(&queue, 10);
    printf("10 enqueue 결과: %s\n", result ? "성공" : "실패");
    ql_print(&queue);

    result = ql_enqueue(&queue, 20);
    printf("20 enqueue 결과: %s\n", result ? "성공" : "실패");
    ql_print(&queue);

    result = ql_enqueue(&queue, 30);
    printf("30 enqueue 결과: %s\n", result ? "성공" : "실패");
    ql_print(&queue);
    printf("\n");

    // 3. dequeue 기본 테스트
    printf("3. dequeue 기본 테스트\n");
    printf("dequeue 전 상태: ");
    ql_print(&queue);

    int dequeue_value;
    result = ql_dequeue(&queue, &dequeue_value);
    if (result) {
        printf("dequeue 결과: %d\n", dequeue_value);
        printf("dequeue 후 상태: ");
        ql_print(&queue);
    }
    else {
        printf("dequeue 실패\n");
    }
    printf("\n");

    // 4. FIFO(First In First Out) 특성 테스트
    printf("4. FIFO 특성 테스트\n");
    printf("현재 큐 상태: ");
    ql_print(&queue);

    printf("순서대로 enqueue: 40, 50\n");
    ql_enqueue(&queue, 40);
    ql_enqueue(&queue, 50);
    ql_print(&queue);

    printf("dequeue 순서 확인:\n");
    for (int i = 0; i < 4; i++) {
        result = ql_dequeue(&queue, &dequeue_value);
        if (result) {
            printf("dequeue %d: %d\n", i + 1, dequeue_value);
        }
    }
    printf("FIFO 특성: 20 -> 30 -> 40 -> 50 순서로 나와야 함\n");
    printf("\n");

    // 5. 큐 상태 확인 테스트
    printf("5. 큐 상태 확인 테스트\n");
    printf("현재 큐 크기: %d\n", ql_size(&queue));
    printf("비어있음: %s\n", ql_is_empty(&queue) ? "예" : "아니오");
    ql_print(&queue);
    printf("\n");

    // 6. 동적 확장 테스트 (배열과 달리 크기 제한 없음)
    printf("6. 동적 확장 테스트\n");
    printf("많은 요소 추가하기 (배열과 달리 크기 제한 없음)...\n");

    int enqueue_count = 0;
    for (int i = 100; i <= 150; i += 5) {
        result = ql_enqueue(&queue, i);
        if (result) {
            enqueue_count++;
        }
        else {
            printf("enqueue 실패: %d\n", i);
            break;
        }
    }
    printf("%d개 요소 추가 완료\n", enqueue_count);
    printf("최종 크기: %d\n", ql_size(&queue));
    ql_print(&queue);
    printf("\n");

    // 7. 메모리 할당 확인 (연결 리스트의 장점)
    printf("7. 메모리 할당 확인\n");
    printf("더 많은 요소 추가 시도...\n");
    int large_enqueue_count = 0;
    for (int i = 1000; i < 1020; i++) {
        result = ql_enqueue(&queue, i);
        if (result) {
            large_enqueue_count++;
        }
        else {
            printf("메모리 할당 실패: %d\n", i);
            break;
        }
    }
    printf("%d개 추가 요소 enqueue 완료\n", large_enqueue_count);
    printf("총 크기: %d\n", ql_size(&queue));
    printf("앞쪽 5개 요소만 출력:\n");

    // 앞쪽 몇 개만 출력 (전체 출력은 너무 길어서)
    QLNode* cur = queue.front;
    for (int i = 0; i < 5 && cur; i++) {
        printf("  [%d]: %d\n", i, cur->data);
        cur = cur->next;
    }
    printf("  ... (총 %d개)\n", ql_size(&queue));
    printf("\n");

    // 8. 부분 dequeue 후 enqueue 테스트
    printf("8. 부분 dequeue 후 enqueue 테스트\n");
    printf("10개 dequeue 후 새로운 요소 추가\n");

    for (int i = 0; i < 10; i++) {
        ql_dequeue(&queue, &dequeue_value);
    }
    printf("10개 dequeue 후 크기: %d\n", ql_size(&queue));

    // 새로운 요소들 추가
    for (int i = 200; i < 205; i++) {
        ql_enqueue(&queue, i);
    }
    printf("5개 새 요소 추가 후 크기: %d\n", ql_size(&queue));

    // 앞쪽과 뒤쪽 확인
    printf("현재 front 5개: ");
    cur = queue.front;
    for (int i = 0; i < 5 && cur; i++) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    printf("\n");

    // 9. 모든 요소 dequeue 테스트
    printf("9. 모든 요소 dequeue 테스트\n");
    printf("전체 요소 dequeue 시작...\n");

    int dequeue_count = 0;
    while (!ql_is_empty(&queue)) {
        result = ql_dequeue(&queue, &dequeue_value);
        if (result) {
            dequeue_count++;
            if (dequeue_count <= 5 || dequeue_count % 10 == 0) { // 처음 5개와 10개마다 출력
                printf("dequeue[%d]: %d (남은 크기: %d)\n",
                    dequeue_count, dequeue_value, ql_size(&queue));
            }
        }
        else {
            break;
        }
    }
    printf("총 %d개 요소 dequeue 완료\n", dequeue_count);
    printf("최종 상태: ");
    ql_print(&queue);
    printf("비어있음 확인: %s\n", ql_is_empty(&queue) ? "비어있음" : "비어있지 않음");
    printf("\n");

    // 10. 빈 큐에서 dequeue 시도 (언더플로우 테스트)
    printf("10. 빈 큐에서 dequeue 시도 (언더플로우 테스트)\n");
    result = ql_dequeue(&queue, &dequeue_value);
    printf("빈 큐 dequeue 결과: %s\n", result ? "성공" : "실패");
    printf("\n");

    // 11. 단일 노드 테스트
    printf("11. 단일 노드 테스트\n");
    printf("단일 노드 enqueue 후 dequeue\n");
    ql_enqueue(&queue, 99);
    printf("99 enqueue 후: ");
    ql_print(&queue);

    result = ql_dequeue(&queue, &dequeue_value);
    if (result) {
        printf("단일 노드 dequeue: %d\n", dequeue_value);
        ql_print(&queue);
    }
    printf("단일 노드에서 front==rear 상태 확인 완료\n");
    printf("\n");

    // 12. 연결 리스트 특성 테스트 (크기 제한 없음)
    printf("12. 연결 리스트 특성 테스트\n");
    printf("배열 기반과 달리 이론적으로 크기 제한이 없음을 확인\n");

    // 적당한 크기로 테스트
    for (int i = 1; i <= 15; i++) {
        ql_enqueue(&queue, i * 3); // 3의 배수들 추가
    }
    printf("15개 요소 추가 완료, 크기: %d\n", ql_size(&queue));
    ql_print(&queue);

    // 앞쪽 절반 제거
    for (int i = 0; i < 7; i++) {
        ql_dequeue(&queue, &dequeue_value);
    }
    printf("7개 제거 후 크기: %d\n", ql_size(&queue));
    ql_print(&queue);

    // 뒤쪽에 새로운 요소 추가
    for (int i = 50; i < 53; i++) {
        ql_enqueue(&queue, i);
    }
    printf("3개 추가 후: ");
    ql_print(&queue);
    printf("\n");

    // 13. 불변식 검사 테스트
    printf("13. 불변식 검사 테스트\n");
    printf("현재 큐 상태에서 불변식 검사...\n");
    ql_print(&queue);
    printf("불변식 검사 완료 (에러 메시지가 없으면 정상)\n");
    printf("\n");

    // 14. 메모리 해제
    printf("14. 메모리 해제\n");
    ql_free(&queue);
    printf("큐 메모리 해제 완료\n");
    ql_print(&queue);
    printf("해제 후 크기: %d\n", ql_size(&queue));
    printf("\n");

    // 15. NULL 포인터 안전성 테스트
    printf("15. NULL 포인터 안전성 테스트\n");
    result = ql_enqueue(NULL, 10);
    printf("NULL 큐에 enqueue 결과: %s\n", result ? "성공" : "실패");

    result = ql_dequeue(NULL, &dequeue_value);
    printf("NULL 큐에서 dequeue 결과: %s\n", result ? "성공" : "실패");

    ql_print(NULL);
    printf("NULL 포인터 테스트 완료\n");

    printf("\n===== 연결 리스트 기반 큐 테스트 완료 =====\n");
    return 0;
}
