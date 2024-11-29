#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 전역 변수
int comparisonCount = 0;  // 비교 횟수를 기록하는 변수
int moveCount = 0;       // 이동 횟수를 기록하는 변수
int rounds = 0;          // 퀵소트에서의 진행 횟수를 기록하는 변수
int isFirst = 0;         // 첫 번째 실행 여부를 나타내는 변수 (0이면 첫 번째 실행)

/// 배열을 출력하는 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);  // 배열의 각 요소를 출력
    }
    printf("\n");
}

/// 랜덤한 값으로 배열을 채우는 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 랜덤한 값을 배열에 채움
    }
}

/// 퀵소트 알고리즘을 구현한 함수
void doQuickSort(int array[], int left, int right) {
    // 스택 초기화
    int stack[SIZE];
    int top = -1;  // 스택의 최상위 인덱스 초기화

    // 초기 범위 푸시 (왼쪽, 오른쪽 인덱스)
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        // 스택에서 범위 가져오기 (왼쪽, 오른쪽)
        int right = stack[top--];
        int left = stack[top--];

        // 범위가 유효하지 않으면 continue
        if (left >= right) continue;

        // 피벗을 왼쪽 가장자리로 설정
        int pivot = array[left];
        int low = left + 1;  // low는 피벗보다 큰 값을 찾기 위한 인덱스
        int high = right;    // high는 피벗보다 작은 값을 찾기 위한 인덱스

        // 분할 과정
        while (low <= high) {
            comparisonCount++;  // 비교 횟수 증가

            // 피벗보다 작은 값 찾기 (low를 증가)
            while (low <= right && array[low] <= pivot) {
                low++;
                comparisonCount++;  // 비교 횟수 증가
            }

            // 피벗보다 큰 값 찾기 (high를 감소)
            while (high > left && array[high] >= pivot) {
                high--;
                comparisonCount++;  // 비교 횟수 증가
            }

            // low가 high보다 작으면 두 값을 교환
            if (low < high) {
                int temp = array[low];
                array[low] = array[high];
                array[high] = temp;
                moveCount += 3;  // 이동 횟수 3 증가 (세 개의 값을 교환하므로)
            }
        }

        // 피벗을 high 위치로 이동
        if (left != high) {
            int temp = array[left];
            array[left] = array[high];
            array[high] = temp;
            moveCount += 3;  // 이동 횟수 3 증가 (세 개의 값을 교환하므로)
        }

        // 첫 번째 실행에서만 중간 배열 상태 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            // 배열의 20~39번째 인덱스 값을 출력
            for (int i = 20; i < 40; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");

            // 배열의 40~59번째 인덱스 값을 출력
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }
        rounds++;  // 진행 횟수 증가

        // 새로운 범위를 스택에 푸시 (분할된 두 범위에 대해 재귀적으로 퀵소트를 수행)
        if (left < high - 1) {
            stack[++top] = left;
            stack[++top] = high - 1;
        }
        if (high + 1 < right) {
            stack[++top] = high + 1;
            stack[++top] = right;
        }
    }
}

/// 메인 함수
int main() {
    srand(time(NULL));  // 랜덤 함수 초기화 (현재 시간으로 시드값 설정)
    int array[SIZE];    // 정렬할 배열
    int totalComparisons = 0;  // 모든 실행에서의 총 비교 횟수
    int totalMoveCount = 0;   // 모든 실행에서의 총 이동 횟수

    for (int i = 0; i < 20; i++) {  // 20번 반복
        generateRandomArray(array);  // 랜덤한 배열 생성

        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;       // 이동 횟수 초기화
        rounds = 0;          // 진행 횟수 초기화

        if (i == 0) {  // 첫 번째 실행
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // 퀵소트 호출
            printf("Result:\n");
            printArray(array, SIZE);  // 결과 출력
            isFirst++;  // 첫 번째 실행 이후 isFirst 값 증가
        }
        else {
            doQuickSort(array, 0, SIZE - 1);  // 두 번째 이후 실행 시 퀵소트 호출
        }

        totalComparisons += comparisonCount;  // 비교 횟수 누적
        totalMoveCount += moveCount;         // 이동 횟수 누적
    }

    // 평균 비교 횟수와 평균 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
