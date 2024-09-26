#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


TreeNode* root = NULL;


TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = CreateNode(data);
    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}


void GenerateLinkTree(TreeNode* node) {
    PlaceNode(node, 0, 2);
    PlaceNode(node, 1, 9);
    PlaceNode(node->left, 0, 3);
    PlaceNode(node->left, 1, 5);
    PlaceNode(node->right, 0, 10);
    PlaceNode(node->right, 1, 13);
    PlaceNode(node->left->left, 0, 4);
    PlaceNode(node->left->left, 1, 6);
    PlaceNode(node->left->right, 0, 7);
    PlaceNode(node->left->right, 1, 8);
    PlaceNode(node->right->left, 0, 11);
    PlaceNode(node->right->left, 1, 12);
    PlaceNode(node->right->right, 0, 14);
    PlaceNode(node->right->right, 1, 15);
}


int GetSumOfNodes(TreeNode* node) {
    if (node == NULL) return 0;

    int sum = 0;
    TreeNode* stack[100];
    int top = -1;

    stack[++top] = node;
    while (top >= 0) {
        TreeNode* current = stack[top--];
        sum += current->data;

        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }
    return sum;
}

int GetNumberOfNodes(TreeNode* node) {
    if (node == NULL) return 0;

    int count = 0;
    TreeNode* stack[100];
    int top = -1;

    stack[++top] = node;
    while (top >= 0) {
        TreeNode* current = stack[top--];
        count++;

        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }
    return count;
}


int GetHeightOfTree(TreeNode* node) {
    if (node == NULL) return 0;

    int height = 0;
    TreeNode* stack[100];
    int level[100];
    int top = -1;

    stack[++top] = node;
    level[top] = 1;

    while (top >= 0) {
        TreeNode* current = stack[top--];
        int currentLevel = level[top + 1];

        if (current->right) {
            stack[++top] = current->right;
            level[top] = currentLevel + 1;
        }
        if (current->left) {
            stack[++top] = current->left;
            level[top] = currentLevel + 1;
        }

        if (top == -1 || (top >= 0 && level[top + 1] > height)) {
            height = currentLevel;
        }
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    return height;      
}


int GetNumberOfLeafNodes(TreeNode* node) {
    if (node == NULL) return 0;

    int leafCount = 0;
    TreeNode* stack[100];
    int top = -1;

    stack[++top] = node;
    while (top >= 0) {
        TreeNode* current = stack[top--];


        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }
    return leafCount;
}


int main() {
    root = CreateNode(1);
    GenerateLinkTree(root);

    printf("Sum of nodes: %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumberOfNodes(root));
    printf("Height of Tree: %d\n", GetHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root));

    return 0;
}
