#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��� ����ü ����
// �� ����ü�� ���� Ž�� Ʈ��(BST) �� AVL Ʈ������ ���˴ϴ�.
typedef struct Node {
    int key; // ����� Ű ��
    struct Node* left, * right; // ���� �� ������ �ڽ� ��带 ����Ű�� ������
    int height; // AVL Ʈ������ ����� ���̸� ����
} Node;

int compareCount = 0; // �� ���� Ƚ���� �����ϴ� ���� ����
int searchCount = 0;  // �������� Ž�� Ƚ���� �����ϴ� ���� ����

// ���ο� ��带 �����ϴ� �Լ��Դϴ�.
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // AVL Ʈ�������� ���� ������ ����� �ʱ� ���̸� 1�� �����մϴ�.
    return newNode;
}

// ���� Ž�� Ʈ��(BST)�� ��带 �����ϴ� �Լ��Դϴ�.
Node* insertBST(Node* root, int key) {
    if (root == NULL) // Ʈ���� ��� ������ ���ο� ��带 ��ȯ�մϴ�.
        return createNode(key);
    if (key < root->key) // ������ ���� ���� ����� Ű���� ������ ���� ����Ʈ���� �����մϴ�.
        root->left = insertBST(root->left, key);
    else if (key > root->key) // ������ ���� ���� ����� Ű���� ũ�� ������ ����Ʈ���� �����մϴ�.
        root->right = insertBST(root->right, key);
    return root; // ���� �� ��Ʈ�� ��ȯ�մϴ�.
}

// ���� Ž�� Ʈ��(BST)���� ��带 �����ϴ� �Լ��Դϴ�.
Node* deleteBST(Node* root, int key) {
    if (root == NULL) // ������ ��尡 ������ NULL�� ��ȯ�մϴ�.
        return root;
    if (key < root->key) // ������ ���� ���� ����� Ű���� ������ ���� ����Ʈ������ ������ �õ��մϴ�.
        root->left = deleteBST(root->left, key);
    else if (key > root->key) // ������ ���� ���� ����� Ű���� ũ�� ������ ����Ʈ������ ������ �õ��մϴ�.
        root->right = deleteBST(root->right, key);
    else { // ������ ��带 ã�� ���
        if (root->left == NULL) { // �ڽ��� �ϳ� �Ǵ� ���� ���
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) { // �ڽ��� �ϳ� �Ǵ� ���� ���
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // �ڽ��� �� �� �ִ� ���, ������ ����Ʈ������ ���� ���� ���� ���� ���� ��ü�մϴ�.
        Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->key = temp->key; // ��ü
        root->right = deleteBST(root->right, temp->key); // ��ü�� ��带 ������ ����Ʈ������ ����
    }
    return root; // ��Ʈ�� ��ȯ�մϴ�.
}

// ���� Ž�� Ʈ��(BST)���� ���� Ž���ϴ� �Լ��Դϴ�.
Node* searchBST(Node* root, int key) {
    if (root == NULL) // Ž�� ���� �� NULL�� ��ȯ�մϴ�.
        return NULL;
    compareCount++; // �� ���� Ƚ���� ������ŵ�ϴ�.
    if (key == root->key) // ���� ã���� ���� ��带 ��ȯ�մϴ�.
        return root;
    if (key < root->key) // Ž���� ���� ���� ����� Ű���� ������ ���� ����Ʈ���� Ž���մϴ�.
        return searchBST(root->left, key);
    return searchBST(root->right, key); // �׷��� ������ ������ ����Ʈ���� Ž���մϴ�.
}

// AVL Ʈ���� ��� ���̸� ����ϴ� �Լ��Դϴ�.
int height(Node* root) {
    return root ? root->height : 0; // ��Ʈ�� NULL�� ��� 0�� ��ȯ�մϴ�.
}

// AVL Ʈ������ ���� ����� ����ϴ� �Լ��Դϴ�.
int getBalance(Node* root) {
    return root ? height(root->left) - height(root->right) : 0; // ���ʰ� ������ ����Ʈ�� ������ ���̸� ��ȯ�մϴ�.
}

// AVL Ʈ������ ������ ȸ���� �����ϴ� �Լ��Դϴ�.
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    // ���̸� �����մϴ�.
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    return x; // ���ο� ��Ʈ�� ��ȯ�մϴ�.
}

// AVL Ʈ������ ���� ȸ���� �����ϴ� �Լ��Դϴ�.
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    // ���̸� �����մϴ�.
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    return y; // ���ο� ��Ʈ�� ��ȯ�մϴ�.
}

// AVL Ʈ���� ��带 �����ϴ� �Լ��Դϴ�.
Node* insertAVL(Node* root, int key) {
    if (root == NULL) // Ʈ���� ��� ������ ���ο� ��带 ��ȯ�մϴ�.
        return createNode(key);
    if (key < root->key) // ������ ���� ���� ����� Ű���� ������ ���� ����Ʈ���� �����մϴ�.
        root->left = insertAVL(root->left, key);
    else if (key > root->key) // ������ ���� ���� ����� Ű���� ũ�� ������ ����Ʈ���� �����մϴ�.
        root->right = insertAVL(root->right, key);
    else
        return root; // �ߺ� ������ ������� �ʽ��ϴ�.

    // ����� ���̸� ������Ʈ�մϴ�.
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // ������ Ȯ���ϰ� �ʿ��ϸ� ȸ���� �����մϴ�.
    int balance = getBalance(root);

    // LL ȸ��
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR ȸ��
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR ȸ��
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL ȸ��
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // ��Ʈ�� ��ȯ�մϴ�.
}

// AVL Ʈ������ ��带 �����ϴ� �Լ��Դϴ�.
Node* deleteAVL(Node* root, int key) {
    return deleteBST(root, key); // ���� ������ BST�� �����ϰ� �����Ǿ����ϴ�.
}

// AVL Ʈ������ ���� Ž���ϴ� �Լ��Դϴ�.
Node* searchAVL(Node* root, int key) {
    return searchBST(root, key); // Ž�� ������ BST�� �����մϴ�.
}

// Ʈ�� �޸𸮸� �����ϴ� �Լ��Դϴ�.
void freeTree(Node* root) {
    if (root == NULL) // Ʈ���� ��� ������ ��ȯ�մϴ�.
        return;
    freeTree(root->left); // ���� ����Ʈ���� �����մϴ�.
    freeTree(root->right); // ������ ����Ʈ���� �����մϴ�.
    free(root); // ���� ��带 �����մϴ�.
}

// AVL Ʈ���� ���� 2000���� ��ġ �۾��� �����ϴ� �Լ��Դϴ�.
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // �۾� ������ �����մϴ� (����, ����, Ž��).
        int B = rand() % 1000; // �۾��� ����� ���� �����մϴ�.
        if (A == 0) { // ���� �۾�
            root = insertAVL(root, B);
        }
        else if (A == 1) { // ���� �۾�
            root = deleteAVL(root, B);
        }
        else if (A == 2) { // Ž�� �۾�
            if (searchAVL(root, B) != NULL)
                searchCount++; // ���������� Ž���� Ƚ���� ������ŵ�ϴ�.
        }
    }
}

// ���� Ž�� Ʈ���� ���� 2000���� ��ġ �۾��� �����ϴ� �Լ��Դϴ�.
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // �۾� ������ �����մϴ� (����, ����, Ž��).
        int B = rand() % 1000; // �۾��� ����� ���� �����մϴ�.
        if (A == 0) { // ���� �۾�
            root = insertBST(root, B);
        }
        else if (A == 1) { // ���� �۾�
            root = deleteBST(root, B);
        }
        else if (A == 2) { // Ž�� �۾�
            if (searchBST(root, B) != NULL)
                searchCount++; // ���������� Ž���� Ƚ���� ������ŵ�ϴ�.
        }
    }
}

// ���α׷��� ���� �Լ��Դϴ�.
int main(int argc, char* argv[]) {
    Node* root = NULL; // ��Ʈ ��带 �ʱ�ȭ�մϴ�.
    srand(time(NULL)); // ���� �õ� ���� �����մϴ�.
    float allCount = 0.0;

    // AVL Ʈ���� ���� 2000ȸ ��ġ �۾��� �����մϴ�.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount; // ��� �� Ƚ���� ����մϴ�.
    printf("average AVL compare count: %.2f\n", allCount);

    // Ʈ���� �����մϴ�.
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // ���� Ž�� Ʈ���� ���� 2000ȸ ��ġ �۾��� �����մϴ�.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount; // ��� �� Ƚ���� ����մϴ�.
    printf("average Bin compare count: %.2f\n", allCount);

    // Ʈ���� �����մϴ�.
    freeTree(root);
    return 0; // ���α׷��� �����մϴ�.
}
