#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


typedef struct Stack {
    TreeNode* nodes[100];
    int top;
} Stack;

Stack stack;


void initStack() {
    stack.top = -1;
}


int isEmpty() {
    return stack.top == -1;
}


void push(TreeNode* node) {
    stack.nodes[++stack.top] = node;
    printf("push(%d) ", node->data);
}


TreeNode* pop() {
    if (!isEmpty()) {
        TreeNode* node = stack.nodes[stack.top--];
        printf("pop(%d) ", node->data);
        return node;
    }
    return NULL;
}


TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = createNode(data);
    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}


TreeNode* GenerateLinkTree() {
    TreeNode* root = createNode(1);

    PlaceNode(root, 0, 2);    
    PlaceNode(root, 1, 9);   

    PlaceNode(root->left, 0, 3);   
    PlaceNode(root->left, 1, 5);   

    PlaceNode(root->left->right, 0, 7); 
    PlaceNode(root->left->right, 1, 8);  

    PlaceNode(root->left->left, 0, 4);   
    PlaceNode(root->left->left, 1, 6);   

    PlaceNode(root->right, 0, 10);   
    PlaceNode(root->right, 1, 13);   

    PlaceNode(root->right->left, 0, 11); 
    PlaceNode(root->right->left, 1, 12);  

    PlaceNode(root->right->right, 0, 14); 
    PlaceNode(root->right->right, 1, 15); 

    return root;
}


void LinkPreOrder(TreeNode* root) {
    printf("LinkedPreOrder: ");
    initStack();
    if (root == NULL) return;

    push(root);
    while (!isEmpty()) {
        TreeNode* node = pop();
        printf("visit(%d) ", node->data);

        if (node->right) push(node->right);
        if (node->left) push(node->left);
    }
    printf("\n");
}


void LinkInOrder(TreeNode* root) {
    printf("LinkedInOrder: ");
    initStack();
    TreeNode* current = root;

    while (current != NULL || !isEmpty()) {
        while (current != NULL) {
            push(current);
            current = current->left;
        }
        current = pop();
        printf("visit(%d) ", current->data);
        current = current->right;
    }
    printf("\n");
}


void LinkPostOrder(TreeNode* root) {
    printf("LinkedPostOrder: ");
    initStack();
    TreeNode* lastVisited = NULL;
    TreeNode* current = root;

    while (current != NULL || !isEmpty()) {
        if (current != NULL) {
            push(current);
            current = current->left;
        }
        else {
            TreeNode* peekNode = stack.nodes[stack.top];
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                current = peekNode->right;
            }
            else {
                printf("visit(%d) ", peekNode->data);
                lastVisited = pop();
            }
        }
    }
    printf("\n");
}

int main() {
    TreeNode* root = GenerateLinkTree();


    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);

    return 0;
}
