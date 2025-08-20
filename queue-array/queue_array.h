#ifndef QUEUE_ARRAY_H // 중복 포함 방지 가드
#define QUEUE_ARRAY_H

#define QUEUE_MAX_SIZE 10 // 큐 최대 크기 정의

/* ===== 배열 기반 원형 큐 구조체 ===== */
typedef struct QueueArray {
    int data[QUEUE_MAX_SIZE]; // 데이터를 저장할 배열
    int front; // 큐의 front 위치를 나타내는 인덱스
    int rear; // 큐의 rear 위치를 나타내는 인덱스
    int size; // 현재 큐에 저장된 요소 개수
    int capacity; // 큐의 최대 용량
} QueueArray;

/* ===== 큐 포인터 타입 정의 ===== */
typedef QueueArray* QAP; // Queue Array Pointer

/* ===== 큐 생성 ===== */
QAP qa_create(); // 새로운 큐 생성 및 초기화

/* ===== 불변식 검사(추가 기능) ===== */
// front, rear, size가 유효한 범위에 있는지 검사
// 원형 큐의 상태 일관성 검사
static void qa_check_invariants(const QAP queue);

/* ===== 큐 상태 확인 ===== */
int qa_is_empty(const QAP queue); // 비어 있으면 1, 아니면 0
int qa_is_full(const QAP queue); // 가득 차면 1, 아니면 0
int qa_size(const QAP queue); // 현재 큐에 저장된 요소 개수 반환

/* ===== 큐 기본 연산 ===== */
int qa_enqueue(QAP queue, int value); // 데이터 삽입: 성공 시 1, 실패 시 0
int qa_dequeue(QAP queue, int* out); // 데이터 제거 및 반환: 성공 시 1, 실패 시 0

/* ===== 큐 출력 ===== */
void qa_print(const QAP queue); // 큐 내용 출력 (front -> rear 순서)

/* ===== 메모리 해제: 큐 구조체 해제 ===== */
void qa_free(QAP queue);

#endif
