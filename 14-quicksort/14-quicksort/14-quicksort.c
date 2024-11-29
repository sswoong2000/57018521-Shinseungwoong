#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// ���� ����
int comparisonCount = 0;  // �� Ƚ���� ����ϴ� ����
int moveCount = 0;       // �̵� Ƚ���� ����ϴ� ����
int rounds = 0;          // ����Ʈ������ ���� Ƚ���� ����ϴ� ����
int isFirst = 0;         // ù ��° ���� ���θ� ��Ÿ���� ���� (0�̸� ù ��° ����)

/// �迭�� ����ϴ� �Լ�
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);  // �迭�� �� ��Ҹ� ���
    }
    printf("\n");
}

/// ������ ������ �迭�� ä��� �Լ�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0���� 999������ ������ ���� �迭�� ä��
    }
}

/// ����Ʈ �˰����� ������ �Լ�
void doQuickSort(int array[], int left, int right) {
    // ���� �ʱ�ȭ
    int stack[SIZE];
    int top = -1;  // ������ �ֻ��� �ε��� �ʱ�ȭ

    // �ʱ� ���� Ǫ�� (����, ������ �ε���)
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        // ���ÿ��� ���� �������� (����, ������)
        int right = stack[top--];
        int left = stack[top--];

        // ������ ��ȿ���� ������ continue
        if (left >= right) continue;

        // �ǹ��� ���� �����ڸ��� ����
        int pivot = array[left];
        int low = left + 1;  // low�� �ǹ����� ū ���� ã�� ���� �ε���
        int high = right;    // high�� �ǹ����� ���� ���� ã�� ���� �ε���

        // ���� ����
        while (low <= high) {
            comparisonCount++;  // �� Ƚ�� ����

            // �ǹ����� ���� �� ã�� (low�� ����)
            while (low <= right && array[low] <= pivot) {
                low++;
                comparisonCount++;  // �� Ƚ�� ����
            }

            // �ǹ����� ū �� ã�� (high�� ����)
            while (high > left && array[high] >= pivot) {
                high--;
                comparisonCount++;  // �� Ƚ�� ����
            }

            // low�� high���� ������ �� ���� ��ȯ
            if (low < high) {
                int temp = array[low];
                array[low] = array[high];
                array[high] = temp;
                moveCount += 3;  // �̵� Ƚ�� 3 ���� (�� ���� ���� ��ȯ�ϹǷ�)
            }
        }

        // �ǹ��� high ��ġ�� �̵�
        if (left != high) {
            int temp = array[left];
            array[left] = array[high];
            array[high] = temp;
            moveCount += 3;  // �̵� Ƚ�� 3 ���� (�� ���� ���� ��ȯ�ϹǷ�)
        }

        // ù ��° ���࿡���� �߰� �迭 ���� ���
        if (rounds % 10 == 0 && isFirst == 0) {
            // �迭�� 20~39��° �ε��� ���� ���
            for (int i = 20; i < 40; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");

            // �迭�� 40~59��° �ε��� ���� ���
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }
        rounds++;  // ���� Ƚ�� ����

        // ���ο� ������ ���ÿ� Ǫ�� (���ҵ� �� ������ ���� ��������� ����Ʈ�� ����)
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

/// ���� �Լ�
int main() {
    srand(time(NULL));  // ���� �Լ� �ʱ�ȭ (���� �ð����� �õ尪 ����)
    int array[SIZE];    // ������ �迭
    int totalComparisons = 0;  // ��� ���࿡���� �� �� Ƚ��
    int totalMoveCount = 0;   // ��� ���࿡���� �� �̵� Ƚ��

    for (int i = 0; i < 20; i++) {  // 20�� �ݺ�
        generateRandomArray(array);  // ������ �迭 ����

        comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;       // �̵� Ƚ�� �ʱ�ȭ
        rounds = 0;          // ���� Ƚ�� �ʱ�ȭ

        if (i == 0) {  // ù ��° ����
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // ����Ʈ ȣ��
            printf("Result:\n");
            printArray(array, SIZE);  // ��� ���
            isFirst++;  // ù ��° ���� ���� isFirst �� ����
        }
        else {
            doQuickSort(array, 0, SIZE - 1);  // �� ��° ���� ���� �� ����Ʈ ȣ��
        }

        totalComparisons += comparisonCount;  // �� Ƚ�� ����
        totalMoveCount += moveCount;         // �̵� Ƚ�� ����
    }

    // ��� �� Ƚ���� ��� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
