# 과제(10) - 순차리스트

## 파일 구조

```
assignment10/
├── ArrayList.h       # 양의 정수 전용 순차리스트 헤더
├── ArrayList.c       # 순차리스트 구현 (insert/delete/replace/print/clear)
├── main.c            # 메뉴 기반 순차리스트 테스트 프로그램
├── SparseMatrix.h    # 희소행렬 헤더 (다단계 포인터 구조)
├── SparseMatrix.c    # 희소행렬 구현 및 전치행렬
└── sparseMain.c      # 희소행렬 테스트 프로그램
```

---

## 1) 순차 리스트 개선

### 과제 9에서 개선된 사항

| 항목 | 과제 9 | 과제 10 |
|------|--------|---------|
| 데이터 타입 | 모든 정수 | **양의 정수만** 허용 |
| 삽입 방식 | 맨 끝 추가만 (`add`) | **임의 위치 삽입** (`insert`) |
| 삭제 | 없음 | **위치 지정 삭제** (`delete`) |
| 변경 | 없음 | **위치 지정 변경** (`replace`) |
| 출력 | 값만 출력 | **위치(인덱스)와 값** 함께 출력 |
| 초기화 | 없음 | **전체 삭제** (`clear`) |
| 오류 처리 | 없음 | 잘못된 입력/위치 **오류 메시지** 출력 |
| 동적 확장 | realloc 2배 | 동일 유지 (과제 9 재활용) |

### 메뉴 기능

```
1. 삽입 (insert)  - 양의 정수와 위치를 입력받아 추가
2. 삭제 (delete)  - 위치를 입력받아 삭제
3. 변경 (replace) - 양의 정수와 위치를 입력받아 값 변경
4. 출력 (print)   - 위치와 값을 함께 출력
5. 초기화 (clear) - 모든 항목 삭제
0. 종료
```

### 빌드 및 실행

```bash
gcc -o main main.c ArrayList.c
./main
```

---

## 2) 순차리스트 희소행렬

### 자료구조 설계 (다단계 포인터)

```
SparseMatrix*           (1단계 포인터)
  ├── row
  ├── col
  └── ArrayList*        (2단계 포인터)
        ├── count
        ├── size
        └── int* data   (3단계 포인터)
              └── [r0, c0, v0, r1, c1, v1, ...]
```

- 비영 원소 1개를 `[행, 열, 값]` 3칸으로 ArrayList에 순차 저장
- `SparseMatrix` → `ArrayList*` → `int*` 의 **3단계 포인터** 구조

### 희소행렬 초기화

- 10×10 행렬에 **0이 아닌 원소 20개** 배치
- `toSparseMatrix()`로 ArrayList 기반 압축 표현으로 변환

### 전치행렬 알고리즘

- 열 번호를 0부터 순서대로 탐색
- 해당 열에 속하는 원소를 `(열, 행, 값)` 순서로 삽입
- 탐색(읽기) + 삽입(쓰기) 모두 데이터 이동으로 카운트

### 빌드 및 실행

```bash
gcc -o sparseMain sparseMain.c SparseMatrix.c ArrayList.c
./sparseMain
```
