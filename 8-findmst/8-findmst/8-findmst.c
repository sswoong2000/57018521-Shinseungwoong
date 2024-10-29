#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // 최대 정점 수를 100으로 설정
#define INF 1000 // 무한대 값 정의 (INF)

// 엣지 구조체: 그래프의 한 엣지 정보를 저장
typedef struct {
    int start, end, weight; // 시작, 끝 정점과 가중치
} Edge;

// 그래프를 나타내는 구조체
typedef struct {
    int n; // 현재 그래프에 포함된 엣지의 개수
    Edge edges[MAX_VERTICES]; // 최대 정점 수만큼 엣지 배열 선언
} GraphType;

// 최소 힙을 나타내는 구조체
typedef struct {
    Edge heap[MAX_VERTICES]; // 최소 힙으로 사용할 엣지 배열
    int size; // 힙에 저장된 엣지 수
} MinHeap;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0; // 엣지 개수를 0으로 초기화
}

// 엣지 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start; // 시작 정점 설정
    g->edges[g->n].end = end; // 끝 정점 설정
    g->edges[g->n].weight = w; // 엣지 가중치 설정
    g->n++; // 엣지 개수 증가
}

// 정해진 엣지로 그래프 생성
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

// 가중치 오름차순으로 정렬을 위한 비교 함수 (QuickSort 사용 시 필요)
int compare(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return x->weight - y->weight; // 가중치를 기준으로 정렬
}

// 집합 표현을 위한 부모 배열
int parent[MAX_VERTICES];

// 집합 초기화 함수
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1; // 모든 정점의 부모를 -1로 초기화 (자기 자신을 부모로 설정)
}

// 집합 찾기 함수 (경로 압축 적용)
int set_find(int curr) {
    if (parent[curr] == -1) // 최상위 부모를 찾은 경우
        return curr;
    return parent[curr] = set_find(parent[curr]); // 경로 압축으로 최상위 부모로 설정
}

// 집합 합치기 함수 (두 집합 병합)
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2; // 하나의 집합으로 합침
}

// QuickSort를 활용한 Kruskal 알고리즘
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; // MST에 포함된 엣지 수
    int uset, vset;

    qsort(g->edges, g->n, sizeof(Edge), compare); // 가중치 기준으로 엣지 정렬

    printf("QuickSort Based Kruskal \n");
    set_init(MAX_VERTICES); // 집합 초기화

    for (int i = 0; i < g->n; i++) {
        uset = set_find(g->edges[i].start); // 시작 정점의 집합 찾기
        vset = set_find(g->edges[i].end); // 끝 정점의 집합 찾기
        if (uset != vset) { // 서로 다른 집합인 경우
            printf("Edge (%d, %d) select (%d)\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight); // 선택된 엣지 출력
            set_union(uset, vset); // 집합 합치기
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1) // 모든 엣지를 선택하면 종료
            break;
    }
}

// MinHeap 초기화 함수
void minHeapInit(MinHeap* h) {
    h->size = 0; // 힙 크기 초기화
}

// MinHeap에 엣지 삽입 함수
void minHeapInsert(MinHeap* h, Edge e) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->heap[parent].weight <= e.weight) // 부모의 가중치가 더 작으면 위치를 찾은 것
            break;
        h->heap[i] = h->heap[parent];
        i = parent;
    }
    h->heap[i] = e;
}

// MinHeap에서 엣지 삭제 (가장 작은 가중치의 엣지 반환)
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

// MinHeap을 활용한 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
    MinHeap heap;
    minHeapInit(&heap);
    int edge_accepted = 0;
    int uset, vset;

    // 모든 엣지를 MinHeap에 삽입
    for (int i = 0; i < g->n; i++) {
        minHeapInsert(&heap, g->edges[i]);
    }

    printf("MinHeap Based Kruskal \n");
    set_init(MAX_VERTICES); // 집합 초기화

    while (heap.size > 0) {
        Edge edge = minHeapDelete(&heap); // 최소 가중치 엣지 추출
        uset = set_find(edge.start); // 시작 정점의 집합 찾기
        vset = set_find(edge.end); // 끝 정점의 집합 찾기
        if (uset != vset) { // 다른 집합인 경우
            printf("Edge (%d, %d) select (%d)\n", edge.start, edge.end, edge.weight); // 선택된 엣지 출력
            set_union(uset, vset); // 집합 합치기
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1) // MST가 완성되면 종료
            break;
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 동적 할당
    graph_init(g); // 그래프 초기화
    GenerateGraph(g); // 그래프 생성
    QuickKruskal(g); // QuickSort 기반 Kruskal 알고리즘 수행
    MinHeapKruskal(g); // MinHeap 기반 Kruskal 알고리즘 수행
    free(g); // 메모리 해제
    return 0;
}
