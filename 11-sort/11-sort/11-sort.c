#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100        // 배열 크기 정의
#define ATTEMPTS 20     // 시도 횟수 정의

// 배열 출력 함수
// 이 함수는 배열을 받아 첫 100개의 요소를 출력합니다. 출력이 10개씩 구분되어 표시됩니다.
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0); // 10개마다 개행
    }
    printf("\n");
}

// 랜덤 데이터 생성 함수
// 이 함수는 배열을 받아 각 요소에 0에서 999 사이의 랜덤한 값을 할당합니다.
void generateRandomData(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000; // 0~999 사이의 난수
    }
}

// 선택 정렬 함수
// 이 함수는 선택 정렬 알고리즘을 사용하여 배열을 정렬합니다. 정렬 과정과 각 단계별 배열 상태를 출력합니다.
void doSelectionSort(int arr[]) {
    printf("Selection Sort Process:\n");
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = arr[i]; // 원본 데이터 복사
    int temp_val, min_idx;

    for (int i = 0; i < SIZE - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (temp[j] < temp[min_idx]) {
                min_idx = j;
            }
        }
        temp_val = temp[i];
        temp[i] = temp[min_idx];
        temp[min_idx] = temp_val;

        // 10부터 20 단위 및 마지막(99번째) 출력
        if (i + 1 == 10 || (i + 1) % 20 == 10 || i + 1 == 99) {
            printf("\nAfter %d steps:", i + 1);
            printArray(temp, SIZE);
        }
    }
}

// 삽입 정렬 함수
// 이 함수는 삽입 정렬 알고리즘을 사용하여 배열을 정렬합니다. ATTEMPTS 만큼 새로운 데이터 세트를 생성하고 각 세트에서 평균 비교 횟수를 계산한 후, 최종적으로 하나의 데이터 세트를 사용하여 정렬된 배열을 출력합니다.
void doInsertionSort(int arr[]) {
    int total_comparisons = 0;

    for (int t = 0; t < ATTEMPTS; t++) {
        int temp[SIZE];
        generateRandomData(temp); // 매번 새로운 데이터 생성
        int comparisons = 0;

        for (int i = 1; i < SIZE; i++) {
            int key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j] > key) {
                temp[j + 1] = temp[j];
                j--;
                comparisons++;
            }
            comparisons++;
            temp[j + 1] = key;
        }
        total_comparisons += comparisons;
    }

    printf("\nInsertion Sort Compare Average: %.0f\n", (double)total_comparisons / ATTEMPTS);
    printf("Insertion Sort Result:\n");
    int final_data[SIZE];
    generateRandomData(final_data);
    for (int i = 1; i < SIZE; i++) {
        int key = final_data[i];
        int j = i - 1;
        while (j >= 0 && final_data[j] > key) {
            final_data[j + 1] = final_data[j];
            j--;
        }
        final_data[j + 1] = key;
    }
    printArray(final_data, SIZE);
}

// 버블 정렬 함수
// 이 함수는 버블 정렬 알고리즘을 사용하여 배열을 정렬합니다. ATTEMPTS 만큼 새로운 데이터 세트를 생성하고 각 세트에서 평균 이동 횟수를 계산한 후, 최종적으로 하나의 데이터 세트를 사용하여 정렬된 배열을 출력합니다.
void doBubbleSort(int arr[]) {
    int total_moves = 0;

    for (int t = 0; t < ATTEMPTS; t++) {
        int temp[SIZE];
        generateRandomData(temp); // 매번 새로운 데이터 생성

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int temp_val = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = temp_val;
                    total_moves += 3; // swap당 3회 이동
                }
            }
        }
    }

    printf("\nBubble Sort Move Average: %.0f\n", (double)total_moves / ATTEMPTS);
    printf("Bubble Sort Result:\n");
    int final_data[SIZE];
    generateRandomData(final_data);
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (final_data[j] > final_data[j + 1]) {
                int temp_val = final_data[j];
                final_data[j] = final_data[j + 1];
                final_data[j + 1] = temp_val;
            }
        }
    }
    printArray(final_data, SIZE);
}


int main() {
    int randomData[SIZE];
    srand(time(NULL));

    // 랜덤 데이터 생성
    generateRandomData(randomData);

    // 각 정렬 수행
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
