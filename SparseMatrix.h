#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "ArrayList.h"

#define MATRIX_SIZE 10   // 10×10 행렬
#define NONZERO_COUNT 20 // 0이 아닌 원소 개수

/*
 * SparseMatrix 구조체
 *   - row, col : 원래 행렬의 크기
 *   - list     : ArrayList* (포인터) → 동적 할당된 ArrayList 사용
 *
 * ArrayList 한 항목(Element)은 하나의 비영 원소를 나타낸다.
 * 저장 순서: [행, 열, 값] 3개씩 묶어서 순차 저장
 *   예) data = { r0, c0, v0,  r1, c1, v1, ... }
 *
 * 다단계 포인터 구조:
 *   SparseMatrix  →  ArrayList*  →  int* (data)
 *       (1단계)         (2단계)       (3단계)
 */
typedef struct {
    int row;          // 원래 행렬 행 크기
    int col;          // 원래 행렬 열 크기
    ArrayList *list;  // 비영 원소 저장용 ArrayList (포인터)
} SparseMatrix;

/* ---------- SparseMatrix 연산 ---------- */
SparseMatrix *createSparseMatrix(int row, int col);     // 동적 생성
void destroySparseMatrix(SparseMatrix *sm);             // 메모리 해제

/* 원래 10×10 행렬을 희소행렬(SparseMatrix)로 변환 */
SparseMatrix *toSparseMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int row, int col);

/* 희소행렬을 10×10 2차원 배열로 복원 후 출력 */
void printSparseMatrix(SparseMatrix *sm);

/* 원래 행렬 출력 */
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]);

/* 전치행렬 생성 (데이터 이동 횟수 반환) */
SparseMatrix *transpose(SparseMatrix *sm, int *moveCount);

#endif
