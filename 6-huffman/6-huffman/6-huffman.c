#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    char character;          // 노드가 저장하는 문자
    int frequency;          // 해당 문자의 빈도수
    struct Node* left;      // 왼쪽 자식 노드
    struct Node* right;     // 오른쪽 자식 노드
} Node;

// 우선순위 큐에서 사용할 구조체
typedef struct MinHeap {
    int size;               // 현재 힙의 크기
    int capacity;           // 힙의 최대 용량
    Node** array;          // 노드 포인터 배열
} MinHeap;

// 노드 생성 함수
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 메모리 할당
    newNode->character = character;               // 문자 초기화
    newNode->frequency = frequency;               // 빈도수 초기화
    newNode->left = newNode->right = NULL;       // 자식 노드 초기화
    return newNode;
}

// 최소 힙 생성 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // 메모리 할당
    minHeap->size = 0;                                  // 힙의 초기 크기
    minHeap->capacity = capacity;                        // 최대 용량 설정
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*)); // 노드 포인터 배열 초기화
    return minHeap;
}

// 최소 힙 재정렬 함수
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;                                 // 가장 작은 노드 인덱스
    int left = 2 * idx + 1;                            // 왼쪽 자식 인덱스
    int right = 2 * idx + 2;                           // 오른쪽 자식 인덱스

    // 왼쪽 자식과 비교하여 더 작은 노드 인덱스를 찾음
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    // 오른쪽 자식과 비교하여 더 작은 노드 인덱스를 찾음
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    // 현재 인덱스가 가장 작은 인덱스가 아니면, 스왑 후 재귀 호출
    if (smallest != idx) {
        Node* temp = minHeap->array[smallest];
        minHeap->array[smallest] = minHeap->array[idx];
        minHeap->array[idx] = temp;
        minHeapify(minHeap, smallest);
    }
}

// 힙에 노드 추가 함수
void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->array[minHeap->size] = node; // 노드 추가
    minHeap->size++;                       // 힙 크기 증가

    // 힙 상태 정렬
    for (int i = (minHeap->size / 2) - 1; i >= 0; i--) {
        minHeapify(minHeap, i); // 모든 부모 노드를 재정렬
    }

    // 현재 힙 상태 출력
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->frequency); // 빈도수 출력
    }
    printf("\n");
}

// 최소 힙에서 최솟값 제거 함수
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];              // 최솟값 노드 저장
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; // 마지막 노드로 루트 대체
    minHeap->size--;                             // 힙 크기 감소
    minHeapify(minHeap, 0);                      // 힙 재정렬
    return temp;                                 // 최솟값 노드 반환
}

// 허프만 트리 생성 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap(size); // 최소 힙 생성

    // 모든 문자를 힙에 추가하고 그때마다 출력
    for (int i = 0; i < size; i++) {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i])); // 각 문자와 빈도수로 노드 생성 후 추가
    }

    // 힙에서 두 개의 노드를 추출하여 새 노드를 만들고 힙에 추가
    while (minHeap->size > 1) {
        Node* left = extractMin(minHeap);     // 최솟값 노드 추출 (왼쪽 자식)
        Node* right = extractMin(minHeap);    // 다음 최솟값 노드 추출 (오른쪽 자식)
        Node* newNode = createNode('\0', left->frequency + right->frequency); // 새로운 내부 노드 생성
        newNode->left = left;                  // 왼쪽 자식 설정
        newNode->right = right;                // 오른쪽 자식 설정

        // 중간 과정 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, newNode->frequency);

        // 힙에 새로 생성된 노드 추가
        insertMinHeap(minHeap, newNode);
    }

    return extractMin(minHeap); // 최종 루트 노드 반환
}

// 허프만 코드 출력 함수
void printCodes(Node* root, int arr[], int top) {
    // 왼쪽 자식 노드인 경우
    if (root->left) {
        arr[top] = 1;  // 왼쪽 자식에 1 할당
        printCodes(root->left, arr, top + 1);
    }

    // 오른쪽 자식 노드인 경우
    if (root->right) {
        arr[top] = 0;  // 오른쪽 자식에 0 할당
        printCodes(root->right, arr, top + 1);
    }

    // 리프 노드인 경우
    if (!root->left && !root->right) {
        printf("%c: ", root->character); // 리프 노드의 문자 출력
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]); // 코드 출력
        }
        printf("\n");
    }
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size); // 허프만 트리 생성
    int arr[100]; // 배열 크기
    int top = 0;  // 현재 깊이
    printCodes(root, arr, top); // 허프만 코드 출력
}

// 메인 함수
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' }; // 문자 배열
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };          // 빈도수 배열
    int size = sizeof(characters) / sizeof(characters[0]);   // 배열 크기 계산
    GenerateHuffmanCodes(characters, frequencies, size);      // 허프만 코드 생성
    return 0;
}
