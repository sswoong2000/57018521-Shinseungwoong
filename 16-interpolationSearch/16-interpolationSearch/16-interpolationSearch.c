#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �迭 ũ�� �� �׽�Ʈ Ƚ�� ����
#define SIZE 10000       // �迭�� ũ��
#define TEST_COUNT 1000  // �׽�Ʈ Ƚ��

// Quick Sort �Լ�: �迭�� �����ϴ� ��� �Լ��Դϴ�.
void QuickSort(int arr[], int left, int right) {
    if (left < right) {
        // �迭�� ���� ������ ���� �ǹ����� �����մϴ�.
        int pivot = arr[right];
        int i = left - 1;  // �ǹ����� ���� ������ �����ϱ� ���� �ε���

        // �ǹ��� �������� �迭�� �����ϴ�.
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                // �ǹ����� ���� ���� �������� �̵��մϴ�.
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // �ǹ��� �ùٸ� ��ġ�� �̵��մϴ�.
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        // �ǹ��� �������� ���� �κа� ������ �κ��� ��������� �����մϴ�.
        QuickSort(arr, left, i);
        QuickSort(arr, i + 2, right);
    }
}

// �迭 ��� �Լ�: ���ĵ� �迭�� �պκа� �޺κ��� ����մϴ�.
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    // �迭�� ù 20���� ��Ҹ� ����մϴ�.
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");

    // �迭�� ������ 20���� ��Ҹ� ����մϴ�.
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Binary Search �Լ�: ���� Ž���� ����Ͽ� �迭���� ��ǥ ���� ã���ϴ�.
int BinarySearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;

    // ���� �ε����� ������ �ε����� �ʰ��� ������ Ž���մϴ�.
    while (left <= right) {
        // �߰� �ε����� ����մϴ�.
        int mid = left + (right - left) / 2;
        compareCount++; // �� Ƚ���� ������ŵ�ϴ�.

        // ��ǥ ���� ã���� �� �� Ƚ���� ��ȯ�մϴ�.
        if (array[mid] == target)
            return compareCount;

        // ��ǥ ���� �߰� ������ ũ�ų� ������ Ž�� ������ �����մϴ�.
        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return compareCount; // ���� ã�� ������ ��� �� Ƚ���� ��ȯ�մϴ�.
}

// Interpolation Search �Լ�: ���� Ž�� �˰����� ����Ͽ� �迭���� ��ǥ ���� ã���ϴ�.
int InterpolationSearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;

    // Ž�� ������ �ʰ����� �ʴ� �� Ž���� ����մϴ�.
    while (left <= right && target >= array[left] && target <= array[right]) {
        compareCount++; // �� Ƚ���� ������ŵ�ϴ�.

        // ���ʰ� ������ �ε����� ������ �� ���� Ȯ���մϴ�.
        if (left == right) {
            if (array[left] == target) return compareCount;
            break;
        }

        // ���� ������ ����Ͽ� ���� ��ġ�� ����մϴ�.
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));

        // ���� ��ġ�� ������ ����ٸ� �����մϴ�.
        if (pos < left || pos > right) break;

        // ��ǥ ���� ã���� �� �� Ƚ���� ��ȯ�մϴ�.
        if (array[pos] == target)
            return compareCount;

        // ��ǥ ���� ���� ��ġ ������ ũ�ų� ������ Ž�� ������ �����մϴ�.
        if (array[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }
    return compareCount; // ���� ã�� ������ ��� �� Ƚ���� ��ȯ�մϴ�.
}

// ��� �� Ƚ���� ����ϴ� �Լ� (Binary Search)
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;

    // �����ϰ� ���õ� ��ǥ ���鿡 ���� ���� Ž���� �����ϰ� �� Ƚ���� �����մϴ�.
    for (int i = 0; i < TEST_COUNT; i++) {
        int target = array[rand() % SIZE];
        totalCompareCount += BinarySearch(array, SIZE, target);
    }
    // ��� �� Ƚ���� ����Ͽ� ��ȯ�մϴ�.
    return totalCompareCount / TEST_COUNT;
}

// ��� �� Ƚ���� ����ϴ� �Լ� (Interpolation Search)
double getAverageInterpolationSearchCompareCount(int* array) {
    double totalCompareCount = 0;

    // �����ϰ� ���õ� ��ǥ ���鿡 ���� ���� Ž���� �����ϰ� �� Ƚ���� �����մϴ�.
    for (int i = 0; i < TEST_COUNT; i++) {
        int target = array[rand() % SIZE];
        totalCompareCount += InterpolationSearch(array, SIZE, target);
    }
    // ��� �� Ƚ���� ����Ͽ� ��ȯ�մϴ�.
    return totalCompareCount / TEST_COUNT;
}

// ���� �迭 ���� �Լ�: �迭�� 0~9999 ������ ������ ����� �ʱ�ȭ�մϴ�.
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;
}


int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    int array[SIZE];   // ���� �� Ž���� ����� �迭 ����
    generateRandomArray(array); // ���� �迭 ����

    QuickSort(array, 0, SIZE - 1); // �迭�� �����մϴ�.
    printArray(array); // ���ĵ� �迭�� ����� ����մϴ�.

    // ���� Ž���� ���� Ž���� ��� �� Ƚ���� ����ϰ� ����մϴ�.
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0; 
}
