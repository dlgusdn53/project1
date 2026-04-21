#include <stdio.h>
#include <stdlib.h>
#include "SparseMatrix.h"

int main(void) {
    /*
     * 10×10 희소행렬 초기화
     * 0이 아닌 원소 20개를 직접 지정
     */
    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {0};

    /* 0이 아닌 원소 20개 배치 */
    int nonzeroData[NONZERO_COUNT][3] = {
        {0, 1,  3}, {0, 5,  7},
        {1, 2,  1}, {1, 8,  4},
        {2, 0,  9}, {2, 4,  2},
        {3, 3,  5}, {3, 7,  6},
        {4, 1,  8}, {4, 6,  3},
        {5, 0,  2}, {5, 9,  1},
        {6, 2,  7}, {6, 5,  4},
        {7, 4, 10}, {7, 8,  5},
        {8, 1,  6}, {8, 7,  9},
        {9, 3,  3}, {9, 6,  2}
    };

    for (int i = 0; i < NONZERO_COUNT; i++) {
        matrix[nonzeroData[i][0]][nonzeroData[i][1]] = nonzeroData[i][2];
    }

    /* ── 원본 행렬 출력 ── */
    printf("=== 원본 10x10 희소행렬 ===\n");
    printMatrix(matrix);

    /* ── 희소행렬 변환 및 출력 ── */
    printf("\n=== 희소행렬 (ArrayList로 압축 저장) ===\n");
    SparseMatrix *sm = toSparseMatrix(matrix, MATRIX_SIZE, MATRIX_SIZE);
    printSparseMatrix(sm);

    /* ── 전치행렬 생성 ── */
    int moveCount = 0;
    printf("\n=== 전치행렬 생성 중... ===\n");
    SparseMatrix *transposed = transpose(sm, &moveCount);

    printf("\n=== 전치행렬 결과 ===\n");
    printSparseMatrix(transposed);

    printf("\n>>> 데이터 이동 횟수: %d회\n", moveCount);

    /* ── 메모리 해제 ── */
    destroySparseMatrix(sm);
    destroySparseMatrix(transposed);

    return 0;
}
