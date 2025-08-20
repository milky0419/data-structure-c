#ifndef QUEUE_LINKEDLIST_H // 중복 포함 방지 가드
#define QUEUE_LINKEDLIST_H

/* ===== 연결 리스트 기반 큐의 노드 ===== */
typedef struct QLNode {
    int data; // 정수를 저장할 변수
    struct QLNode* next; // 다음 노드를 가리킬 포인터
} QLNode;

/* ===== 큐 컨테이너: front와 rear 포인터 관리 ===== */
typedef struct QLP {
    QLNode* front; // 큐의 앞쪽 노드를 가리키는 포인터 (dequeue 위치)
    QLNode* rear; // 큐의 뒤쪽 노드를 가리키는 포인터 (enqueue 위치)
} QLP;

/* ===== 큐 생성 ===== */
QLP ql_create(); // 빈 큐 생성 및 초기화

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 큐일 때 front==NULL && rear==NULL인지 검사
// 빈 큐가 아닐 때 front와 rear가 올바르게 연결되어 있는지 검사
// 단일 노드일 때 front==rear인지 검사
static void ql_check_invariants(const QLP* queue);

/* ===== 큐 상태 확인 ===== */
int ql_is_empty(const QLP* queue); // 비어 있으면 1, 아니면 0
int ql_size(const QLP* queue); // 현재 큐에 저장된 요소 개수 반환

/* ===== 큐 기본 연산 ===== */
int ql_enqueue(QLP* queue, int value); // 데이터 삽입: 성공 시 1, 실패 시 0
int ql_dequeue(QLP* queue, int* out); // 데이터 제거 및 반환: 성공 시 1, 실패 시 0

/* ===== 큐 출력 ===== */
void ql_print(const QLP* queue); // 큐 내용 출력 (front -> rear 순서)

/* ===== 메모리 해제: 모든 노드 해제 + front/rear 초기화 ===== */
void ql_free(QLP* queue);

#endif
