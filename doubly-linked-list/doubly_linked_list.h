#ifndef DOUBLY_LINKED_LIST_H // 중복 포함 방지 가드
#define DOUBLY_LINKED_LIST_H

/* ===== 이중 연결 리스트의 노드 ===== */
typedef struct DLLNode {
    int data; // 정수를 저장할 변수
    struct DLLNode* prev; // 이전 노드를 가리킬 포인터
    struct DLLNode* next; // 다음 노드를 가리킬 포인터
} DLLNode;

/* ===== 리스트 컨테이너: head와 tail 포인터 관리 ===== */
typedef struct DLLP {
    DLLNode* head; // head pointer
    DLLNode* tail; // tail pointer
} DLLP;

/* ===== 리스트 생성 ===== */
DLLP dll_create();

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 리스트일 때 head==NULL && tail==NULL인지 검사
// 빈 리스트가 아닐 때 head->prev==NULL && tail->next==NULL인지 검사
// 양방향 연결이 올바른지 검사 (node->next->prev == node)
void dll_check_invariants(const DLLP* list);

/* ===== 리스트가 비어있는지 확인 ===== */
int dll_is_empty(const DLLP* list); // 비어있으면 1, 아니면 0

/* ===== 맨 앞/뒤 삽입 ===== */
int dll_push_front(DLLP* list, int value); // 맨 앞 삽입: 성공 시 1, 실패 시 0 반환
int dll_push_back(DLLP* list, int value); // 맨 뒤 삽입: 성공 시 1, 실패 시 0 반환

/* ===== 맨 앞/뒤 삭제 ===== */
int dll_pop_front(DLLP* list, int* out); // 맨 앞 삭제: 성공 시 1, 실패 시 0 반환
int dll_pop_back(DLLP* list, int* out); // 맨 뒤 삭제: 성공 시 1, 실패 시 0 반환

/* ===== 값 탐색 ===== */
DLLNode* dll_find(const DLLP* list, int target); // 없으면 NULL 반환

/* ===== 전체 출력: 앞→뒤, 뒤→앞 양방향 출력 ===== */
void dll_print_forward(const DLLP* list); // 앞에서 뒤로 출력
void dll_print_backward(const DLLP* list); // 뒤에서 앞으로 출력

/* ===== 메모리 해제: 모든 노드 해제 + 헤드/테일 초기화 ===== */
void dll_free(DLLP* list);

#endif
