#ifndef LINKED_LIST_H // 중복 포함 방지 가드
#define LINKED_LIST_H

/* ===== 단일 연결 리스트의 노드 ===== */
typedef struct LLNode {
    int data; // 값을 저장할 변수
    struct LLNode* next; // 다음 노드를 가리킬 포인터
} LLNode;

/* ===== 리스트 컨테이너: head와 tail 포인터 관리 ===== */
typedef struct LLP {
    LLNode* head; // head pointer
    LLNode* tail; // tail pointer
} LLP;

/* ===== 리스트 생성 ===== */
LLP ll_create();

/* ===== 불변식 검사(추가 기능) ===== */
// 빈 리스트일 때 head==NULL && tail==NULL인지 검사
// 빈 리스트가 아닐 때 tail이 마지막 노드이고, tail->next==NULL인지 검사
static void ll_check_invariants(const LLP* list);

/* ===== 맨 앞/뒤 삽입 ===== */
void ll_push_front(LLP* list, int value); // 맨 앞 삽입
void ll_push_back(LLP* list, int value); // 맨 뒤 삽입

/* ===== 맨 앞/뒤 삭제 ===== */
int ll_pop_front(LLP* list, int* out); // 맨 앞 삭제: 성공 시 1, 실패 시 0
int ll_pop_back(LLP* list, int* out); // 맨 뒤 삭제: 성공 시 1, 실패 시 0

/* ===== 값 탐색 ===== */
LLNode* ll_find(const LLP* list, int target); // 없으면 NULL 반환

/* ===== 전체 출력: [a -> b -> c]\n 형식으로 출력 ===== */
void ll_print(const LLP* list);

/* ===== 메모리 해제: 모든 노드 해제 + 헤드/테일 초기화 ===== */
void ll_free(LLP* list);

/* ===== 리스트가 비어있는지 확인: main.c에서 사용 ===== */
int ll_is_empty(const LLP* list); // 비어있으면 1, 아니면 0

#endif