#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // �ִ� ���� ���� 100���� ����
#define INF 1000 // ���Ѵ� �� ���� (INF)

// ���� ����ü: �׷����� �� ���� ������ ����
typedef struct {
    int start, end, weight; // ����, �� ������ ����ġ
} Edge;

// �׷����� ��Ÿ���� ����ü
typedef struct {
    int n; // ���� �׷����� ���Ե� ������ ����
    Edge edges[MAX_VERTICES]; // �ִ� ���� ����ŭ ���� �迭 ����
} GraphType;

// �ּ� ���� ��Ÿ���� ����ü
typedef struct {
    Edge heap[MAX_VERTICES]; // �ּ� ������ ����� ���� �迭
    int size; // ���� ����� ���� ��
} MinHeap;

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    g->n = 0; // ���� ������ 0���� �ʱ�ȭ
}

// ���� �߰� �Լ�
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start; // ���� ���� ����
    g->edges[g->n].end = end; // �� ���� ����
    g->edges[g->n].weight = w; // ���� ����ġ ����
    g->n++; // ���� ���� ����
}

// ������ ������ �׷��� ����
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 2, 7, 8);
}

// ����ġ ������������ ������ ���� �� �Լ� (QuickSort ��� �� �ʿ�)
int compare(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return x->weight - y->weight; // ����ġ�� �������� ����
}

// ���� ǥ���� ���� �θ� �迭
int parent[MAX_VERTICES];

// ���� �ʱ�ȭ �Լ�
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1; // ��� ������ �θ� -1�� �ʱ�ȭ (�ڱ� �ڽ��� �θ�� ����)
}

// ���� ã�� �Լ� (��� ���� ����)
int set_find(int curr) {
    if (parent[curr] == -1) // �ֻ��� �θ� ã�� ���
        return curr;
    return parent[curr] = set_find(parent[curr]); // ��� �������� �ֻ��� �θ�� ����
}

// ���� ��ġ�� �Լ� (�� ���� ����)
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2; // �ϳ��� �������� ��ħ
}

// QuickSort�� Ȱ���� Kruskal �˰���
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; // MST�� ���Ե� ���� ��
    int uset, vset;

    qsort(g->edges, g->n, sizeof(Edge), compare); // ����ġ �������� ���� ����

    printf("QuickSort Based Kruskal \n");
    set_init(MAX_VERTICES); // ���� �ʱ�ȭ

    for (int i = 0; i < g->n; i++) {
        uset = set_find(g->edges[i].start); // ���� ������ ���� ã��
        vset = set_find(g->edges[i].end); // �� ������ ���� ã��
        if (uset != vset) { // ���� �ٸ� ������ ���
            printf("Edge (%d, %d) select (%d)\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight); // ���õ� ���� ���
            set_union(uset, vset); // ���� ��ġ��
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1) // ��� ������ �����ϸ� ����
            break;
    }
}

// MinHeap �ʱ�ȭ �Լ�
void minHeapInit(MinHeap* h) {
    h->size = 0; // �� ũ�� �ʱ�ȭ
}

// MinHeap�� ���� ���� �Լ�
void minHeapInsert(MinHeap* h, Edge e) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->heap[parent].weight <= e.weight) // �θ��� ����ġ�� �� ������ ��ġ�� ã�� ��
            break;
        h->heap[i] = h->heap[parent];
        i = parent;
    }
    h->heap[i] = e;
}

// MinHeap���� ���� ���� (���� ���� ����ġ�� ���� ��ȯ)
Edge minHeapDelete(MinHeap* h) {
    Edge minEdge = h->heap[0];
    Edge lastEdge = h->heap[--h->size];

    int parent = 0;
    int child = 1;
    while (child < h->size) {
        if (child + 1 < h->size && h->heap[child + 1].weight < h->heap[child].weight)
            child++;
        if (lastEdge.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    h->heap[parent] = lastEdge;
    return minEdge;
}

// MinHeap�� Ȱ���� Kruskal �˰���
void MinHeapKruskal(GraphType* g) {
    MinHeap heap;
    minHeapInit(&heap);
    int edge_accepted = 0;
    int uset, vset;

    // ��� ������ MinHeap�� ����
    for (int i = 0; i < g->n; i++) {
        minHeapInsert(&heap, g->edges[i]);
    }

    printf("MinHeap Based Kruskal \n");
    set_init(MAX_VERTICES); // ���� �ʱ�ȭ

    while (heap.size > 0) {
        Edge edge = minHeapDelete(&heap); // �ּ� ����ġ ���� ����
        uset = set_find(edge.start); // ���� ������ ���� ã��
        vset = set_find(edge.end); // �� ������ ���� ã��
        if (uset != vset) { // �ٸ� ������ ���
            printf("Edge (%d, %d) select (%d)\n", edge.start, edge.end, edge.weight); // ���õ� ���� ���
            set_union(uset, vset); // ���� ��ġ��
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1) // MST�� �ϼ��Ǹ� ����
            break;
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType)); // �׷��� ���� �Ҵ�
    graph_init(g); // �׷��� �ʱ�ȭ
    GenerateGraph(g); // �׷��� ����
    QuickKruskal(g); // QuickSort ��� Kruskal �˰��� ����
    MinHeapKruskal(g); // MinHeap ��� Kruskal �˰��� ����
    free(g); // �޸� ����
    return 0;
}
