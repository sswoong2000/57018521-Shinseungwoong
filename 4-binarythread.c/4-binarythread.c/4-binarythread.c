#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int isThreaded;
} ThreadNode;

TreeNode* insertBST(TreeNode* root, int data) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    }
    else {
        root->right = insertBST(root->right, data);
    }
    return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insertBST(root, inputData[i]);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* createThreadNode(int data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

ThreadNode* insertThreaded(ThreadNode* root, int data) {
    if (root == NULL) {
        return createThreadNode(data);
    }
    if (data < root->data) {
        root->left = insertThreaded(root->left, data);
    }
    else {
        root->right = insertThreaded(root->right, data);
    }
    return root;
}

void convertToThreaded(TreeNode* root, ThreadNode** troot, ThreadNode** prev) {
    if (root == NULL) return;

    convertToThreaded(root->left, troot, prev);

    ThreadNode* newNode = createThreadNode(root->data);
    if (*prev) {
        if ((*prev)->right == NULL) {
            (*prev)->right = newNode;
            (*prev)->isThreaded = 1;
        }
    }
    else {
        *troot = newNode;
    }
    *prev = newNode;

    convertToThreaded(root->right, troot, prev);
}

ThreadNode* GenerateThreadTree(TreeNode* root) {
    ThreadNode* troot = NULL;
    ThreadNode* prev = NULL;
    convertToThreaded(root, &troot, &prev);
    return troot;
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;
    while (current) {
        while (current->left) {
            current = current->left;
        }
        printf("%d ", current->data);
        if (current->isThreaded) {
            current = current->right;
        }
        else {
            current = current->right;
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);
    return 0;
}