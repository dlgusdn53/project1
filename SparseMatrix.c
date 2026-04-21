#include <stdio.h>
#include <stdlib.h>
#include "SparseMatrix.h"

/*
 * 저장 형식 (ArrayList 내부 data 배열):
 *   인덱스  0   1   2  |  3   4   5  |  6   7   8  | ...
 *          row col val | row col val | row col val  | ...
 *   비영 원소 1개 = 3칸
 *
 * 다단계 포인터:
 *   sm (SparseMatrix*)  →  sm->list (ArrayList*)  →  sm->list->data (int*)
 */

#define ENTRY_SIZE 3   /* 원소 1개당 저장 칸 수: [row, col, val] */

/* ── SparseMatrix 동적 생성 ── */
SparseMatrix *createSparseMatrix(int row, int col) {
    /* 1단계 포인터: SparseMatrix 동적 할당 */
    SparseMatrix *sm = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    if (!sm) { fprintf(stderr, "[오류] SparseMatrix 할당 실패\n"); exit(1); }

    sm->row = row;
    sm->col = col;

    /* 2단계 포인터: ArrayList 동적 할당 */
    sm->list = (ArrayList *)malloc(sizeof(ArrayList));
    if (!sm->list) { fprintf(stderr, "[오류] ArrayList 할당 실패\n"); exit(1); }

    /* 3단계 포인터: ArrayList 내부 int* data 초기화 */
    init(sm->list);

    return sm;
}

/* ── 메모리 해제 ── */
void destroySparseMatrix(SparseMatrix *sm) {
    if (sm) {
        if (sm->list) {
            free(sm->list->data);  /* 3단계 */
            free(sm->list);        /* 2단계 */
        }
        free(sm);                  /* 1단계 */
    }
}

/* ── 10×10 행렬 → 희소행렬 변환 ── */
SparseMatrix *toSparseMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int row, int col) {
    SparseMatrix *sm = createSparseMatrix(row, col);

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (matrix[r][c] != 0) {
                /* [행, 열, 값] 순서로 ArrayList에 순차 저장 (row/col은 0 포함 가능) */
                appendRaw(sm->list, r);
                appendRaw(sm->list, c);
                appendRaw(sm->list, matrix[r][c]);
            }
        }
    }
    return sm;
}

/* ── 희소행렬 출력 (2차원 형태로 복원하여 출력) ── */
void printSparseMatrix(SparseMatrix *sm) {
    /* 빈 행렬 준비 */
    int restored[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int nonzero = sm->list->count / ENTRY_SIZE;

    /* 3단계 포인터(data)에서 값 꺼내 복원 */
    for (int i = 0; i < nonzero; i++) {
        int r   = sm->list->data[i * ENTRY_SIZE];
        int c   = sm->list->data[i * ENTRY_SIZE + 1];
        int val = sm->list->data[i * ENTRY_SIZE + 2];
        restored[r][c] = val;
    }

    printf("  (%d x %d 행렬, 비영 원소 %d개)\n", sm->row, sm->col, nonzero);
    for (int r = 0; r < sm->row; r++) {
        printf("  ");
        for (int c = 0; c < sm->col; c++) {
            printf("%4d", restored[r][c]);
        }
        printf("\n");
    }

    /* ArrayList 저장 내용도 표시 */
    printf("\n  [ArrayList 저장 내용: (행, 열, 값)]\n  ");
    for (int i = 0; i < nonzero; i++) {
        int r   = sm->list->data[i * ENTRY_SIZE];
        int c   = sm->list->data[i * ENTRY_SIZE + 1];
        int val = sm->list->data[i * ENTRY_SIZE + 2];
        printf("(%d,%d,%d) ", r, c, val);
    }
    printf("\n");
}

/* ── 원래 10×10 행렬 출력 ── */
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int r = 0; r < MATRIX_SIZE; r++) {
        printf("  ");
        for (int c = 0; c < MATRIX_SIZE; c++) {
            printf("%4d", matrix[r][c]);
        }
        printf("\n");
    }
}

/* ── 전치행렬 생성 ── */
/*
 * 전치행렬: 원소 (r, c, v)  →  (c, r, v)
 * 방법: 원래 희소행렬의 col 값이 작은 것부터 차례로 탐색하여
 *       열 우선 순서로 새 희소행렬에 삽입한다.
 *       → 데이터 이동 횟수를 정확히 카운트하기 위해 선형 탐색 사용
 */
SparseMatrix *transpose(SparseMatrix *sm, int *moveCount) {
    *moveCount = 0;

    /* 전치 결과: 행↔열 교환 */
    SparseMatrix *result = createSparseMatrix(sm->col, sm->row);

    int nonzero = sm->list->count / ENTRY_SIZE;

    /*
     * 열 번호(c)를 0부터 순서대로 탐색하여
     * 해당 열에 속하는 원소를 전치 행렬에 (c, r, v) 순으로 삽입
     */
    for (int targetCol = 0; targetCol < sm->col; targetCol++) {
        for (int i = 0; i < nonzero; i++) {
            int r   = sm->list->data[i * ENTRY_SIZE];
            int c   = sm->list->data[i * ENTRY_SIZE + 1];
            int val = sm->list->data[i * ENTRY_SIZE + 2];

            (*moveCount)++;  /* 탐색(읽기)도 데이터 접근으로 카운트 */

            if (c == targetCol) {
                /* 전치: 행↔열 교환하여 삽입 */
                appendRaw(result->list, c);    /* 새 행 = 원래 열 */
                appendRaw(result->list, r);    /* 새 열 = 원래 행 */
                appendRaw(result->list, val);
                *moveCount += 3;  /* 삽입(쓰기) 3칸 */
            }
        }
    }
    return result;
}
