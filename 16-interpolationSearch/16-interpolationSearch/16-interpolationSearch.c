#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 배열 크기 및 테스트 횟수 정의
#define SIZE 10000       // 배열의 크기
#define TEST_COUNT 1000  // 테스트 횟수

// Quick Sort 함수: 배열을 정렬하는 재귀 함수입니다.
void QuickSort(int arr[], int left, int right) {
    if (left < right) {
        // 배열의 가장 오른쪽 값을 피벗으로 설정합니다.
        int pivot = arr[right];
        int i = left - 1;  // 피벗보다 작은 값들을 정렬하기 위한 인덱스

        // 피벗을 기준으로 배열을 나눕니다.
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                // 피벗보다 작은 값을 왼쪽으로 이동합니다.
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // 피벗을 올바른 위치로 이동합니다.
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        // 피벗을 기준으로 왼쪽 부분과 오른쪽 부분을 재귀적으로 정렬합니다.
        QuickSort(arr, left, i);
        QuickSort(arr, i + 2, right);
    }
}

// 배열 출력 함수: 정렬된 배열의 앞부분과 뒷부분을 출력합니다.
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    // 배열의 첫 20개의 요소를 출력합니다.
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");

    // 배열의 마지막 20개의 요소를 출력합니다.
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Binary Search 함수: 이진 탐색을 사용하여 배열에서 목표 값을 찾습니다.
int BinarySearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;

    // 왼쪽 인덱스가 오른쪽 인덱스를 초과할 때까지 탐색합니다.
    while (left <= right) {
        // 중간 인덱스를 계산합니다.
        int mid = left + (right - left) / 2;
        compareCount++; // 비교 횟수를 증가시킵니다.

        // 목표 값을 찾았을 때 비교 횟수를 반환합니다.
        if (array[mid] == target)
            return compareCount;

        // 목표 값이 중간 값보다 크거나 작으면 탐색 범위를 조정합니다.
        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return compareCount; // 값을 찾지 못했을 경우 비교 횟수를 반환합니다.
}

// Interpolation Search 함수: 보간 탐색 알고리즘을 사용하여 배열에서 목표 값을 찾습니다.
int InterpolationSearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;

    // 탐색 범위를 초과하지 않는 한 탐색을 계속합니다.
    while (left <= right && target >= array[left] && target <= array[right]) {
        compareCount++; // 비교 횟수를 증가시킵니다.

        // 왼쪽과 오른쪽 인덱스가 동일할 때 값을 확인합니다.
        if (left == right) {
            if (array[left] == target) return compareCount;
            break;
        }

        // 보간 공식을 사용하여 예상 위치를 계산합니다.
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));

        // 예상 위치가 범위를 벗어났다면 종료합니다.
        if (pos < left || pos > right) break;

        // 목표 값을 찾았을 때 비교 횟수를 반환합니다.
        if (array[pos] == target)
            return compareCount;

        // 목표 값이 예상 위치 값보다 크거나 작으면 탐색 범위를 조정합니다.
        if (array[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }
    return compareCount; // 값을 찾지 못했을 경우 비교 횟수를 반환합니다.
}

// 평균 비교 횟수를 계산하는 함수 (Binary Search)
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;

    // 랜덤하게 선택된 목표 값들에 대해 이진 탐색을 수행하고 비교 횟수를 누적합니다.
    for (int i = 0; i < TEST_COUNT; i++) {
        int target = array[rand() % SIZE];
        totalCompareCount += BinarySearch(array, SIZE, target);
    }
    // 평균 비교 횟수를 계산하여 반환합니다.
    return totalCompareCount / TEST_COUNT;
}

// 평균 비교 횟수를 계산하는 함수 (Interpolation Search)
double getAverageInterpolationSearchCompareCount(int* array) {
    double totalCompareCount = 0;

    // 랜덤하게 선택된 목표 값들에 대해 보간 탐색을 수행하고 비교 횟수를 누적합니다.
    for (int i = 0; i < TEST_COUNT; i++) {
        int target = array[rand() % SIZE];
        totalCompareCount += InterpolationSearch(array, SIZE, target);
    }
    // 평균 비교 횟수를 계산하여 반환합니다.
    return totalCompareCount / TEST_COUNT;
}

// 랜덤 배열 생성 함수: 배열을 0~9999 범위의 랜덤한 값들로 초기화합니다.
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;
}


int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 초기화
    int array[SIZE];   // 정렬 및 탐색에 사용할 배열 선언
    generateRandomArray(array); // 랜덤 배열 생성

    QuickSort(array, 0, SIZE - 1); // 배열을 정렬합니다.
    printArray(array); // 정렬된 배열의 결과를 출력합니다.

    // 이진 탐색과 보간 탐색의 평균 비교 횟수를 계산하고 출력합니다.
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0; 
}
