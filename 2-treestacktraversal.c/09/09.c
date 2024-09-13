#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


typedef struct Stack {
    TreeNode* data;
    struct Stack* next;
} Stack;


Stack* createStack() {
    return NULL;
}

int isEmpty(Stack* stack) {
    return stack == NULL;
}

void push(Stack** stack, TreeNode* node) {
    Stack* new_node = (Stack*)malloc(sizeof(Stack));
    new_node->data = node;
    new_node->next = *stack;
    *stack = new_node;
    printf("push(%d) ", node->data);
}

TreeNode* pop(Stack** stack) {
    if (isEmpty(*stack)) return NULL;
    Stack* temp = *stack;
    TreeNode* node = temp->data;
    *stack = (*stack)->next;
    free(temp);
    printf("pop(%d) ", node->data);
    return node;
}


void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {  
        node->left = newNode;
    }
    else {  
        node->right = newNode;
    }
}


void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);  
    PlaceNode(root, 1, 5);  

    PlaceNode(root->left, 0, 3);  
    PlaceNode(root->left, 1, 6);  

    PlaceNode(root->right, 0, 7);  
    PlaceNode(root->right, 1, 8);   

    PlaceNode(root->left->left, 0, 4); 
}


void LinkPreOrder(TreeNode* root) {
    Stack* stack = createStack();
    TreeNode* current = root;

    printf("\n LinkedPreOrder: ");
    push(&stack, current);

    while (!isEmpty(stack)) {
        current = pop(&stack);
        printf("visit(%d) ", current->data);

        if (current->right) {
            push(&stack, current->right);
        }
        if (current->left) {
            push(&stack, current->left);
        }
    }
    printf("\n");
}


void LinkInOrder(TreeNode* root) {
    Stack* stack = createStack();
    TreeNode* current = root;

    printf("\n LinkedInOrder: ");
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("visit(%d) ", current->data);
        current = current->right;
    }
    printf("\n");
}


void LinkPostOrder(TreeNode* root) {
    Stack* s1 = createStack();
    Stack* s2 = createStack();
    TreeNode* current = root;

    printf("\n LinkedPostOrder: ");
    push(&s1, current);

    while (!isEmpty(s1)) {
        current = pop(&s1);
        push(&s2, current);

        if (current->left) {
            push(&s1, current->left);
        }
        if (current->right) {
            push(&s1, current->right);
        }
    }

    while (!isEmpty(s2)) {
        current = pop(&s2);
        printf("visit(%d) ", current->data);
    }
    printf("\n");
}


void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);  // 전위 순회 호출
    LinkInOrder(root);   // 중위 순회 호출
    LinkPostOrder(root); // 후위 순회 호출
}


int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;


    GenerateLinkTree(root);

    
    LinkOrders(root);

    return 0;
}
