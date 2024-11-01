#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// 그래프 구조체 정의: 정점의 개수(n)와 간선 가중치(weight) 배열을 포함
typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];  // 간선의 가중치 인접 행렬
} GraphType;

// Prim 알고리즘에 필요한 전역 배열 선언
int selected[MAX_VERTICES];  // 정점이 최소 신장 트리에 포함되었는지 여부
int distance[MAX_VERTICES];  // 각 정점까지의 최소 거리

// Prim 알고리즘에서 선택되지 않은 정점 중 최소 거리의 정점을 찾는 함수
int FindPrimMST(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        // 선택되지 않은 정점 중 최소 거리 정점 찾기
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

// 그래프 초기화 함수: 정점 개수를 0으로 설정하고 가중치와 거리 배열을 초기화
void graph_init(GraphType* g) {
    g->n = 0;  // 정점 개수 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;  // 초기 가중치를 무한대로 설정
        }
        selected[i] = FALSE;  // 모든 정점을 선택되지 않은 상태로 초기화
        distance[i] = INF;  // 모든 정점까지의 거리를 무한대로 초기화
    }
}

// Prim 알고리즘을 사용하여 최소 신장 트리를 생성하는 함수
void prim(GraphType* g, int s) {
    int u, v;

    // 초기 거리 배열 설정
    for (u = 0; u < g->n; u++)
        distance[u] = INF;  // 모든 정점까지의 거리를 무한대로 설정
    distance[s] = 0;  // 시작 정점의 거리를 0으로 설정

    printf("Prim MST Algorithm\n");

    // 모든 정점을 대상으로 반복
    for (int i = 0; i < g->n; i++) {
        u = FindPrimMST(g->n);  // 최소 거리 정점 찾기
        if (u == -1 || distance[u] == INF) return;  // 모든 정점이 선택되었거나 연결되지 않으면 종료

        selected[u] = TRUE;  // 선택한 정점을 최소 신장 트리에 포함
        printf("정점 %d 추가\n", u + 1);  // 선택된 정점 출력 (1부터 시작하도록 표시)

        // 선택된 정점과 인접한 모든 정점을 검사하여 최소 거리 갱신
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];  // 최소 거리 갱신
            }
        }
    }
}

// 그래프의 간선 가중치를 초기화하는 함수
void GenerateGraph(GraphType* g) {
    g->n = 10;  // 그래프의 정점 개수를 10으로 설정

    // 정점 간의 가중치 정의
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

    // 가중치 배열을 그래프의 가중치 행렬에 복사
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

// 프로그램의 진입점
int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));  // 그래프 구조체를 동적 할당
    graph_init(g);  // 그래프 초기화

    GenerateGraph(g);  // 그래프에 가중치를 설정

    prim(g, 0);  // Prim 알고리즘 실행, 시작 정점은 0 (정점 1에 해당)

    free(g);  // 그래프 구조체의 메모리를 해제
    return 0;
}
