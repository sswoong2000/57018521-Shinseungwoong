#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // �迭�� ũ�⸦ �����մϴ�. �� �ڵ�� 1000���� ��Ҹ� ���� �迭�� ����մϴ�.

// ���� ������ Quick Sort�� �� Ƚ���� �����մϴ�.
int compareCount = 0;

// �� �Լ��� 0���� 999 ������ ������ ������ �����Ͽ� �迭�� �ʱ�ȭ�մϴ�.
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0���� 999������ ������ �����մϴ�.
    }
}

// �� �Լ��� �迭���� ���� Ž���� �����ϸ� �� Ƚ���� ��ȯ�մϴ�.
int linearSearch(int* array, int target) {
    int count = 0;  // �� Ƚ���� ���ϴ�.
    for (int i = 0; i < SIZE; i++) {
        count++;
        if (array[i] == target) {  // ��ǥ���� ã���� �� Ƚ���� ��ȯ�մϴ�.
            return count;
        }
    }
    return count;  // ��ǥ���� ���� ���, Ž���� �ҿ�� �� Ƚ���� ��ȯ�մϴ�.
}

// �� �Լ��� 100���� ���� Ž���� �����ϰ� ��� �� Ƚ���� ����մϴ�.
double getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // �迭���� �������� ��ǥ���� �����մϴ�.
        totalComparisons += linearSearch(array, target);
    }
    return totalComparisons / 100.0;  // ��� �� Ƚ���� ��ȯ�մϴ�.
}

// �� �Լ��� Quick Sort�� Partition �۾��� �����ϸ�, �� Ƚ���� ī��Ʈ�մϴ�.
int partition(int* array, int low, int high) {
    int pivot = array[high];  // �ǹ��� �迭�� ������ ��ҷ� �����մϴ�.
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compareCount++;  // �� Ƚ���� ������ŵ�ϴ�.
        if (array[j] < pivot) {  // �ǹ����� ���� ��Ҹ� ������ �̵��մϴ�.
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];  // �ǹ��� ���ĵ� ��ġ�� �����ϴ�.
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;  // �ǹ��� ���� ��ġ�� ��ȯ�մϴ�.
}

// �� �Լ��� ��������� Quick Sort�� �����Ͽ� �迭�� �����մϴ�.
void quickSort(int* array, int low, int high) {
    if (low < high) {  // �迭�� ������ ��ȿ�� ��쿡�� �����մϴ�.
        int pi = partition(array, low, high);  // Partition�� �����ϰ� �ǹ� ��ġ�� ����ϴ�.
        quickSort(array, low, pi - 1);  // �ǹ����� ���� �κ� ����
        quickSort(array, pi + 1, high);  // �ǹ����� ū �κ� ����
    }
}

// �� �Լ��� Quick Sort�� �����ϰ� ��ü �� Ƚ���� ����մϴ�.
void getQuickSortCompareCount(int* array) {
    compareCount = 0;  // �� Ƚ���� �ʱ�ȭ�մϴ�.
    quickSort(array, 0, SIZE - 1);
}

// �� �Լ��� ���� Ž���� �����ϸ�, ��ǥ���� ã�� ���� �� Ƚ���� ��ȯ�մϴ�.
int binarySearch(int* array, int target) {
    int low = 0, high = SIZE - 1;
    int count = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // �߰� �ε����� ����մϴ�.
        count++;
        if (array[mid] == target) {  // ��ǥ���� ã�� ��� �� Ƚ���� ��ȯ�մϴ�.
            return count;
        }
        if (array[mid] < target) {
            low = mid + 1;  // ��ǥ���� �� ū ���, ������ �κ��� Ž���մϴ�.
        }
        else {
            high = mid - 1;  // ��ǥ���� �� ���� ���, ���� �κ��� Ž���մϴ�.
        }
    }
    return count;  // ��ǥ���� ���� ���, Ž���� �ҿ�� �� Ƚ���� ��ȯ�մϴ�.
}

// �� �Լ��� 100���� ���� Ž���� �����ϰ� ��� �� Ƚ���� ����մϴ�.
double getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // �迭���� �������� ��ǥ���� �����մϴ�.
        totalComparisons += binarySearch(array, target);
    }
    return totalComparisons / 100.0;  // ��� �� Ƚ���� ��ȯ�մϴ�.
}

// �� �Լ��� �迭�� �պκ� 20���� �޺κ� 20�� ��Ҹ� ����մϴ�.
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);  // �迭�� ù 20�� ��Ҹ� ����մϴ�.
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);  // �迭�� ������ 20�� ��Ҹ� ����մϴ�.
    printf("\n");
}

// ���α׷��� ���� �Լ��Դϴ�.
int main(int argc, char* argv[]) {
    srand(time(NULL));  // ���� �õ带 �����մϴ�.
    int array[SIZE];
    generateRandomArray(array);  // �迭�� ���� ������ �ʱ�ȭ�մϴ�.

    // ���� Ž���� ��� �� Ƚ���� ����ϰ� ����մϴ�.
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // Quick Sort�� �����ϰ� �� Ƚ���� ����մϴ�.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // ���� Ž���� ��� �� Ƚ���� ����ϰ� ����մϴ�.
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // �迭�� �պκа� �޺κ��� ����մϴ�.
    printArray(array);
    return 0;
}
