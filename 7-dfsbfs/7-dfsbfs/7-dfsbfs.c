#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 11

int graph[MAX_NODES][MAX_NODES] = {
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0}
};

void depth_first_search(int start, int goal) {
    int stack[MAX_NODES], top = -1;
    int visited[MAX_NODES] = { 0 };
    int visited_count = 0;
    int search_path[MAX_NODES]; // ��� ������ ���� �迭
    int path_index = 0; // ��� �ε���

    stack[++top] = start;

    while (top != -1) {
        int node = stack[top--];

        // ��尡 �̹� �湮�Ǿ����� Ȯ��
        if (visited[node]) {
            continue;
        }

        visited[node] = 1;
        search_path[path_index++] = node; // ��ο� ��� �߰�
        visited_count++;

        // �湮�� ��� ���
        printf("%d ", node);

        // ��ǥ ��忡 ������ ���
        if (node == goal) {
            printf("\nŽ�� ����: %d\n", goal);
            printf("�湮�� ����� ��: %d\n", visited_count);
            return;
        }

        // ���� ��带 ���ÿ� �߰�
        for (int i = MAX_NODES - 1; i >= 0; i--) {
            if (graph[node][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }

        // ��Ʈ��ŷ ��� ���
        if (path_index > 0) {
            path_index--; // ���� ��带 ��ο��� ���� (��Ʈ��ŷ)
        }
    }

    printf("\nŽ�� ����\n");
    printf("�湮�� ����� ��: %d\n", visited_count);
}

void breadth_first_search(int start, int goal) {
    int queue[MAX_NODES], front = -1, rear = -1;
    int visited[MAX_NODES] = { 0 };
    int visited_count = 0;

    queue[++rear] = start;

    while (front < rear) {
        front++;
        int node = queue[front];

        // ��尡 �̹� �湮�Ǿ����� Ȯ��
        if (visited[node]) {
            continue;
        }

        visited[node] = 1;
        visited_count++;
        printf("%d ", node);

        // ��ǥ ��忡 ������ ���
        if (node == goal) {
            printf("\nŽ�� ����: %d\n", goal);
            printf("�湮�� ����� ��: %d\n", visited_count);
            return;
        }

        // ���� ��带 ť�� �߰�
        for (int i = 0; i < MAX_NODES; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                queue[++rear] = i;
            }
        }
    }

    printf("\nŽ�� ����\n");
    printf("�湮�� ����� ��: %d\n", visited_count);
}

int main() {
    while (1) {
        int menu_input;
        printf("\n1: ���� �켱 Ž��\n");
        printf("2: �ʺ� �켱 Ž��\n");
        printf("3: ����\n");
        printf("�޴� �Է�: ");
        scanf_s("%d", &menu_input);

        if (menu_input == 1) {
            int start, goal;
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &goal);
            depth_first_search(start, goal);
        }
        else if (menu_input == 2) {
            int start, goal;
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &goal);
            breadth_first_search(start, goal);
        }
        else if (menu_input == 3) {
            printf("���α׷� ����\n");
            break;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    return 0;
}
