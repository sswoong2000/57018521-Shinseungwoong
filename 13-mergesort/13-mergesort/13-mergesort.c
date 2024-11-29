#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // �迭�� ũ�⸦ 100���� ����

int rounds = 0;  // mergeSort�� ���� Ƚ���� ����ϴ� ����
int comparisonCount = 0;  // �� Ƚ���� ����ϴ� ����
int moveCount = 0;  // ������ �̵� Ƚ���� ����ϴ� ����
int totalComparisons = 0;  // ��ü �� Ƚ���� ����
int totalMoves = 0;  // ��ü �̵� Ƚ���� ����
int isFirst = 0;  // ù ��° ���� ���θ� üũ�ϴ� ����

// ���� �迭 ���� �Լ�
void generateRandomArray(int array[]) {
    // SIZE ũ�⸸ŭ ���� ���� �����Ͽ� �迭�� �����մϴ�.
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0-999 ������ ���� ��
    }
}

// �迭 ��� �Լ�
void printArray(int array[], int size) {
    // �迭�� ��� ���Ҹ� ����մϴ�.
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// �ݺ��� �պ� ���� �Լ�
void doMergeSort(int array[]) {
    int temp[SIZE];  // �ӽ� �迭 ����

    // �պ� ���Ŀ����� '��'�� 1���� �����Ͽ�, ���� 2�辿 �����ϸ鼭 �ݺ��մϴ�.
    for (int width = 1; width < SIZE; width *= 2) {
        // �迭�� '��' ũ�⸸ŭ ������ �� ���� �κ� �迭�� �����մϴ�.
        for (int i = 0; i < SIZE; i += 2 * width) {
            int left = i;  // ���� �κ� �迭�� ���� �ε���
            int mid = i + width < SIZE ? i + width : SIZE;  // ��� �ε��� (�߰� ��)
            int right = i + 2 * width < SIZE ? i + 2 * width : SIZE;  // ������ �κ� �迭�� �� �ε���

            int l = left, r = mid, k = left;  // ����, ������, �ӽ� �迭�� �ε���

            // �� �迭�� �����ϴ� ����
            while (l < mid && r < right) {
                comparisonCount++;  // �� Ƚ�� ����
                if (array[l] <= array[r]) {
                    temp[k++] = array[l++];  // ���� �迭�� ���� �ӽ� �迭�� �ְ� ���� �ε��� ����
                    moveCount++;  // �̵� Ƚ�� ����
                }
                else {
                    temp[k++] = array[r++];  // ������ �迭�� ���� �ӽ� �迭�� �ְ� ������ �ε��� ����
                    moveCount++;  // �̵� Ƚ�� ����
                }
            }

            // ���� �迭�� ���� ���Ҹ� �ӽ� �迭�� ����
            while (l < mid) {
                temp[k++] = array[l++];
                moveCount++;  // �̵� Ƚ�� ����
            }

            // ������ �迭�� ���� ���Ҹ� �ӽ� �迭�� ����
            while (r < right) {
                temp[k++] = array[r++];
                moveCount++;  // �̵� Ƚ�� ����
            }

            // �ӽ� �迭���� ���� �迭�� �� ����
            for (int j = left; j < right; j++) {
                array[j] = temp[j];
                moveCount++;  // �̵� Ƚ�� ����
            }

            // �߰� ���� ��� (10������ ���)
            if (rounds % 10 == 0 && isFirst == 0) {
                // ó�� 10�� ���ҿ� �߰� 10�� ���Ҹ� ����մϴ�.
                for (int j = 0; j < 10; j++) {
                    printf("%3d ", array[j]);
                }
                printf("! ");
                for (int j = SIZE / 2 - 1; j < SIZE / 2 + 10; j++) {
                    printf("%3d ", array[j]);
                }
                printf("\n");
            }
            rounds++;  // ���� Ƚ�� ����
        }
    }
}

// ���� �Լ�
int main() {
    int array[SIZE];  // �迭 ����
    srand((unsigned int)time(NULL));  // ���� �õ� ����

    // 20���� �׽�Ʈ�� ����
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // ���� �迭 ����
        comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;  // �̵� Ƚ�� �ʱ�ȭ

        // ù ��° ���� �ø� �պ� ���� ���� �޽��� ���
        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array);  // �պ� ���� ����

            // ��� ���
            printf("Result\n");
            printArray(array, SIZE);  // ���ĵ� �迭 ���
            isFirst++;  // ù ��° ���� ǥ��
        }
        else {
            doMergeSort(array);  // ���� ���࿡���� ���ĸ� ����
        }

        totalComparisons += comparisonCount;  // ��ü �� Ƚ���� �߰�
        totalMoves += moveCount;  // ��ü �̵� Ƚ���� �߰�
    }

    // ��� �� Ƚ���� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;  
}
