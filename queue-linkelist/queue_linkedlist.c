#include "queue_linkedlist.h"
#include <stdio.h>
#include <stdlib.h> // malloc, free를 사용하기 위함

/* ===== 큐 생성 ===== */

/* 빈 큐 생성 및 초기화 */
QLP ql_create() {
    QLP queue;
    queue.front = NULL;
    queue.rear = NULL;

    return queue;
}

/* 새 노드 동적 생성 */
static QLNode* ql_new_node(int value) {
    QLNode* n = (QLNode*)malloc(sizeof(QLNode));

    if (!n) // 동적 할당 실패 시
        return NULL; // NULL 반환

    n->data = value;
    n->next = NULL;

    return n;
}

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 큐일 때 front==NULL && rear==NULL인지 검사
// 빈 큐가 아닐 때 front와 rear 연결 상태 검사
// 단일 노드일 때 front==rear인지 검사
static void ql_check_invariants(const QLP* queue) {
    if (!queue) { // 큐가 존재하지 않을 때
        printf("invariant failed: queue does not exist\n");
        return; // 함수 종료
    }

    // 1) 빈 큐일 때: front/rear은 동시에 NULL이어야 함
    if (queue->front == NULL || queue->rear == NULL) {
        if (!(queue->front == NULL && queue->rear == NULL))
            printf("invariant failed: only one of front/rear is NULL (front=%p, rear=%p)\n",
                (void*)queue->front, (void*)queue->rear);
        return; // 빈 큐면 추가 검사 불필요
    }

    // 2) 단일 노드일 때: front == rear인지 검사
    if (queue->front == queue->rear) {
        if (queue->front->next != NULL) {
            printf("invariant failed: single node should have next==NULL\n");
        }
        return; // 단일 노드면 추가 검사 불필요
    }

    // 3) 다중 노드일 때: rear->next == NULL인지 검사
    if (queue->rear->next != NULL) {
        printf("invariant failed: rear->next must be NULL\n");
    }

    // 4) front에서 rear까지 연결 확인
    QLNode* cur = queue->front;
    int count = 0;
    while (cur && cur != queue->rear && count < 10000) { // 무한 루프 방지
        cur = cur->next;
        count++;
    }

    if (count >= 10000) {
        printf("invariant failed: possible circular reference in queue\n");
    }
    else if (cur != queue->rear) {
        printf("invariant failed: rear is not reachable from front\n");
    }
}

/* ===== 큐 상태 확인 ===== */

/* 비어 있는지 확인 */
int ql_is_empty(const QLP* queue) {
    if (!queue) { // 큐가 존재하지 않으면
        return 1; // 비어있다고 간주
    }
    return (queue->front == NULL) ? 1 : 0;
}

/* 현재 큐에 저장된 요소 개수 반환 */
int ql_size(const QLP* queue) {
    if (!queue || !queue->front) {
        return 0;
    }

    int count = 0;
    QLNode* cur = queue->front;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

/* ===== 큐 기본 연산 ===== */

/* 데이터 삽입: 성공 시 1, 실패 시 0 */
int ql_enqueue(QLP* queue, int value) {
    if (!queue) {
        printf("큐가 존재하지 않습니다\n");
        return 0; // 실패
    }

    QLNode* n = ql_new_node(value);
    if (!n) { // 메모리 부족 시
        printf("메모리 할당 실패\n");
        return 0; // 실패
    }

    if (ql_is_empty(queue)) { // 빈 큐일 때
        queue->front = queue->rear = n;
    }
    else {
        queue->rear->next = n;
        queue->rear = n;
    }

    ql_check_invariants(queue); // 불변식 검사
    return 1; // 성공
}

/* 데이터 제거 및 반환: 성공 시 1, 실패 시 0 */
int ql_dequeue(QLP* queue, int* out) {
    if (!queue) {
        printf("큐가 존재하지 않습니다\n");
        return 0; // 실패
    }

    if (ql_is_empty(queue)) {
        printf("큐가 비어있습니다\n");
        return 0; // 실패
    }

    QLNode* front_node = queue->front;
    if (out) {
        *out = front_node->data;
    }

    queue->front = front_node->next;

    // 큐가 비어지면 rear도 NULL로 설정
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(front_node);
    front_node = NULL; // free 후 포인터를 NULL로 설정

    ql_check_invariants(queue); // 불변식 검사
    return 1; // 성공
}

/* ===== 큐 출력 ===== */
// front->rear 순서
void ql_print(const QLP* queue) {
    if (!queue) {
        printf("큐가 존재하지 않습니다\n");
        return;
    }

    if (ql_is_empty(queue)) {
        printf("큐가 비어있습니다\n");
        return;
    }

    printf("큐 [front -> rear]: [ ");
    QLNode* cur = queue->front;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" ]\n");
    printf("크기: %d\n", ql_size(queue));
}

/* ===== 메모리 해제 ===== */
void ql_free(QLP* queue) {
    if (!queue) {
        return;
    }

    QLNode* cur = queue->front;
    while (cur) {
        QLNode* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL; // free 후 포인터를 NULL로 설정
    }

    queue->front = NULL;
    queue->rear = NULL;
}
