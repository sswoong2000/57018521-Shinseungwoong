#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // 배열 크기 (100개의 데이터)
int comparisonCount = 0; // 비교 횟수를 카운트하는 변수입니다.
int moveCount = 0;       // 이동 횟수를 카운트하는 변수입니다.

// 함수 선언
void generateRandomArray(int array[]); // 배열에 랜덤 값을 생성하는 함수입니다.
void doMergeSort(int array[], int size); // 반복적인 방식으로 합병 정렬을 수행하는 함수입니다.
void merge(int array[], int left, int mid, int right, int temp[]); // 두 부분 배열을 병합하는 함수입니다.
void printArray(int array[], int size); // 배열의 내용을 출력하는 함수입니다.

// 배열에 랜덤 값을 생성하는 함수입니다.
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0부터 999 사이의 랜덤 값을 생성합니다.
    }
}

// 반복적인 방식으로 합병 정렬을 수행하는 함수입니다.
void doMergeSort(int array[], int size) {
    int temp[SIZE]; // 병합 작업에 사용할 임시 배열입니다.
    int rounds = 0; // 출력 조건을 제어하기 위한 변수입니다.

    // width는 병합할 부분 배열의 크기를 나타냅니다.
    for (int width = 1; width < size; width *= 2) {
        // 각 단계에서 배열을 병합합니다.
        for (int i = 0; i < size; i += 2 * width) {
            int left = i;                          // 왼쪽 부분 배열의 시작 인덱스입니다.
            int mid = i + width < size ? i + width : size; // 중간 지점 (병합의 끝)을 나타냅니다.
            int right = i + 2 * width < size ? i + 2 * width : size; // 오른쪽 끝을 나타냅니다.

            // 두 부분 배열을 병합합니다.
            merge(array, left, mid, right, temp);

            rounds++; // 병합 작업이 몇 번 수행되었는지 카운트합니다.

            // 10번마다 현재 배열 상태를 출력합니다.
            if (rounds % 10 == 0) {
                for (int i = 0; i < 10; i++) // 배열의 처음 10개의 요소를 출력합니다.
                    printf("%3d ", array[i]);
                printf("! ");
                for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 배열 중앙값 근처의 값을 출력합니다.
                    printf("%3d ", array[i]);
                printf("\n");
            }
        }
    }
}

// 두 부분 배열을 병합하는 함수입니다.
void merge(int array[], int left, int mid, int right, int temp[]) {
    int l = left;   // 왼쪽 부분 배열의 시작 인덱스입니다.
    int r = mid;    // 오른쪽 부분 배열의 시작 인덱스입니다.
    int k = left;   // 임시 배열에서의 인덱스를 나타냅니다.

    // 병합 과정: 두 배열의 값을 비교하여 작은 값을 temp에 저장합니다.
    while (l < mid && r < right) {
        comparisonCount++; // 비교 횟수를 증가시킵니다.
        if (array[l] <= array[r]) {
            temp[k++] = array[l++];
            moveCount++; // 이동 횟수를 증가시킵니다.
        }
        else {
            temp[k++] = array[r++];
            moveCount++; // 이동 횟수를 증가시킵니다.
        }
    }

    // 왼쪽 배열에 남은 값들을 처리합니다.
    while (l < mid) {
        temp[k++] = array[l++];
        moveCount++; // 이동 횟수를 증가시킵니다.
    }

    // 오른쪽 배열에 남은 값들을 처리합니다.
    while (r < right) {
        temp[k++] = array[r++];
        moveCount++; // 이동 횟수를 증가시킵니다.
    }

    // 병합된 결과를 원래 배열로 복사합니다.
    for (int i = left; i < right; i++) {
        array[i] = temp[i];
        moveCount++; // 이동 횟수를 증가시킵니다.
    }
}

// 배열의 내용을 출력하는 함수입니다.
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]); // 배열의 각 값을 출력합니다.
        if ((i + 1) % 10 == 0)   // 10개씩 출력 후 줄 바꿈을 추가합니다.
            printf("\n");
    }
}

int main() {
    int array[SIZE];
    int totalComparisons = 0; // 총 비교 횟수를 저장하는 변수입니다.
    int totalMoves = 0;       // 총 이동 횟수를 저장하는 변수입니다.
    int isFirst = 0;          // 처음 실행 여부를 나타내는 변수입니다.

    srand((unsigned)time(NULL)); // 랜덤 시드를 초기화합니다.

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // 랜덤 배열을 생성합니다.
        comparisonCount = 0; // 비교 횟수를 초기화합니다.
        moveCount = 0;       // 이동 횟수를 초기화합니다.

        // 첫 번째 실행일 경우 Merge Sort Run을 출력합니다.
        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, SIZE); // 합병 정렬을 수행합니다.

            printf("\nResult\n");
            printArray(array, SIZE); // 정렬된 결과를 출력합니다.
            isFirst++;
        }
        else {
            doMergeSort(array, SIZE); // 합병 정렬을 수행합니다.
        }

        // 비교 횟수와 이동 횟수를 누적합니다.
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // 평균 비교 횟수와 이동 횟수를 출력합니다.
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
