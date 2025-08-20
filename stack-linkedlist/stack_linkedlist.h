#ifndef STACK_LINKEDLIST_H // 중복 포함 방지 가드
#define STACK_LINKEDLIST_H

/* ===== 연결 리스트 기반 스택의 노드 ===== */
typedef struct SLNode {
    int data; // 정수를 저장할 변수
    struct SLNode* next; // 다음 노드를 가리킬 포인터
} SLNode;

/* ===== 스택 컨테이너: top 포인터 관리 ===== */
typedef struct SLP {
    SLNode* top; // 스택의 최상단 노드를 가리키는 포인터
} SLP;

/* ===== 스택 생성 ===== */
SLP sl_create(); // 빈 스택 생성 및 초기화

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 스택일 때 top==NULL인지 검사
// 연결 리스트의 무결성 검사 (NULL 체크)
void sl_check_invariants(const SLP* stack);

/* ===== 스택 상태 확인 ===== */
int sl_is_empty(const SLP* stack); // 비어 있으면 1, 아니면 0
int sl_size(const SLP* stack); // 현재 스택에 저장된 요소 개수 반환

/* ===== 스택 기본 연산 ===== */
int sl_push(SLP* stack, int value); // 데이터 삽입: 성공 시 1, 실패 시 0
int sl_pop(SLP* stack, int* out); // 데이터 제거 및 반환: 성공 시 1, 실패 시 0
int sl_peek(const SLP* stack, int* out); // 최상단 확인: 성공 시 1, 실패 시 0

/* ===== 스택 출력 ===== */
void sl_print(const SLP* stack); // 스택 내용 출력 (top -> bottom 순서)

/* ===== 메모리 해제: 모든 노드 해제 + top 초기화 ===== */
void sl_free(SLP* stack);

#endif
