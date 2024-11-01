#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// �׷��� ����ü ����: ������ ����(n)�� ���� ����ġ(weight) �迭�� ����
typedef struct GraphType {
    int n;  // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];  // ������ ����ġ ���� ���
} GraphType;

// Prim �˰��� �ʿ��� ���� �迭 ����
int selected[MAX_VERTICES];  // ������ �ּ� ���� Ʈ���� ���ԵǾ����� ����
int distance[MAX_VERTICES];  // �� ���������� �ּ� �Ÿ�

// Prim �˰��򿡼� ���õ��� ���� ���� �� �ּ� �Ÿ��� ������ ã�� �Լ�
int FindPrimMST(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        // ���õ��� ���� ���� �� �ּ� �Ÿ� ���� ã��
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

// �׷��� �ʱ�ȭ �Լ�: ���� ������ 0���� �����ϰ� ����ġ�� �Ÿ� �迭�� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->n = 0;  // ���� ���� �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;  // �ʱ� ����ġ�� ���Ѵ�� ����
        }
        selected[i] = FALSE;  // ��� ������ ���õ��� ���� ���·� �ʱ�ȭ
        distance[i] = INF;  // ��� ���������� �Ÿ��� ���Ѵ�� �ʱ�ȭ
    }
}

// Prim �˰����� ����Ͽ� �ּ� ���� Ʈ���� �����ϴ� �Լ�
void prim(GraphType* g, int s) {
    int u, v;

    // �ʱ� �Ÿ� �迭 ����
    for (u = 0; u < g->n; u++)
        distance[u] = INF;  // ��� ���������� �Ÿ��� ���Ѵ�� ����
    distance[s] = 0;  // ���� ������ �Ÿ��� 0���� ����

    printf("Prim MST Algorithm\n");

    // ��� ������ ������� �ݺ�
    for (int i = 0; i < g->n; i++) {
        u = FindPrimMST(g->n);  // �ּ� �Ÿ� ���� ã��
        if (u == -1 || distance[u] == INF) return;  // ��� ������ ���õǾ��ų� ������� ������ ����

        selected[u] = TRUE;  // ������ ������ �ּ� ���� Ʈ���� ����
        printf("���� %d �߰�\n", u + 1);  // ���õ� ���� ��� (1���� �����ϵ��� ǥ��)

        // ���õ� ������ ������ ��� ������ �˻��Ͽ� �ּ� �Ÿ� ����
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];  // �ּ� �Ÿ� ����
            }
        }
    }
}

// �׷����� ���� ����ġ�� �ʱ�ȭ�ϴ� �Լ�
void GenerateGraph(GraphType* g) {
    g->n = 10;  // �׷����� ���� ������ 10���� ����

    // ���� ���� ����ġ ����
    int weights[10][10] = {
        // 1    2    3    4    5    6    7    8    9    10
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF }, // 1
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF }, // 2
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF }, // 3
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 }, // 4
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 }, // 5
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF }, // 6
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF }, // 7
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 }, // 8
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 }, // 9
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }  // 10
    };

    // ����ġ �迭�� �׷����� ����ġ ��Ŀ� ����
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

// ���α׷��� ������
int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));  // �׷��� ����ü�� ���� �Ҵ�
    graph_init(g);  // �׷��� �ʱ�ȭ

    GenerateGraph(g);  // �׷����� ����ġ�� ����

    prim(g, 0);  // Prim �˰��� ����, ���� ������ 0 (���� 1�� �ش�)

    free(g);  // �׷��� ����ü�� �޸𸮸� ����
    return 0;
}
