#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {

    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n\n");
}

void ArrayPreOrder(int* tree, int index, int size) {
    if (index < size) {
        printf("%d ", tree[index]);
        ArrayPreOrder(tree, 2 * index + 1, size);
        ArrayPreOrder(tree, 2 * index + 2, size);
    }
}

void ArrayInOrder(int* tree, int index, int size) {
    if (index < size) {
        ArrayInOrder(tree, 2 * index + 1, size);
        printf("%d ", tree[index]);
        ArrayInOrder(tree, 2 * index + 2, size);
    }
}

void ArrayPostOrder(int* tree, int index, int size) {
    if (index < size) {
        ArrayPostOrder(tree, 2 * index + 1, size);
        ArrayPostOrder(tree, 2 * index + 2, size);
        printf("%d ", tree[index]);
    }
}

void ArrayOrders(int* tree) {
    printf("");
    ArrayPreOrder(tree, 0, 15);
    printf("\n");
    ArrayInOrder(tree, 0, 15);
    printf("\n");
    ArrayPostOrder(tree, 0, 15);
    printf("\n\n");
}

TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void GenerateLinkTree(TreeNode** root) {
    *root = CreateNode(1);
    (*root)->left = CreateNode(2);
    (*root)->right = CreateNode(9);
    (*root)->left->left = CreateNode(3);
    (*root)->left->right = CreateNode(5);
    (*root)->right->left = CreateNode(10);
    (*root)->right->right = CreateNode(13);
    (*root)->left->left->left = CreateNode(4);
    (*root)->left->left->right = CreateNode(6);
    (*root)->left->right->left = CreateNode(7);
    (*root)->left->right->right = CreateNode(8);
    (*root)->right->left->left = CreateNode(11);
    (*root)->right->left->right = CreateNode(12);
    (*root)->right->right->left = CreateNode(14);
    (*root)->right->right->right = CreateNode(15);
}

void LinkPreOrder(TreeNode* node) {
    if (node) {
        printf("%d ", node->data);
        LinkPreOrder(node->left);
        LinkPreOrder(node->right);
    }
}

void LinkInOrder(TreeNode* node) {
    if (node) {
        LinkInOrder(node->left);
        printf("%d ", node->data);
        LinkInOrder(node->right);
    }
}

void LinkPostOrder(TreeNode* node) {
    if (node) {
        LinkPostOrder(node->left);
        LinkPostOrder(node->right);
        printf("%d ", node->data);
    }
}

void LinkOrders(TreeNode* root) {
    printf("");
    LinkPreOrder(root);
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];
    TreeNode* root = NULL;

    GenerateArrayTree(arr);
    GenerateLinkTree(&root);

    ArrayOrders(arr);
    LinkOrders(root);

    return 0;
}
