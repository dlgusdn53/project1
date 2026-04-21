#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define INIT_SIZE 3  // 초기 배열 크기 (과제 9 유지)

typedef struct {
    int *data;   // 동적 배열 포인터 (과제 9 유지)
    int size;    // 현재 배열 용량
    int count;   // 현재 저장된 데이터 수
} ArrayList;

/* ---------- 핵심 연산 ---------- */
void init(ArrayList *list);
void insert(ArrayList *list, int pos, int value); // 1. 삽입
void delete(ArrayList *list, int pos);            // 2. 삭제
void replace(ArrayList *list, int pos, int value);// 3. 변경
void printList(ArrayList *list);                  // 4. 출력
void clear(ArrayList *list);                      // 5. 전체 삭제

/* ---------- 내부 유틸 ---------- */
void growIfNeeded(ArrayList *list);        // 용량 초과 시 2배 확장
void appendRaw(ArrayList *list, int val);  // 양의 정수 검사 없이 내부 저장 (희소행렬 전용)

#endif
