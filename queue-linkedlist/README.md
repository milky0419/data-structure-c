[README.md](https://github.com/user-attachments/files/21900621/README.ql.md)
# 연결 리스트 기반 큐 (Queue-Linkedlist)

## 개념

### 1. 연결 리스트 기반 큐의 구조

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;  // 데이터가 나가는 쪽
    Node* rear;   // 데이터가 들어오는 쪽
} Queue;
```

### 2. 연결 리스트 기반 큐의 특징

- 크기 제한이 없음 (메모리가 허락하는 한 무한 확장 가능)

- `enqueue` → rear 뒤에 새 노드 붙이고 rear를 새 노드로 변경

- `dequeue` → front 노드 제거 후 front를 다음 노드로 변경

## 구현된 기능

- 빈 큐 생성 및 초기화: `ql_create()`

- 데이터 삽입: `ql_enqueue()`

- 데이터 제거 및 반환: `ql_dequeue()`

- 비어 있는지 확인: `ql_is_empty()`

- 현재 저장된 요소 개수 반환: `ql_size()`

- 큐 내용 출력 (front -> rear 순서): `ql_print()`

- 모든 노드 해제 및 front/rear 초기화: `ql_free()`

- 연결 리스트 무결성과 front/rear 연결 상태 검증 (자동 실행): `ql_check_invariants()`

## 테스트

### 1. 큐 생성 테스트

- 빈 큐 생성 확인
- 초기 상태에서 비어있음 확인
- 초기 크기 및 front/rear 포인터 상태 확인

### 2. enqueue 기본 테스트

- 10, 20, 30 순서로 enqueue 연산
- 각 enqueue 후 성공/실패 결과 확인
- enqueue 후 큐 상태 및 크기 출력

### 3. dequeue 기본 테스트

- 첫 번째 요소 제거 및 값 반환
- dequeue 전후 큐 상태 비교
- out 파라미터를 통한 값 반환 확인

### 4. FIFO 특성 테스트

- 40, 50 추가 enqueue
- 순서대로 dequeue하여 FIFO 동작 확인
- First In First Out 원칙 검증

### 5. 큐 상태 확인 테스트

- 현재 큐 크기 확인
- 비어있음 상태 확인
- 큐 내용 출력

### 6. 동적 확장 테스트

- 배열과 달리 크기 제한 없음을 확인
- 많은 요소 추가 (100부터 150까지 5씩 증가)
- 추가된 요소 개수 및 최종 크기 확인
- 전체 큐 내용 출력

### 7. 메모리 할당 확인 테스트

- 더 많은 요소 추가 시도 (1000부터 1020까지)
- 메모리 할당 성공/실패 확인
- 대량 데이터 처리 시 앞쪽 몇 개 요소만 출력
- 총 크기 확인

### 8. 부분 dequeue 후 enqueue 테스트

- 10개 요소 dequeue
- 새로운 요소 5개 추가 (200부터 204까지)
- 큐의 동적 사용 패턴 확인
- front 부분 요소들 확인

### 9. 모든 요소 dequeue 테스트

- 큐가 빌 때까지 모든 요소 제거
- dequeue된 요소 개수 및 순서 확인
- 처음 5개와 10개마다 진행 상황 출력
- 최종 빈 큐 상태 확인

### 10. 언더플로우 테스트

- 빈 큐에서 dequeue 시도
- 언더플로우 상황에서 실패 처리 확인

### 11. 단일 노드 테스트

- 하나의 요소만 enqueue
- 단일 노드에서 front==rear 상태 확인
- 단일 노드 dequeue 후 빈 큐 상태 확인

### 12. 연결 리스트 특성 테스트

- 배열 기반과 달리 이론적으로 크기 제한이 없음 확인
- 15개 요소 추가 (3의 배수들)
- 앞쪽 절반 제거 후 크기 변화 확인
- 뒤쪽에 새로운 요소 추가

### 13. 불변식 검사 테스트

- 현재 큐 상태에서 불변식 검사
- 모든 enqueue/dequeue 연산 후 `ql_check_invariants()` 자동 실행
- 빈 큐와 단일 노드 상태 일관성 확인
- 에러 메시지가 없으면 데이터 구조가 올바르게 유지됨을 확인

### 14. 메모리 해제 테스트

- `ql_free()` 함수로 모든 노드 메모리 해제
- 해제 후 빈 큐 상태 확인
- 해제 후 크기 확인

### 15. NULL 포인터 안전성 테스트

- NULL 큐에 대한 모든 연산 테스트
- `ql_enqueue(NULL, 10)`, `ql_dequeue(NULL, &value)` 테스트
- `ql_print(NULL)` 테스트
