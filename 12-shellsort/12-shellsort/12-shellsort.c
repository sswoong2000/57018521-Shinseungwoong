#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100


// �־��� �迭�� 0���� 999 ������ ������ ä��ϴ�.
void generateRandomNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // 0�� 999 ������ ���� ����
    }
}


// ���� �迭�� ũ�Ⱑ 20���� ũ�ٸ� '...'�� ǥ���Ͽ� ������ �κ��� �˷��ݴϴ�.
void printTruncatedArray(int arr[], int size) {
    for (int i = 0; i < 20 && i < size; i++) {
        printf("%d ", arr[i]);
    }
    if (size > 20) {
        printf("..."); // �迭�� ũ�� ������ �κ��� ǥ���մϴ�.
    }
    printf("\n\n");
}

// �Լ�: �迭�� �����ϰ� ����ϴ� �Լ��Դϴ�.
// �迭�� ��� ��Ҹ� ����մϴ�.
void printFullArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}


// ���� �迭�� �����Ͽ� �� �迭�� �����մϴ�.
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}


// gapType�� ���� gap ���� n/2 �Ǵ� n/3���� �����ϰ� ������ �����մϴ�.
// �� �񱳿� �̵��� ���ϰ�, ���� �߰� ����� ����մϴ�.
void doShellSort(int arr[], int gapType, int* compCount, int* moveCount) {
    int gap, i, j, temp;
    *compCount = 0;
    *moveCount = 0;

    int arrCopy[ARRAY_SIZE];
    copyArray(arr, arrCopy, ARRAY_SIZE);  // �迭�� ���� ���� �����մϴ�.

    gap = (gapType == 2) ? ARRAY_SIZE / 2 : ARRAY_SIZE / 3; // gap ���� n/2 �Ǵ� n/3���� �����մϴ�.
    while (gap > 0) {
        printf("Sorting with gap = %d:\n", gap); // gap�� ���� ������ ����մϴ�.
        for (i = gap; i < ARRAY_SIZE; i++) {
            temp = arrCopy[i];
            j = i;

            // �񱳿� �̵��� ��
            while (j >= gap) {
                (*compCount)++; // �� �񱳸� ���ϴ�.
                if (arrCopy[j - gap] > temp) {
                    arrCopy[j] = arrCopy[j - gap];
                    j -= gap;
                    (*moveCount)++; // �� �̵��� ���ϴ�.
                }
                else {
                    break;
                }
            }
            arrCopy[j] = temp;
            (*moveCount)++; // ���������� �ڸ��� �ٲ� �͵� �̵����� ���ϴ�.
        }
        printTruncatedArray(arrCopy, ARRAY_SIZE); // �߰� ����� ����մϴ�.
        gap = (gapType == 2) ? gap / 2 : gap / 3; // gap�� ������ ���̰ų� 3���� 1�� ���Դϴ�.
    }
    printf("Sorted array (gap = %d):\n", gapType);
    printFullArray(arrCopy, ARRAY_SIZE); // ���������� ���ĵ� �迭�� ����մϴ�.
}


// �迭�� �����ϰ�, �񱳿� �̵� Ƚ���� ���ϴ�.
void doInsertionSort(int arr[], int* compCount, int* moveCount) {
    int i, j, temp;
    *compCount = 0;
    *moveCount = 0;

    int arrCopy[ARRAY_SIZE];
    copyArray(arr, arrCopy, ARRAY_SIZE);  // �迭�� ���� ���� �����մϴ�.

    for (i = 1; i < ARRAY_SIZE; i++) {
        temp = arrCopy[i];
        j = i - 1;

        // temp���� ū ��Ҹ� ���������� �о��
        while (j >= 0 && arrCopy[j] > temp) {
            arrCopy[j + 1] = arrCopy[j];
            j--;
            (*compCount)++; // �� �񱳸� ���ϴ�.
            (*moveCount)++; // �� �̵��� ���ϴ�.
        }
        arrCopy[j + 1] = temp;
        (*moveCount)++; // ���������� �ڸ��� �ٲ� �͵� �̵����� ���ϴ�.
        if (j >= 0) {
            (*compCount)++; // �� �� �� �񱳸� ������ ��츦 ���ϴ�.
        }
    }
    printf("Sorted array with insertion sort:\n");
    printFullArray(arrCopy, ARRAY_SIZE); 
}


// ���� �迭�� �����ϰ�, �� ���İ� ���� ������ ������ ��, �� ������ �� Ƚ���� �̵� Ƚ���� ����մϴ�.
int main() {
    srand(time(NULL)); // ���� ������ �õ带 ���� �ð����� �����մϴ�.

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // �迭�� ������ �����մϴ�.
    generateRandomNumbers(array, ARRAY_SIZE);

    // �� ���� (n/2 ���)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // �� ���� (n/3 ���)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // ���� ����
    printf("\nInsertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
