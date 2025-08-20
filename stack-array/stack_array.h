#ifndef STACK_ARRAY_H // 중복 포함 방지 가드
#define STACK_ARRAY_H

#define STACK_MAX_SIZE 10 // 테스트 편의성을 위한 스택 최대 크기 정의

/* ===== 배열 기반 스택 구조체 ===== */
typedef struct StackArray {
    int data[STACK_MAX_SIZE]; // 데이터를 저장할 배열
    int top; // 스택의 top 위치를 나타내는 인덱스 (-1이면 빈 스택)
    int capacity; // 스택의 최대 용량
} StackArray;

/* ===== 스택 포인터 타입 정의 ===== */
typedef StackArray* SAP; // Stack Array Pointer

/* ===== 스택 생성 ===== */
SAP sa_create(); // 새로운 스택 생성 및 초기화

/* ===== 불변식 검사(추가 기능) ===== */
// top이 유효한 범위에 있는지 검사 (-1 <= top < capacity)
// 스택이 비어있을 때와 가득 찰 때의 상태 검사
static void sa_check_invariants(const SAP stack);

/* ===== 스택 상태 확인 ===== */
int sa_is_empty(const SAP stack); // 비어 있으면 1, 아니면 0
int sa_is_full(const SAP stack); // 가득 차면 1, 아니면 0
int sa_size(const SAP stack); // 현재 스택에 저장된 요소 개수 반환

/* ===== 스택 기본 연산 ===== */
int sa_push(SAP stack, int value); // 데이터 삽입: 성공 시 1, 실패 시 0
int sa_pop(SAP stack, int* out); // 데이터 제거 및 반환: 성공 시 1, 실패 시 0
int sa_peek(SAP stack, int* out); // 최상단 확인: 성공 시 1, 실패 시 0

/* ===== 스택 출력 ===== */
void sa_print(const SAP stack); // 스택 내용 출력 (bottom -> top 순서)

/* ===== 메모리 해제: 스택 구조체 해제 ===== */
void sa_free(SAP stack);

#endif
