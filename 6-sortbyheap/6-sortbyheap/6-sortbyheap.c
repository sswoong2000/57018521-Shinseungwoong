#include <stdio.h>

// 두 정수의 값을 서로 바꾸는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 주어진 배열의 i번째 노드를 루트로 하는 최대 힙을 만드는 함수
void heapify(int inputData[], int n, int i) {
    int largest = i;  // 현재 루트
    int left = 2 * i + 1;  // 왼쪽 자식 인덱스
    int right = 2 * i + 2; // 오른쪽 자식 인덱스

    // 왼쪽 자식이 현재 가장 큰 값보다 크면 largest 업데이트
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식이 현재 가장 큰 값보다 크면 largest 업데이트
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // largest가 루트가 아니라면 swap하고 재귀적으로 heapify
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        heapify(inputData, n, largest);
    }
}

// 주어진 배열로부터 최대 힙을 생성하는 함수
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        int currentIndex = i;

        // 부모와 비교하여 최대 힙을 유지하도록 재정렬
        while (currentIndex > 0) {
            int parentIndex = (currentIndex - 1) / 2;
            if (inputData[currentIndex] > inputData[parentIndex]) {
                swap(&inputData[currentIndex], &inputData[parentIndex]);
                currentIndex = parentIndex;
            }
            else {
                break; // 더 이상 교환할 필요 없음
            }
        }

        // 중간 과정 출력
        for (int j = 0; j <= i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n"); // 힙 상태 출력
    }
}

// 최대 힙을 생성하고 힙 정렬을 수행하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 최대 힙 생성
    BuildMaxHeap(inputData, n);

    // 힙 정렬 과정
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);  // 최대값(루트)을 배열 끝으로 이동
        heapify(inputData, i, 0);  // 나머지 힙 재정렬

        // 힙 상태 출력
        for (int j = 0; j <= i - 1; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n"); // 힙 상태 출력
    }
}

int main() {
    // 정렬할 데이터 배열
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // 배열의 크기 계산

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0; // 프로그램 종료
}
