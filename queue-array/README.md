[README.md](https://github.com/user-attachments/files/21773614/README.qa.md)
# 배열 기반 큐 (Queue-Array)

## 개념

### 1. 큐(queue)란?

- 선입선출(FIFO, First In First Out) 구조

### 2. 주요 연산

- **enqueue**: 데이터 삽입 (뒤쪽에 넣음)

- **dequeue**: 데이터 제거 (앞쪽에서 뺌)

- **is_empty**: 비었는지 확인

- **is_full**: (배열 기반 큐에서만) 가득 찼는지 확인

- **size**: 현재 저장된 데이터 개수 확인

### 3. 배열 기반 큐의 구조

```c
typedef struct {
    int* data;      // 데이터 저장 배열
    int front;      // 데이터가 나오는 위치
    int rear;       // 데이터가 들어가는 위치
    int capacity;   // 배열 크기
    int size;       // 저장된 데이터 개수
} Queue;
```

### 4. 배열 기반 큐의 특징

- **원형 구조**를 사용하면, 배열을 다 쓰고 나서도 비어 있는 칸을 재활용 가능

- `enqueue` → rear 위치에 값 넣고 `(rear + 1) % capacity`

- `dequeue` → front 위치 값 꺼내고 `(front + 1) % capacity`

## 구현된 기능

- 새로운 큐 생성 및 초기화: `qa_create()`
- 데이터 삽입: `qa_enqueue()`
- 데이터 제거 및 반환: `qa_dequeue()`
- 비어 있는지 확인: `qa_is_empty()`
- 가득 찼는지 확인: `qa_is_full()`
- 현재 저장된 요소 개수 반환: `qa_size()`
- 큐 내용 출력 (front -> rear 순서): `qa_print()`
- 큐 구조체 해제: `qa_free()`
- front, rear, size 유효성과 원형 큐 상태 검증 (자동 실행): `qa_check_invariants()`

## 테스트

### 1. 큐 생성 테스트

- 빈 큐 생성 확인
- 초기 상태에서 비어있음/가득참 확인
- 초기 front, rear, size 상태 확인

### 2. enqueue 기본 테스트

- 10, 20, 30 순서로 enqueue 연산
- 각 enqueue 후 성공/실패 결과 확인
- enqueue 후 큐 상태 및 인덱스 출력

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
- 비어있음/가득참 상태 확인
- front, rear 인덱스 정보 출력

### 6. 큐 가득 찰 때까지 enqueue 테스트

- 최대 크기까지 데이터 채우기
- 각 enqueue 성공/실패 결과 확인
- 최종 크기 및 가득참 상태 확인

### 7. 오버플로우 테스트

- 가득 찬 큐에 추가 enqueue 시도
- 오버플로우 상황에서 실패 처리 확인
- 큐 크기 변화 없음 확인

### 8. 원형 큐 특성 테스트

- 일부 dequeue 후 다시 enqueue
- rear 인덱스가 배열 처음 부분으로 순환하는지 확인
- 원형 구조의 공간 효율성 검증

### 9. 모든 요소 dequeue 테스트

- 큐가 빌 때까지 모든 요소 제거
- dequeue된 요소 개수 및 순서 확인
- 최종 빈 큐 상태 확인

### 10. 언더플로우 테스트

- 빈 큐에서 dequeue 시도
- 언더플로우 상황에서 실패 처리 확인

### 11. 큐 재사용 테스트

- 빈 큐 상태에서 다시 데이터 추가
- 부분 dequeue 후 추가 enqueue
- 큐의 재사용 가능성 확인
- 원형 구조의 지속적 사용 검증

### 12. 불변식 검사 테스트

- 현재 큐 상태에서 불변식 검사
- 모든 enqueue/dequeue 연산 후 `qa_check_invariants()` 자동 실행
- front, rear, size 인덱스 유효성 검증
- 원형 큐 상태 일관성 확인
- 에러 메시지가 없으면 데이터 구조가 올바르게 유지됨을 확인

### 13. 메모리 해제 테스트

- `qa_free()` 함수로 큐 구조체 메모리 해제
- 해제 후 댕글링 포인터 방지 확인

### 14. NULL 포인터 안전성 테스트

- NULL 큐에 대한 모든 연산 테스트
- `qa_enqueue(NULL, 10)`, `qa_dequeue(NULL, &value)` 안전 처리
- `qa_print(NULL)` 적절한 메시지 출력


