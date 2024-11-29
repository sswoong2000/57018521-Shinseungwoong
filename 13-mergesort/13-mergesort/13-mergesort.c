#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // �迭 ũ�� (100���� ������)
int comparisonCount = 0; // �� Ƚ���� ī��Ʈ�ϴ� �����Դϴ�.
int moveCount = 0;       // �̵� Ƚ���� ī��Ʈ�ϴ� �����Դϴ�.

// �Լ� ����
void generateRandomArray(int array[]); // �迭�� ���� ���� �����ϴ� �Լ��Դϴ�.
void doMergeSort(int array[], int size); // �ݺ����� ������� �պ� ������ �����ϴ� �Լ��Դϴ�.
void merge(int array[], int left, int mid, int right, int temp[]); // �� �κ� �迭�� �����ϴ� �Լ��Դϴ�.
void printArray(int array[], int size); // �迭�� ������ ����ϴ� �Լ��Դϴ�.

// �迭�� ���� ���� �����ϴ� �Լ��Դϴ�.
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0���� 999 ������ ���� ���� �����մϴ�.
    }
}

// �ݺ����� ������� �պ� ������ �����ϴ� �Լ��Դϴ�.
void doMergeSort(int array[], int size) {
    int temp[SIZE]; // ���� �۾��� ����� �ӽ� �迭�Դϴ�.
    int rounds = 0; // ��� ������ �����ϱ� ���� �����Դϴ�.

    // width�� ������ �κ� �迭�� ũ�⸦ ��Ÿ���ϴ�.
    for (int width = 1; width < size; width *= 2) {
        // �� �ܰ迡�� �迭�� �����մϴ�.
        for (int i = 0; i < size; i += 2 * width) {
            int left = i;                          // ���� �κ� �迭�� ���� �ε����Դϴ�.
            int mid = i + width < size ? i + width : size; // �߰� ���� (������ ��)�� ��Ÿ���ϴ�.
            int right = i + 2 * width < size ? i + 2 * width : size; // ������ ���� ��Ÿ���ϴ�.

            // �� �κ� �迭�� �����մϴ�.
            merge(array, left, mid, right, temp);

            rounds++; // ���� �۾��� �� �� ����Ǿ����� ī��Ʈ�մϴ�.

            // 10������ ���� �迭 ���¸� ����մϴ�.
            if (rounds % 10 == 0) {
                for (int i = 0; i < 10; i++) // �迭�� ó�� 10���� ��Ҹ� ����մϴ�.
                    printf("%3d ", array[i]);
                printf("! ");
                for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // �迭 �߾Ӱ� ��ó�� ���� ����մϴ�.
                    printf("%3d ", array[i]);
                printf("\n");
            }
        }
    }
}

// �� �κ� �迭�� �����ϴ� �Լ��Դϴ�.
void merge(int array[], int left, int mid, int right, int temp[]) {
    int l = left;   // ���� �κ� �迭�� ���� �ε����Դϴ�.
    int r = mid;    // ������ �κ� �迭�� ���� �ε����Դϴ�.
    int k = left;   // �ӽ� �迭������ �ε����� ��Ÿ���ϴ�.

    // ���� ����: �� �迭�� ���� ���Ͽ� ���� ���� temp�� �����մϴ�.
    while (l < mid && r < right) {
        comparisonCount++; // �� Ƚ���� ������ŵ�ϴ�.
        if (array[l] <= array[r]) {
            temp[k++] = array[l++];
            moveCount++; // �̵� Ƚ���� ������ŵ�ϴ�.
        }
        else {
            temp[k++] = array[r++];
            moveCount++; // �̵� Ƚ���� ������ŵ�ϴ�.
        }
    }

    // ���� �迭�� ���� ������ ó���մϴ�.
    while (l < mid) {
        temp[k++] = array[l++];
        moveCount++; // �̵� Ƚ���� ������ŵ�ϴ�.
    }

    // ������ �迭�� ���� ������ ó���մϴ�.
    while (r < right) {
        temp[k++] = array[r++];
        moveCount++; // �̵� Ƚ���� ������ŵ�ϴ�.
    }

    // ���յ� ����� ���� �迭�� �����մϴ�.
    for (int i = left; i < right; i++) {
        array[i] = temp[i];
        moveCount++; // �̵� Ƚ���� ������ŵ�ϴ�.
    }
}

// �迭�� ������ ����ϴ� �Լ��Դϴ�.
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]); // �迭�� �� ���� ����մϴ�.
        if ((i + 1) % 10 == 0)   // 10���� ��� �� �� �ٲ��� �߰��մϴ�.
            printf("\n");
    }
}

int main() {
    int array[SIZE];
    int totalComparisons = 0; // �� �� Ƚ���� �����ϴ� �����Դϴ�.
    int totalMoves = 0;       // �� �̵� Ƚ���� �����ϴ� �����Դϴ�.
    int isFirst = 0;          // ó�� ���� ���θ� ��Ÿ���� �����Դϴ�.

    srand((unsigned)time(NULL)); // ���� �õ带 �ʱ�ȭ�մϴ�.

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // ���� �迭�� �����մϴ�.
        comparisonCount = 0; // �� Ƚ���� �ʱ�ȭ�մϴ�.
        moveCount = 0;       // �̵� Ƚ���� �ʱ�ȭ�մϴ�.

        // ù ��° ������ ��� Merge Sort Run�� ����մϴ�.
        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, SIZE); // �պ� ������ �����մϴ�.

            printf("\nResult\n");
            printArray(array, SIZE); // ���ĵ� ����� ����մϴ�.
            isFirst++;
        }
        else {
            doMergeSort(array, SIZE); // �պ� ������ �����մϴ�.
        }

        // �� Ƚ���� �̵� Ƚ���� �����մϴ�.
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // ��� �� Ƚ���� �̵� Ƚ���� ����մϴ�.
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
