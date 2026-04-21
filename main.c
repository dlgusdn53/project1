#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

void printMenu(void) {
    printf("\n========== 양의 정수 순차 리스트 ==========\n");
    printf("  1. 삽입 (insert)  - 값과 위치 입력\n");
    printf("  2. 삭제 (delete)  - 위치 입력\n");
    printf("  3. 변경 (replace) - 값과 위치 입력\n");
    printf("  4. 출력 (print)   - 전체 리스트 출력\n");
    printf("  5. 초기화 (clear) - 모든 항목 삭제\n");
    printf("  0. 종료\n");
    printf("==========================================\n");
    printf("선택: ");
}

int main(void) {
    ArrayList list;
    init(&list);

    int choice, pos, value;

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) { /* 잘못된 입력 방어 */
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: /* insert */
                printf("  삽입할 양의 정수: ");
                scanf("%d", &value);
                printf("  삽입할 위치 (0 ~ %d): ", list.count);
                scanf("%d", &pos);
                insert(&list, pos, value);
                break;

            case 2: /* delete */
                if (list.count == 0) {
                    printf("[오류] 리스트가 비어 있습니다.\n");
                    break;
                }
                printf("  삭제할 위치 (0 ~ %d): ", list.count - 1);
                scanf("%d", &pos);
                delete(&list, pos);
                break;

            case 3: /* replace */
                if (list.count == 0) {
                    printf("[오류] 리스트가 비어 있습니다.\n");
                    break;
                }
                printf("  변경할 위치 (0 ~ %d): ", list.count - 1);
                scanf("%d", &pos);
                printf("  새로운 양의 정수: ");
                scanf("%d", &value);
                replace(&list, pos, value);
                break;

            case 4: /* print */
                printList(&list);
                break;

            case 5: /* clear */
                clear(&list);
                break;

            case 0:
                printf("프로그램을 종료합니다.\n");
                free(list.data);
                return 0;

            default:
                printf("[오류] 0~5 사이의 숫자를 입력하세요.\n");
        }
    }
}
