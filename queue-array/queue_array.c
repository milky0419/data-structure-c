#include "queue_array.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free를 사용하기 위함

/* ===== 큐 생성 ===== */

/* 새로운 큐 생성 및 초기화 */
QAP qa_create() {
    QAP queue = (QAP)malloc(sizeof(QueueArray));

    if (!queue) { // 동적 할당 실패 시
        printf("메모리 할당 실패\n");
        return NULL;
    }

    queue->front = 0;
    queue->rear = -1; // 빈 큐 상태
    queue->size = 0;
    queue->capacity = QUEUE_MAX_SIZE;

    return queue;
}

/* ===== 불변식 검사(추가 기능) ===== */
// front, rear, size가 유효한 범위에 있는지 검사
// 원형 큐의 상태 일관성 검사
static void qa_check_invariants(const QAP queue) {
    if (!queue) { // 큐가 존재하지 않을 때
        printf("invariant failed: queue does not exist\n");
        return;
    }

    // 1) 인덱스가 유효한 범위에 있는지 검사
    if (queue->front < 0 || queue->front >= queue->capacity) {
        printf("invariant failed: front index out of range (front=%d, capacity=%d)\n",
            queue->front, queue->capacity);
    }

    if (queue->rear < -1 || queue->rear >= queue->capacity) {
        printf("invariant failed: rear index out of range (rear=%d, capacity=%d)\n",
            queue->rear, queue->capacity);
    }

    // 2) size가 유효한 범위에 있는지 검사
    if (queue->size < 0 || queue->size > queue->capacity) {
        printf("invariant failed: size out of range (size=%d, capacity=%d)\n",
            queue->size, queue->capacity);
    }

    // 3) 빈 큐일 때 size == 0인지 검사
    if (queue->size == 0) {
        if (queue->rear != -1) {
            printf("invariant failed: empty queue rear should be -1 (rear=%d)\n",
                queue->rear);
        }
    }

    // 4) 가득 찬 큐일 때 size == capacity인지 검사
    if (queue->size == queue->capacity) {
        // 가득 찬 상태: 정상
    }
}

/* ===== 큐 상태 확인 ===== */

/* 비어 있는지 확인 */
int qa_is_empty(const QAP queue) {
    if (!queue) { // 큐가 존재하지 않으면
        return 1; // 비어있다고 간주
    }
    return (queue->size == 0) ? 1 : 0;
}

/* 가득 찼는지 확인 */
int qa_is_full(const QAP queue) {
    if (!queue) { // 큐가 존재하지 않으면
        return 0; // 가득 차지 않았다고 간주
    }
    return (queue->size == queue->capacity) ? 1 : 0;
}

/* 현재 큐에 저장된 요소 개수 반환 */
int qa_size(const QAP queue) {
    if (!queue) {
        return 0;
    }
    return queue->size;
}

/* ===== 큐 기본 연산 ===== */

/* 데이터 삽입: 성공 시 1, 실패 시 0 */
int qa_enqueue(QAP queue, int value) {
    if (!queue) {
        printf("큐가 존재하지 않습니다\n");
        return 0; // 실패
    }

    if (qa_is_full(queue)) {
        printf("큐가 가득 찼습니다\n");
        return 0; // 실패
    }

    // 원형 큐: rear를 다음 위치로 이동 (순환)
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;

    qa_check_invariants(queue); // 불변식 검사
    return 1; // 성공
}

/* 데이터 제거 및 반환: 성공 시 1, 실패 시 0 */
int qa_dequeue(QAP queue, int* out) {
    if (!queue) {
        printf("큐가 존재하지 않습니다\n");
        return 0; // 실패
    }

    if (qa_is_empty(queue)) {
        printf("큐가 비어있습니다\n");
        return 0; // 실패
    }

    if (out) {
        *out = queue->data[queue->front];
    }

    // 원형 큐: front를 다음 위치로 이동 (순환)
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    // 큐가 비어지면 rear를 -1로 초기화
    if (queue->size == 0) {
        queue->front = 0;
        queue->rear = -1;
    }

    qa_check_invariants(queue); // 불변식 검사
    return 1; // 성공
}

/* ===== 큐 출력 ===== */
// front->rear 순서
void qa_print(const QAP queue) {
    if (!queue) {
        printf("큐가 존재하지 않습니다\n");
        return;
    }

    if (qa_is_empty(queue)) {
        printf("큐가 비어있습니다\n");
        return;
    }

    printf("큐 [front -> rear]: [ ");
    int current = queue->front;
    for (int i = 0; i < queue->size; i++) {
        printf("%d", queue->data[current]);
        if (i < queue->size - 1) {
            printf(" -> ");
        }
        current = (current + 1) % queue->capacity; // 원형 순환
    }
    printf(" ]\n");
    printf("크기: %d/%d, front=%d, rear=%d\n",
        queue->size, queue->capacity, queue->front, queue->rear);
}

/* ===== 메모리 해제 ===== */
void qa_free(QAP queue) {
    if (!queue) {
        return;
    }

    free(queue);
    queue = NULL; // free 후 포인터를 NULL로 설정
}
