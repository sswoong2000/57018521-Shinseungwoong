#include <stdio.h>

// �� ������ ���� ���� �ٲٴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �־��� �迭�� i��° ��带 ��Ʈ�� �ϴ� �ִ� ���� ����� �Լ�
void heapify(int inputData[], int n, int i) {
    int largest = i;  // ���� ��Ʈ
    int left = 2 * i + 1;  // ���� �ڽ� �ε���
    int right = 2 * i + 2; // ������ �ڽ� �ε���

    // ���� �ڽ��� ���� ���� ū ������ ũ�� largest ������Ʈ
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // ������ �ڽ��� ���� ���� ū ������ ũ�� largest ������Ʈ
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // largest�� ��Ʈ�� �ƴ϶�� swap�ϰ� ��������� heapify
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        heapify(inputData, n, largest);
    }
}

// �־��� �迭�κ��� �ִ� ���� �����ϴ� �Լ�
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        int currentIndex = i;

        // �θ�� ���Ͽ� �ִ� ���� �����ϵ��� ������
        while (currentIndex > 0) {
            int parentIndex = (currentIndex - 1) / 2;
            if (inputData[currentIndex] > inputData[parentIndex]) {
                swap(&inputData[currentIndex], &inputData[parentIndex]);
                currentIndex = parentIndex;
            }
            else {
                break; // �� �̻� ��ȯ�� �ʿ� ����
            }
        }

        // �߰� ���� ���
        for (int j = 0; j <= i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n"); // �� ���� ���
    }
}

// �ִ� ���� �����ϰ� �� ������ �����ϴ� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    // �ִ� �� ����
    BuildMaxHeap(inputData, n);

    // �� ���� ����
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);  // �ִ밪(��Ʈ)�� �迭 ������ �̵�
        heapify(inputData, i, 0);  // ������ �� ������

        // �� ���� ���
        for (int j = 0; j <= i - 1; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n"); // �� ���� ���
    }
}

int main() {
    // ������ ������ �迭
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // �迭�� ũ�� ���

    // �� ���� ����
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // ���ĵ� ��� ���
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0; // ���α׷� ����
}
