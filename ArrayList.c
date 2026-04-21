#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

/* ── 초기화 (과제 9 유지 + 동적 할당) ── */
void init(ArrayList *list) {
    list->data  = (int *)malloc(INIT_SIZE * sizeof(int));
    if (!list->data) {
        fprintf(stderr, "[오류] 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    list->size  = INIT_SIZE;
    list->count = 0;
}

/* ── 용량 부족 시 2배 확장 (과제 9의 realloc 로직 유지) ── */
void growIfNeeded(ArrayList *list) {
    if (list->count == list->size) {
        list->size *= 2;
        list->data = (int *)realloc(list->data, list->size * sizeof(int));
        if (!list->data) {
            fprintf(stderr, "[오류] 메모리 재할당 실패\n");
            exit(EXIT_FAILURE);
        }
        printf("  [배열 확장] 용량 → %d\n", list->size);
    }
}

/* ── 1. 삽입 (pos: 0-based) ── */
void insert(ArrayList *list, int pos, int value) {
    /* 양의 정수 검사 */
    if (value <= 0) {
        printf("[오류] 양의 정수만 입력 가능합니다. (입력값: %d)\n", value);
        return;
    }
    /* 위치 검사: 0 ~ count 사이 허용 (count 위치 = 맨 끝 추가) */
    if (pos < 0 || pos > list->count) {
        printf("[오류] 유효하지 않은 위치입니다. (허용 범위: 0 ~ %d)\n", list->count);
        return;
    }

    growIfNeeded(list);

    /* pos 이후 원소를 한 칸씩 뒤로 이동 */
    for (int i = list->count; i > pos; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[pos] = value;
    list->count++;
}

/* ── 2. 삭제 (pos: 0-based) ── */
void delete(ArrayList *list, int pos) {
    if (list->count == 0) {
        printf("[오류] 리스트가 비어 있습니다.\n");
        return;
    }
    if (pos < 0 || pos >= list->count) {
        printf("[오류] 유효하지 않은 위치입니다. (허용 범위: 0 ~ %d)\n", list->count - 1);
        return;
    }

    /* pos 이후 원소를 한 칸씩 앞으로 이동 */
    for (int i = pos; i < list->count - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->count--;
}

/* ── 3. 변경 (pos: 0-based) ── */
void replace(ArrayList *list, int pos, int value) {
    if (value <= 0) {
        printf("[오류] 양의 정수만 입력 가능합니다. (입력값: %d)\n", value);
        return;
    }
    if (pos < 0 || pos >= list->count) {
        printf("[오류] 유효하지 않은 위치입니다. (허용 범위: 0 ~ %d)\n", list->count - 1);
        return;
    }
    list->data[pos] = value;
}

/* ── 4. 출력 (위치와 값 함께 표시) ── */
void printList(ArrayList *list) {
    if (list->count == 0) {
        printf("  (리스트가 비어 있습니다)\n");
        return;
    }
    printf("  위치(index) :  값\n");
    printf("  ---------------------\n");
    for (int i = 0; i < list->count; i++) {
        printf("       %4d    :  %d\n", i, list->data[i]);
    }
    printf("  (총 %d개)\n", list->count);
}

/* ── 5. 전체 삭제 (메모리는 유지, count만 0으로) ── */
void clear(ArrayList *list) {
    list->count = 0;
    printf("  리스트의 모든 항목이 삭제되었습니다.\n");
}

/* ── 내부 전용: 양의 정수 검사 없이 맨 끝에 추가 (희소행렬 row/col 0 저장용) ── */
void appendRaw(ArrayList *list, int val) {
    growIfNeeded(list);
    list->data[list->count++] = val;
}
