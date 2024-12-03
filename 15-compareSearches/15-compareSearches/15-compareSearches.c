#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // 배열의 크기를 정의합니다. 이 코드는 1000개의 요소를 가진 배열을 사용합니다.

// 전역 변수로 Quick Sort의 비교 횟수를 저장합니다.
int compareCount = 0;

// 이 함수는 0부터 999 사이의 임의의 정수를 생성하여 배열을 초기화합니다.
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 난수를 생성합니다.
    }
}

// 이 함수는 배열에서 선형 탐색을 수행하며 비교 횟수를 반환합니다.
int linearSearch(int* array, int target) {
    int count = 0;  // 비교 횟수를 셉니다.
    for (int i = 0; i < SIZE; i++) {
        count++;
        if (array[i] == target) {  // 목표값을 찾으면 비교 횟수를 반환합니다.
            return count;
        }
    }
    return count;  // 목표값이 없는 경우, 탐색에 소요된 비교 횟수를 반환합니다.
}

// 이 함수는 100번의 선형 탐색을 수행하고 평균 비교 횟수를 계산합니다.
double getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // 배열에서 무작위로 목표값을 선택합니다.
        totalComparisons += linearSearch(array, target);
    }
    return totalComparisons / 100.0;  // 평균 비교 횟수를 반환합니다.
}

// 이 함수는 Quick Sort의 Partition 작업을 수행하며, 비교 횟수도 카운트합니다.
int partition(int* array, int low, int high) {
    int pivot = array[high];  // 피벗을 배열의 마지막 요소로 설정합니다.
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compareCount++;  // 비교 횟수를 증가시킵니다.
        if (array[j] < pivot) {  // 피벗보다 작은 요소를 앞으로 이동합니다.
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];  // 피벗을 정렬된 위치에 놓습니다.
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;  // 피벗의 최종 위치를 반환합니다.
}

// 이 함수는 재귀적으로 Quick Sort를 수행하여 배열을 정렬합니다.
void quickSort(int* array, int low, int high) {
    if (low < high) {  // 배열의 구간이 유효할 경우에만 수행합니다.
        int pi = partition(array, low, high);  // Partition을 수행하고 피벗 위치를 얻습니다.
        quickSort(array, low, pi - 1);  // 피벗보다 작은 부분 정렬
        quickSort(array, pi + 1, high);  // 피벗보다 큰 부분 정렬
    }
}

// 이 함수는 Quick Sort를 수행하고 전체 비교 횟수를 기록합니다.
void getQuickSortCompareCount(int* array) {
    compareCount = 0;  // 비교 횟수를 초기화합니다.
    quickSort(array, 0, SIZE - 1);
}

// 이 함수는 이진 탐색을 수행하며, 목표값을 찾기 위한 비교 횟수를 반환합니다.
int binarySearch(int* array, int target) {
    int low = 0, high = SIZE - 1;
    int count = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // 중간 인덱스를 계산합니다.
        count++;
        if (array[mid] == target) {  // 목표값을 찾은 경우 비교 횟수를 반환합니다.
            return count;
        }
        if (array[mid] < target) {
            low = mid + 1;  // 목표값이 더 큰 경우, 오른쪽 부분을 탐색합니다.
        }
        else {
            high = mid - 1;  // 목표값이 더 작은 경우, 왼쪽 부분을 탐색합니다.
        }
    }
    return count;  // 목표값이 없는 경우, 탐색에 소요된 비교 횟수를 반환합니다.
}

// 이 함수는 100번의 이진 탐색을 수행하고 평균 비교 횟수를 계산합니다.
double getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // 배열에서 무작위로 목표값을 선택합니다.
        totalComparisons += binarySearch(array, target);
    }
    return totalComparisons / 100.0;  // 평균 비교 횟수를 반환합니다.
}

// 이 함수는 배열의 앞부분 20개와 뒷부분 20개 요소를 출력합니다.
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);  // 배열의 첫 20개 요소를 출력합니다.
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);  // 배열의 마지막 20개 요소를 출력합니다.
    printf("\n");
}

// 프로그램의 메인 함수입니다.
int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드를 설정합니다.
    int array[SIZE];
    generateRandomArray(array);  // 배열을 랜덤 값으로 초기화합니다.

    // 선형 탐색의 평균 비교 횟수를 계산하고 출력합니다.
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // Quick Sort를 수행하고 비교 횟수를 출력합니다.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 이진 탐색의 평균 비교 횟수를 계산하고 출력합니다.
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // 배열의 앞부분과 뒷부분을 출력합니다.
    printArray(array);
    return 0;
}
