#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* 단일 연결 리스트 노드 */
typedef struct LLNode {
	int data;
	struct LLNode* next;
} LLNode;

/* === 리스트 생성 === */
// 빈 리스트의 시작 주소(head) 반환
LLNode* ll_create();

/* === 삽입 === */
/* 새로운 노드 생성 */
static LLNode* ll_new_node(int value);

/* 마지막 노드의 next가 NULL인지 검사 */
static void ll_check_invariants(const LLNode* head);

/* 맨 앞 삽입 */
// head가 바뀔 수 있으므로, 이중 포인터 사용
void ll_push_front(LLNode** head, int value);

/* 맨 뒤 삽입 */
void ll_push_back(LLNode** head, int value);

/* === 삭제 === */
/* 맨 앞 삭제 */
// 성공 시 *out에 데이터 저장 & 1 반환 / 실패(빈 리스트) 시 0 반환
int ll_pop_front(LLNode** head, int* out);

/* 맨 뒤 삭제*/
// 성공 시 *out에 데이터 저장 & 1 반환 / 실패(빈 리스트) 시 0 반환
int ll_pop_back(LLNode** head, int* out);

/* === 값 탐색 === */
// 첫 매칭 노드와 포인터 반환, 없으면 NULL
LLNode* ll_find(LLNode* head, int target);

/* === 전체 출력 === */
// [a -> b -> c] 형식으로 출력
void ll_print(const LLNode* head);

/* === 리스트 메모리 해제 === */
void ll_free(LLNode* head);

#endif