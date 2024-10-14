#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// �ִ� �� ����ü ����
typedef struct {
    int data[MAX_SIZE]; // ���� �����͸� ������ �迭
    int size;          // ���� ���� ũ��
} TreeNode;

// �ִ� �� �ʱ�ȭ �Լ�
void InitMaxHeap(TreeNode* root) {
    root->size = 0; // ���� ũ�⸦ 0���� ����
}

// ���� ������ ����ϴ� �Լ�
void PrintHeap(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]); // ���� �� ��� ���
    }
    printf("\n");
}

// ���� ���� �����ϴ� �Լ�
int InsertMaxHeap(TreeNode* root, int value, int showSteps) {
    // ���� ���� á���� Ȯ��
    if (root->size >= MAX_SIZE) {
        printf("���� ���� á���ϴ�!\n");
        return 0;
    }

    int index = root->size; // ������ ��ġ ����
    root->data[index] = value; // ���� ���� �߰�
    root->size++; // �� ũ�� ����

    int moves = 0; // �̵� Ƚ�� �ʱ�ȭ
    if (showSteps) {
        printf("��� �߰� �� �� ����: ");
        PrintHeap(root); // �߰� �� ���� ���
    }

    // �θ� ���� ���Ͽ� �� �Ӽ� ����
    while (index > 0) {
        int parent = (index - 1) / 2; // �θ� ��� �ε���
        if (root->data[parent] < root->data[index]) {
            // �θ� �ڽĺ��� ������ swap
            int temp = root->data[parent];
            root->data[parent] = root->data[index];
            root->data[index] = temp;
            index = parent; // �ε����� �θ�� ����
            moves++; // �̵� Ƚ�� ����

            if (showSteps) {
                printf("��� �̵� �� �� ����: ");
                PrintHeap(root); // �̵� �� ���� ���
            }
        }
        else {
            break; // �� �Ӽ� ���� �Ϸ�
        }
    }
    if (showSteps) {
        printf("���� �� ����: ");
        PrintHeap(root); // ���� ���� ���
    }

    return moves; // �̵� Ƚ�� ��ȯ
}

// ������ �ִ밪�� �����ϴ� �Լ�
int DeleteMaxHeap(TreeNode* root) {
    // ���� ��� �ִ��� Ȯ��
    if (root->size == 0) {
        printf("���� ����ֽ��ϴ�!\n");
        return 0;
    }

    root->data[0] = root->data[root->size - 1]; // ������ ��Ҹ� ��Ʈ�� �̵�
    root->size--; // �� ũ�� ����

    int index = 0; // ��Ʈ �ε���
    int moves = 0; // �̵� Ƚ�� �ʱ�ȭ
    printf("��� ���� �� �� ����: ");
    PrintHeap(root); // ���� �� ���� ���

    // �ڽİ� ���Ͽ� �� �Ӽ� ����
    while (index * 2 + 1 < root->size) {
        int leftChild = index * 2 + 1; // ���� �ڽ� �ε���
        int rightChild = index * 2 + 2; // ������ �ڽ� �ε���
        int largerChild = leftChild; // ���� �ڽ� ��� �ʱ�ȭ

        // ������ �ڽ��� �� ũ�� largerChild ����
        if (rightChild < root->size && root->data[rightChild] > root->data[leftChild]) {
            largerChild = rightChild;
        }

        // �θ� ��尡 �ڽĺ��� ������ swap
        if (root->data[index] < root->data[largerChild]) {
            int temp = root->data[index];
            root->data[index] = root->data[largerChild];
            root->data[largerChild] = temp;

            index = largerChild; // �ε����� �ڽ����� ����
            moves++; // �̵� Ƚ�� ����

            printf("��� �̵� �� �� ����: ");
            PrintHeap(root); // �̵� �� ���� ���
        }
        else {
            break; // �� �Ӽ� ���� �Ϸ�
        }
    }

    printf("���� �� ����: ");
    PrintHeap(root); // ���� ���� ���

    return moves; // �̵� Ƚ�� ��ȯ
}

// ���� ���� ������ ����ϴ� �Լ�
void PrintHeapLevelOrder(TreeNode* root) {
    if (root->size == 0) {
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }

    int level = 0; // ���� ����
    int count = 1; // ���� ������ ��� ��
    int index = 0; // ���� �ε���

    printf("Ʈ�� ������ ���:\n");
    while (index < root->size) {
        printf("[���� %d] ", level + 1); // ���� ���

        // ���� ������ ��� ���
        for (int i = 0; i < count && index < root->size; i++) {
            printf("%d ", root->data[index]);
            index++;
        }
        printf("\n");

        level++; // ���� ������ �̵�
        count *= 2; // ���� ������ ��� ���� �� ��
    }
}

// ����� �������̽��� ���� �Լ�
void RunUserInterface(TreeNode* root) {
    char choice; // ����� ����
    int value, moves; // �Է� ���� �̵� Ƚ��

    while (1) {
        printf("\n-------------------------------------\n");
        printf(" i : ��� �߰�\n");
        printf(" d : ��� ����\n");
        printf(" p : ������ ���\n");
        printf(" c : ����\n");
        printf("-------------------------------------\n");

        printf("�޴� �Է�: ");
        scanf(" %c", &choice); // ����� �Է�

        switch (choice) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf("%d", &value); // �߰��� �� �Է�
            moves = InsertMaxHeap(root, value, 1); // ���� �� �߰�
            printf("��尡 �߰��Ǿ����ϴ�. ��� �̵� Ƚ��: %d\n", moves);
            break;

        case 'd':
            moves = DeleteMaxHeap(root); // �ִ밪 ����
            printf("�ִ� �������� ��Ʈ ��尡 �����Ǿ����ϴ�. ��� �̵� Ƚ��: %d\n", moves);
            break;

        case 'p':
            PrintHeapLevelOrder(root); // ���� ������ ���
            break;

        case 'c':
            printf("���α׷��� �����մϴ�.\n");
            return; // ���α׷� ����

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n");
        }
    }
}

int main() {
    TreeNode root;  // �ִ� �� ����ü
    InitMaxHeap(&root); // �� �ʱ�ȭ

    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 13 }; // �ʱ� ������
    int size = sizeof(inputData) / sizeof(inputData[0]); // ������ ũ�� ���

    // �ʱ� �����ͷ� �� ����
    for (int i = 0; i < size; i++) {
        InsertMaxHeap(&root, inputData[i], 0); // ���� ������ �߰�
    }

    RunUserInterface(&root); // ����� �������̽� ����

    return 0;
}
