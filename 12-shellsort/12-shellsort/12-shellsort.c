#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100


// 주어진 배열에 0에서 999 사이의 난수를 채웁니다.
void generateRandomNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // 0과 999 사이의 난수 생성
    }
}


// 만약 배열의 크기가 20보다 크다면 '...'을 표시하여 생략된 부분을 알려줍니다.
void printTruncatedArray(int arr[], int size) {
    for (int i = 0; i < 20 && i < size; i++) {
        printf("%d ", arr[i]);
    }
    if (size > 20) {
        printf("..."); // 배열이 크면 생략된 부분을 표시합니다.
    }
    printf("\n\n");
}

// 함수: 배열을 완전하게 출력하는 함수입니다.
// 배열의 모든 요소를 출력합니다.
void printFullArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}


// 원본 배열을 복사하여 새 배열에 저장합니다.
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}


// gapType에 따라 gap 값을 n/2 또는 n/3으로 설정하고 정렬을 진행합니다.
// 각 비교와 이동을 셈하고, 정렬 중간 결과를 출력합니다.
void doShellSort(int arr[], int gapType, int* compCount, int* moveCount) {
    int gap, i, j, temp;
    *compCount = 0;
    *moveCount = 0;

    int arrCopy[ARRAY_SIZE];
    copyArray(arr, arrCopy, ARRAY_SIZE);  // 배열을 정렬 전에 복사합니다.

    gap = (gapType == 2) ? ARRAY_SIZE / 2 : ARRAY_SIZE / 3; // gap 값을 n/2 또는 n/3으로 설정합니다.
    while (gap > 0) {
        printf("Sorting with gap = %d:\n", gap); // gap에 따른 정렬을 출력합니다.
        for (i = gap; i < ARRAY_SIZE; i++) {
            temp = arrCopy[i];
            j = i;

            // 비교와 이동을 셈
            while (j >= gap) {
                (*compCount)++; // 각 비교를 셉니다.
                if (arrCopy[j - gap] > temp) {
                    arrCopy[j] = arrCopy[j - gap];
                    j -= gap;
                    (*moveCount)++; // 각 이동을 셉니다.
                }
                else {
                    break;
                }
            }
            arrCopy[j] = temp;
            (*moveCount)++; // 최종적으로 자리를 바꾼 것도 이동으로 셉니다.
        }
        printTruncatedArray(arrCopy, ARRAY_SIZE); // 중간 결과를 출력합니다.
        gap = (gapType == 2) ? gap / 2 : gap / 3; // gap을 반으로 줄이거나 3분의 1로 줄입니다.
    }
    printf("Sorted array (gap = %d):\n", gapType);
    printFullArray(arrCopy, ARRAY_SIZE); // 최종적으로 정렬된 배열을 출력합니다.
}


// 배열을 정렬하고, 비교와 이동 횟수를 셉니다.
void doInsertionSort(int arr[], int* compCount, int* moveCount) {
    int i, j, temp;
    *compCount = 0;
    *moveCount = 0;

    int arrCopy[ARRAY_SIZE];
    copyArray(arr, arrCopy, ARRAY_SIZE);  // 배열을 정렬 전에 복사합니다.

    for (i = 1; i < ARRAY_SIZE; i++) {
        temp = arrCopy[i];
        j = i - 1;

        // temp보다 큰 요소를 오른쪽으로 밀어내기
        while (j >= 0 && arrCopy[j] > temp) {
            arrCopy[j + 1] = arrCopy[j];
            j--;
            (*compCount)++; // 각 비교를 셉니다.
            (*moveCount)++; // 각 이동을 셉니다.
        }
        arrCopy[j + 1] = temp;
        (*moveCount)++; // 최종적으로 자리를 바꾼 것도 이동으로 셉니다.
        if (j >= 0) {
            (*compCount)++; // 한 번 더 비교를 진행한 경우를 셉니다.
        }
    }
    printf("Sorted array with insertion sort:\n");
    printFullArray(arrCopy, ARRAY_SIZE); 
}


// 난수 배열을 생성하고, 쉘 정렬과 삽입 정렬을 실행한 후, 각 정렬의 비교 횟수와 이동 횟수를 출력합니다.
int main() {
    srand(time(NULL)); // 난수 생성의 시드를 현재 시간으로 설정합니다.

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // 배열에 난수를 생성합니다.
    generateRandomNumbers(array, ARRAY_SIZE);

    // 쉘 정렬 (n/2 방식)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 쉘 정렬 (n/3 방식)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 삽입 정렬
    printf("\nInsertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
