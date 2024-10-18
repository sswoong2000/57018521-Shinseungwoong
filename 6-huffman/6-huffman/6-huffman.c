#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    char character;          // ��尡 �����ϴ� ����
    int frequency;          // �ش� ������ �󵵼�
    struct Node* left;      // ���� �ڽ� ���
    struct Node* right;     // ������ �ڽ� ���
} Node;

// �켱���� ť���� ����� ����ü
typedef struct MinHeap {
    int size;               // ���� ���� ũ��
    int capacity;           // ���� �ִ� �뷮
    Node** array;          // ��� ������ �迭
} MinHeap;

// ��� ���� �Լ�
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // �޸� �Ҵ�
    newNode->character = character;               // ���� �ʱ�ȭ
    newNode->frequency = frequency;               // �󵵼� �ʱ�ȭ
    newNode->left = newNode->right = NULL;       // �ڽ� ��� �ʱ�ȭ
    return newNode;
}

// �ּ� �� ���� �Լ�
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // �޸� �Ҵ�
    minHeap->size = 0;                                  // ���� �ʱ� ũ��
    minHeap->capacity = capacity;                        // �ִ� �뷮 ����
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*)); // ��� ������ �迭 �ʱ�ȭ
    return minHeap;
}

// �ּ� �� ������ �Լ�
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;                                 // ���� ���� ��� �ε���
    int left = 2 * idx + 1;                            // ���� �ڽ� �ε���
    int right = 2 * idx + 2;                           // ������ �ڽ� �ε���

    // ���� �ڽİ� ���Ͽ� �� ���� ��� �ε����� ã��
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    // ������ �ڽİ� ���Ͽ� �� ���� ��� �ε����� ã��
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    // ���� �ε����� ���� ���� �ε����� �ƴϸ�, ���� �� ��� ȣ��
    if (smallest != idx) {
        Node* temp = minHeap->array[smallest];
        minHeap->array[smallest] = minHeap->array[idx];
        minHeap->array[idx] = temp;
        minHeapify(minHeap, smallest);
    }
}

// ���� ��� �߰� �Լ�
void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->array[minHeap->size] = node; // ��� �߰�
    minHeap->size++;                       // �� ũ�� ����

    // �� ���� ����
    for (int i = (minHeap->size / 2) - 1; i >= 0; i--) {
        minHeapify(minHeap, i); // ��� �θ� ��带 ������
    }

    // ���� �� ���� ���
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->frequency); // �󵵼� ���
    }
    printf("\n");
}

// �ּ� ������ �ּڰ� ���� �Լ�
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];              // �ּڰ� ��� ����
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; // ������ ���� ��Ʈ ��ü
    minHeap->size--;                             // �� ũ�� ����
    minHeapify(minHeap, 0);                      // �� ������
    return temp;                                 // �ּڰ� ��� ��ȯ
}

// ������ Ʈ�� ���� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap(size); // �ּ� �� ����

    // ��� ���ڸ� ���� �߰��ϰ� �׶����� ���
    for (int i = 0; i < size; i++) {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i])); // �� ���ڿ� �󵵼��� ��� ���� �� �߰�
    }

    // ������ �� ���� ��带 �����Ͽ� �� ��带 ����� ���� �߰�
    while (minHeap->size > 1) {
        Node* left = extractMin(minHeap);     // �ּڰ� ��� ���� (���� �ڽ�)
        Node* right = extractMin(minHeap);    // ���� �ּڰ� ��� ���� (������ �ڽ�)
        Node* newNode = createNode('\0', left->frequency + right->frequency); // ���ο� ���� ��� ����
        newNode->left = left;                  // ���� �ڽ� ����
        newNode->right = right;                // ������ �ڽ� ����

        // �߰� ���� ���
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, newNode->frequency);

        // ���� ���� ������ ��� �߰�
        insertMinHeap(minHeap, newNode);
    }

    return extractMin(minHeap); // ���� ��Ʈ ��� ��ȯ
}

// ������ �ڵ� ��� �Լ�
void printCodes(Node* root, int arr[], int top) {
    // ���� �ڽ� ����� ���
    if (root->left) {
        arr[top] = 1;  // ���� �ڽĿ� 1 �Ҵ�
        printCodes(root->left, arr, top + 1);
    }

    // ������ �ڽ� ����� ���
    if (root->right) {
        arr[top] = 0;  // ������ �ڽĿ� 0 �Ҵ�
        printCodes(root->right, arr, top + 1);
    }

    // ���� ����� ���
    if (!root->left && !root->right) {
        printf("%c: ", root->character); // ���� ����� ���� ���
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]); // �ڵ� ���
        }
        printf("\n");
    }
}

// ������ �ڵ� ���� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size); // ������ Ʈ�� ����
    int arr[100]; // �迭 ũ��
    int top = 0;  // ���� ����
    printCodes(root, arr, top); // ������ �ڵ� ���
}

// ���� �Լ�
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' }; // ���� �迭
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };          // �󵵼� �迭
    int size = sizeof(characters) / sizeof(characters[0]);   // �迭 ũ�� ���
    GenerateHuffmanCodes(characters, frequencies, size);      // ������ �ڵ� ����
    return 0;
}
