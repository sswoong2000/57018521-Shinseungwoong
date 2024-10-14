#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 최대 힙 구조체 정의
typedef struct {
    int data[MAX_SIZE]; // 힙의 데이터를 저장할 배열
    int size;          // 현재 힙의 크기
} TreeNode;

// 최대 힙 초기화 함수
void InitMaxHeap(TreeNode* root) {
    root->size = 0; // 힙의 크기를 0으로 설정
}

// 힙의 내용을 출력하는 함수
void PrintHeap(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]); // 힙의 각 요소 출력
    }
    printf("\n");
}

// 힙에 값을 삽입하는 함수
int InsertMaxHeap(TreeNode* root, int value, int showSteps) {
    // 힙이 가득 찼는지 확인
    if (root->size >= MAX_SIZE) {
        printf("힙이 가득 찼습니다!\n");
        return 0;
    }

    int index = root->size; // 삽입할 위치 설정
    root->data[index] = value; // 값을 힙에 추가
    root->size++; // 힙 크기 증가

    int moves = 0; // 이동 횟수 초기화
    if (showSteps) {
        printf("노드 추가 전 힙 상태: ");
        PrintHeap(root); // 추가 전 상태 출력
    }

    // 부모 노드와 비교하여 힙 속성 유지
    while (index > 0) {
        int parent = (index - 1) / 2; // 부모 노드 인덱스
        if (root->data[parent] < root->data[index]) {
            // 부모가 자식보다 작으면 swap
            int temp = root->data[parent];
            root->data[parent] = root->data[index];
            root->data[index] = temp;
            index = parent; // 인덱스를 부모로 변경
            moves++; // 이동 횟수 증가

            if (showSteps) {
                printf("노드 이동 후 힙 상태: ");
                PrintHeap(root); // 이동 후 상태 출력
            }
        }
        else {
            break; // 힙 속성 유지 완료
        }
    }
    if (showSteps) {
        printf("최종 힙 상태: ");
        PrintHeap(root); // 최종 상태 출력
    }

    return moves; // 이동 횟수 반환
}

// 힙에서 최대값을 삭제하는 함수
int DeleteMaxHeap(TreeNode* root) {
    // 힙이 비어 있는지 확인
    if (root->size == 0) {
        printf("힙이 비어있습니다!\n");
        return 0;
    }

    root->data[0] = root->data[root->size - 1]; // 마지막 요소를 루트로 이동
    root->size--; // 힙 크기 감소

    int index = 0; // 루트 인덱스
    int moves = 0; // 이동 횟수 초기화
    printf("노드 삭제 전 힙 상태: ");
    PrintHeap(root); // 삭제 전 상태 출력

    // 자식과 비교하여 힙 속성 유지
    while (index * 2 + 1 < root->size) {
        int leftChild = index * 2 + 1; // 왼쪽 자식 인덱스
        int rightChild = index * 2 + 2; // 오른쪽 자식 인덱스
        int largerChild = leftChild; // 비교할 자식 노드 초기화

        // 오른쪽 자식이 더 크면 largerChild 변경
        if (rightChild < root->size && root->data[rightChild] > root->data[leftChild]) {
            largerChild = rightChild;
        }

        // 부모 노드가 자식보다 작으면 swap
        if (root->data[index] < root->data[largerChild]) {
            int temp = root->data[index];
            root->data[index] = root->data[largerChild];
            root->data[largerChild] = temp;

            index = largerChild; // 인덱스를 자식으로 변경
            moves++; // 이동 횟수 증가

            printf("노드 이동 후 힙 상태: ");
            PrintHeap(root); // 이동 후 상태 출력
        }
        else {
            break; // 힙 속성 유지 완료
        }
    }

    printf("최종 힙 상태: ");
    PrintHeap(root); // 최종 상태 출력

    return moves; // 이동 횟수 반환
}

// 힙을 레벨 순서로 출력하는 함수
void PrintHeapLevelOrder(TreeNode* root) {
    if (root->size == 0) {
        printf("힙이 비어 있습니다.\n");
        return;
    }

    int level = 0; // 현재 레벨
    int count = 1; // 현재 레벨의 노드 수
    int index = 0; // 현재 인덱스

    printf("트리 레벨별 출력:\n");
    while (index < root->size) {
        printf("[레벨 %d] ", level + 1); // 레벨 출력

        // 현재 레벨의 노드 출력
        for (int i = 0; i < count && index < root->size; i++) {
            printf("%d ", root->data[index]);
            index++;
        }
        printf("\n");

        level++; // 다음 레벨로 이동
        count *= 2; // 다음 레벨의 노드 수는 두 배
    }
}

// 사용자 인터페이스를 위한 함수
void RunUserInterface(TreeNode* root) {
    char choice; // 사용자 선택
    int value, moves; // 입력 값과 이동 횟수

    while (1) {
        printf("\n-------------------------------------\n");
        printf(" i : 노드 추가\n");
        printf(" d : 노드 삭제\n");
        printf(" p : 레벨별 출력\n");
        printf(" c : 종료\n");
        printf("-------------------------------------\n");

        printf("메뉴 입력: ");
        scanf(" %c", &choice); // 사용자 입력

        switch (choice) {
        case 'i':
            printf("추가할 값 입력: ");
            scanf("%d", &value); // 추가할 값 입력
            moves = InsertMaxHeap(root, value, 1); // 힙에 값 추가
            printf("노드가 추가되었습니다. 노드 이동 횟수: %d\n", moves);
            break;

        case 'd':
            moves = DeleteMaxHeap(root); // 최대값 삭제
            printf("최대 히프에서 루트 노드가 삭제되었습니다. 노드 이동 횟수: %d\n", moves);
            break;

        case 'p':
            PrintHeapLevelOrder(root); // 레벨 순서로 출력
            break;

        case 'c':
            printf("프로그램을 종료합니다.\n");
            return; // 프로그램 종료

        default:
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
        }
    }
}

int main() {
    TreeNode root;  // 최대 힙 구조체
    InitMaxHeap(&root); // 힙 초기화

    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 13 }; // 초기 데이터
    int size = sizeof(inputData) / sizeof(inputData[0]); // 데이터 크기 계산

    // 초기 데이터로 힙 생성
    for (int i = 0; i < size; i++) {
        InsertMaxHeap(&root, inputData[i], 0); // 힙에 데이터 추가
    }

    RunUserInterface(&root); // 사용자 인터페이스 실행

    return 0;
}
