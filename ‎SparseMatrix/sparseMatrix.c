#include <stdio.h>
#include <stdlib.h>

#include "sparseMatrix.h"

sparseMatrix* createSparseMatrix(int row, int col) {
	return createArrayList(row * col);
}

int addElementSparseMatrix(sparseMatrix* sm, int row, int col, int value) {
	int size;
	size = sizeArrayList(sm);

	insertArrayList(sm, size,
		(elementArrayList) {row, col, value});
}

int printSparseMatrix(sparseMatrix* sm) {
	printf("Èñ¼ÒÇà·ÄÀÔ´Ï´Ù\n");

	printArrayList(sm);
}

sparseMatrix* addSparseMatrix(sparseMatrix* sm1, sparseMatrix* sm2) {
    // 넉넉한 크기로 생성하거나 필요에 따라 동적 할당
    sparseMatrix* smResult = createArrayList(sizeArrayList(sm1) + sizeArrayList(sm2));
    
    // 1. sm1의 모든 원소를 결과에 넣으면서 sm2와 겹치는 게 있으면 더함
    for (int i = 0; i < sizeArrayList(sm1); i++) {
        elementArrayList e1 = getItemArrayList(sm1, i);
        int found = 0;
        for (int j = 0; j < sizeArrayList(sm2); j++) {
            elementArrayList e2 = getItemArrayList(sm2, j);
            if (e1.row == e2.row && e1.col == e2.col) {
                int sum = e1.value + e2.value;
                if (sum != 0) { // 합이 0이 아닐 때만 삽입
                    addElementSparseMatrix(smResult, e1.row, e1.col, sum);
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            addElementSparseMatrix(smResult, e1.row, e1.col, e1.value);
        }
    }

    // 2. sm2에만 있는 원소(sm1에는 없는 것)를 추가로 삽입
    for (int j = 0; j < sizeArrayList(sm2); j++) {
        elementArrayList e2 = getItemArrayList(sm2, j);
        int foundInSM1 = 0;
        for (int i = 0; i < sizeArrayList(sm1); i++) {
            elementArrayList e1 = getItemArrayList(sm1, i);
            if (e1.row == e2.row && e1.col == e2.col) {
                foundInSM1 = 1;
                break;
            }
        }
        if (!foundInSM1) {
            addElementSparseMatrix(smResult, e2.row, e2.col, e2.value);
        }
    }
    return smResult;
}
