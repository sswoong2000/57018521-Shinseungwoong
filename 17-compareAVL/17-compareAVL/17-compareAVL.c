#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 노드 구조체 정의
// 이 구조체는 이진 탐색 트리(BST) 및 AVL 트리에서 사용됩니다.
typedef struct Node {
    int key; // 노드의 키 값
    struct Node* left, * right; // 왼쪽 및 오른쪽 자식 노드를 가리키는 포인터
    int height; // AVL 트리에서 노드의 높이를 저장
} Node;

int compareCount = 0; // 비교 연산 횟수를 저장하는 전역 변수
int searchCount = 0;  // 성공적인 탐색 횟수를 저장하는 전역 변수

// 새로운 노드를 생성하는 함수입니다.
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // AVL 트리에서는 새로 생성된 노드의 초기 높이를 1로 설정합니다.
    return newNode;
}

// 이진 탐색 트리(BST)에 노드를 삽입하는 함수입니다.
Node* insertBST(Node* root, int key) {
    if (root == NULL) // 트리가 비어 있으면 새로운 노드를 반환합니다.
        return createNode(key);
    if (key < root->key) // 삽입할 값이 현재 노드의 키보다 작으면 왼쪽 서브트리에 삽입합니다.
        root->left = insertBST(root->left, key);
    else if (key > root->key) // 삽입할 값이 현재 노드의 키보다 크면 오른쪽 서브트리에 삽입합니다.
        root->right = insertBST(root->right, key);
    return root; // 삽입 후 루트를 반환합니다.
}

// 이진 탐색 트리(BST)에서 노드를 삭제하는 함수입니다.
Node* deleteBST(Node* root, int key) {
    if (root == NULL) // 삭제할 노드가 없으면 NULL을 반환합니다.
        return root;
    if (key < root->key) // 삭제할 값이 현재 노드의 키보다 작으면 왼쪽 서브트리에서 삭제를 시도합니다.
        root->left = deleteBST(root->left, key);
    else if (key > root->key) // 삭제할 값이 현재 노드의 키보다 크면 오른쪽 서브트리에서 삭제를 시도합니다.
        root->right = deleteBST(root->right, key);
    else { // 삭제할 노드를 찾은 경우
        if (root->left == NULL) { // 자식이 하나 또는 없는 경우
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) { // 자식이 하나 또는 없는 경우
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // 자식이 두 개 있는 경우, 오른쪽 서브트리에서 가장 작은 값을 가진 노드로 대체합니다.
        Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->key = temp->key; // 대체
        root->right = deleteBST(root->right, temp->key); // 대체한 노드를 오른쪽 서브트리에서 삭제
    }
    return root; // 루트를 반환합니다.
}

// 이진 탐색 트리(BST)에서 값을 탐색하는 함수입니다.
Node* searchBST(Node* root, int key) {
    if (root == NULL) // 탐색 실패 시 NULL을 반환합니다.
        return NULL;
    compareCount++; // 비교 연산 횟수를 증가시킵니다.
    if (key == root->key) // 값을 찾으면 현재 노드를 반환합니다.
        return root;
    if (key < root->key) // 탐색할 값이 현재 노드의 키보다 작으면 왼쪽 서브트리를 탐색합니다.
        return searchBST(root->left, key);
    return searchBST(root->right, key); // 그렇지 않으면 오른쪽 서브트리를 탐색합니다.
}

// AVL 트리의 노드 높이를 계산하는 함수입니다.
int height(Node* root) {
    return root ? root->height : 0; // 루트가 NULL인 경우 0을 반환합니다.
}

// AVL 트리에서 균형 계수를 계산하는 함수입니다.
int getBalance(Node* root) {
    return root ? height(root->left) - height(root->right) : 0; // 왼쪽과 오른쪽 서브트리 높이의 차이를 반환합니다.
}

// AVL 트리에서 오른쪽 회전을 수행하는 함수입니다.
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    // 높이를 재계산합니다.
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    return x; // 새로운 루트를 반환합니다.
}

// AVL 트리에서 왼쪽 회전을 수행하는 함수입니다.
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    // 높이를 재계산합니다.
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    return y; // 새로운 루트를 반환합니다.
}

// AVL 트리에 노드를 삽입하는 함수입니다.
Node* insertAVL(Node* root, int key) {
    if (root == NULL) // 트리가 비어 있으면 새로운 노드를 반환합니다.
        return createNode(key);
    if (key < root->key) // 삽입할 값이 현재 노드의 키보다 작으면 왼쪽 서브트리에 삽입합니다.
        root->left = insertAVL(root->left, key);
    else if (key > root->key) // 삽입할 값이 현재 노드의 키보다 크면 오른쪽 서브트리에 삽입합니다.
        root->right = insertAVL(root->right, key);
    else
        return root; // 중복 삽입은 허용하지 않습니다.

    // 노드의 높이를 업데이트합니다.
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // 균형을 확인하고 필요하면 회전을 수행합니다.
    int balance = getBalance(root);

    // LL 회전
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR 회전
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR 회전
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL 회전
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // 루트를 반환합니다.
}

// AVL 트리에서 노드를 삭제하는 함수입니다.
Node* deleteAVL(Node* root, int key) {
    return deleteBST(root, key); // 삭제 로직은 BST와 동일하게 구현되었습니다.
}

// AVL 트리에서 값을 탐색하는 함수입니다.
Node* searchAVL(Node* root, int key) {
    return searchBST(root, key); // 탐색 로직은 BST와 동일합니다.
}

// 트리 메모리를 해제하는 함수입니다.
void freeTree(Node* root) {
    if (root == NULL) // 트리가 비어 있으면 반환합니다.
        return;
    freeTree(root->left); // 왼쪽 서브트리를 해제합니다.
    freeTree(root->right); // 오른쪽 서브트리를 해제합니다.
    free(root); // 현재 노드를 해제합니다.
}

// AVL 트리에 대해 2000번의 배치 작업을 수행하는 함수입니다.
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // 작업 유형을 결정합니다 (삽입, 삭제, 탐색).
        int B = rand() % 1000; // 작업에 사용할 값을 생성합니다.
        if (A == 0) { // 삽입 작업
            root = insertAVL(root, B);
        }
        else if (A == 1) { // 삭제 작업
            root = deleteAVL(root, B);
        }
        else if (A == 2) { // 탐색 작업
            if (searchAVL(root, B) != NULL)
                searchCount++; // 성공적으로 탐색한 횟수를 증가시킵니다.
        }
    }
}

// 이진 탐색 트리에 대해 2000번의 배치 작업을 수행하는 함수입니다.
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // 작업 유형을 결정합니다 (삽입, 삭제, 탐색).
        int B = rand() % 1000; // 작업에 사용할 값을 생성합니다.
        if (A == 0) { // 삽입 작업
            root = insertBST(root, B);
        }
        else if (A == 1) { // 삭제 작업
            root = deleteBST(root, B);
        }
        else if (A == 2) { // 탐색 작업
            if (searchBST(root, B) != NULL)
                searchCount++; // 성공적으로 탐색한 횟수를 증가시킵니다.
        }
    }
}

// 프로그램의 메인 함수입니다.
int main(int argc, char* argv[]) {
    Node* root = NULL; // 루트 노드를 초기화합니다.
    srand(time(NULL)); // 랜덤 시드 값을 설정합니다.
    float allCount = 0.0;

    // AVL 트리에 대한 2000회 배치 작업을 수행합니다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수를 계산합니다.
    printf("average AVL compare count: %.2f\n", allCount);

    // 트리를 해제합니다.
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // 이진 탐색 트리에 대한 2000회 배치 작업을 수행합니다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수를 계산합니다.
    printf("average Bin compare count: %.2f\n", allCount);

    // 트리를 해제합니다.
    freeTree(root);
    return 0; // 프로그램을 종료합니다.
}
