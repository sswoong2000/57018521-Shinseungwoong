#include <stdio.h>
#include <limits.h>

#define V 10  // ������ ����
#define INF INT_MAX  // ���Ѵ� ���� ��Ÿ���� ���� ���

// �׷��� ����ü ����
typedef struct {
    int n;         // ������ ����
    int weight[V][V]; // ������ ����ġ ���
} GraphType;

// �׷��� �ʱ�ȭ �Լ�
void GenerateGraph(GraphType* g) {
    g->n = 10;  // �׷����� ���� ������ 10���� ����

    // ���� ���� ����ġ ����
    int weights[10][10] = {
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF }, // 1�� ������ ����ġ
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF }, // 2�� ������ ����ġ
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF }, // 3�� ������ ����ġ
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 }, // 4�� ������ ����ġ
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 }, // 5�� ������ ����ġ
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF }, // 6�� ������ ����ġ
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF }, // 7�� ������ ����ġ
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 }, // 8�� ������ ����ġ
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 }, // 9�� ������ ����ġ
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }  // 10�� ������ ����ġ
    };

    // ����ġ �迭�� �׷����� ����ġ ��Ŀ� ����
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

// ���ͽ�Ʈ�� �˰��� ����
void dijkstra(GraphType* g, int start) {
    int distance[V];  // �� ���������� �ִ� �Ÿ��� ����
    int visited[V];   // �ش� ������ �̹� ó���Ǿ����� Ȯ��
    int found_order[V];  // �湮 ������ ������ �迭
    int found_index = 0;  // �湮 ���� �ε���

    // �ʱ�ȭ: ��� ���������� �Ÿ� �� �湮 ���θ� �ʱ�ȭ
    for (int i = 0; i < V; i++) {
        distance[i] = INF;  // �� ���������� �Ÿ��� ���Ѵ�� �ʱ�ȭ
        visited[i] = 0;     // ���� �湮���� ������ ǥ��
        found_order[i] = -1; // �湮 ���� �ʱ�ȭ
    }

    distance[start] = 0;  // ���� ������ �Ÿ��� 0���� ����

    // �ʱ� ���� ���
    printf("distance:  ");
    for (int i = 0; i < V; i++) {
        if (distance[i] == INF) {
            printf("* ");
        }
        else {
            printf("%2d ", distance[i]);
        }
    }
    printf("\n");

    printf("found:     ");
    for (int i = 0; i < V; i++) {
        if (i == start) {
            printf("1 ");  // ���� ���� �湮�� ���·� ���
        }
        else {
            printf("0 ");  // ������ ���� �湮���� ���� ���·� ���
        }
    }
    printf("\n\n");

    // ���ͽ�Ʈ�� �˰����� ���� ����
    for (int step = 0; step < V; step++) {  // ��� ������ ó���� ������ �ݺ�
        // �湮���� ���� ���� �� �ִ� �Ÿ��� ���� ������ ã��
        int min = INF, u = -1;
        for (int j = 0; j < V; j++) {
            if (!visited[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }

        // ���� ����� ������ �� �̻� ���� ��� �ݺ��� ����
        if (u == -1) {
            break;
        }

        // ���� u�� �湮�ߴٰ� ǥ��
        visited[u] = 1;
        found_order[found_index++] = u + 1;  // �湮 ������ �ش� ������ �߰�

        // u�� ���� ���� v�� �Ÿ��� ������Ʈ
        for (int v = 0; v < V; v++) {
            // v�� �湮���� �ʾҰ�, u���� v���� ��ΰ� �����ϸ�, �Ÿ��� �� ª�� ��� ������Ʈ
            if (!visited[v] && g->weight[u][v] != INF && distance[u] != INF
                && distance[u] + g->weight[u][v] < distance[v]) {
                distance[v] = distance[u] + g->weight[u][v];
            }
        }

        // ���� �Ÿ� ���� ���
        printf("distance:  ");
        for (int i = 0; i < V; i++) {
            if (distance[i] == INF) {
                printf("* ");
            }
            else {
                printf("%2d ", distance[i]);
            }
        }
        printf("\n");

        // ���� �湮 ���� ���
        printf("found:     ");
        for (int i = 0; i < V; i++) {
            printf("%d ", visited[i]);
        }
        printf("\n\n");
    }

    // �湮 ���� ���
    printf("Found Order: ");
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main() {
    // �׷��� �ʱ�ȭ
    GraphType g;
    GenerateGraph(&g);

    // ���� ������ 1�� (�ε��� 0)���� �����Ͽ� ���ͽ�Ʈ�� ����
    dijkstra(&g, 0);

    return 0;
}
