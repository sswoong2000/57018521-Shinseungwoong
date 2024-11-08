#include <stdio.h>
#include <limits.h>

#define V 10  // 정점의 개수
#define INF INT_MAX  // 무한대 값을 나타내기 위한 상수

// 그래프 구조체 정의
typedef struct {
    int n;         // 정점의 개수
    int weight[V][V]; // 간선의 가중치 행렬
} GraphType;

// 그래프 초기화 함수
void GenerateGraph(GraphType* g) {
    g->n = 10;  // 그래프의 정점 개수를 10으로 설정

    // 정점 간의 가중치 정의
    int weights[10][10] = {
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF }, // 1번 정점의 가중치
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF }, // 2번 정점의 가중치
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF }, // 3번 정점의 가중치
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 }, // 4번 정점의 가중치
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 }, // 5번 정점의 가중치
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF }, // 6번 정점의 가중치
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF }, // 7번 정점의 가중치
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 }, // 8번 정점의 가중치
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 }, // 9번 정점의 가중치
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }  // 10번 정점의 가중치
    };

    // 가중치 배열을 그래프의 가중치 행렬에 복사
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

// 다익스트라 알고리즘 구현
void dijkstra(GraphType* g, int start) {
    int distance[V];  // 각 정점까지의 최단 거리를 저장
    int visited[V];   // 해당 정점이 이미 처리되었는지 확인
    int found_order[V];  // 방문 순서를 저장할 배열
    int found_index = 0;  // 방문 순서 인덱스

    // 초기화: 모든 정점까지의 거리 및 방문 여부를 초기화
    for (int i = 0; i < V; i++) {
        distance[i] = INF;  // 각 정점까지의 거리를 무한대로 초기화
        visited[i] = 0;     // 아직 방문하지 않음을 표시
        found_order[i] = -1; // 방문 순서 초기화
    }

    distance[start] = 0;  // 시작 정점의 거리를 0으로 설정

    // 초기 상태 출력
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
            printf("1 ");  // 시작 노드는 방문한 상태로 출력
        }
        else {
            printf("0 ");  // 나머지 노드는 방문하지 않은 상태로 출력
        }
    }
    printf("\n\n");

    // 다익스트라 알고리즘의 메인 루프
    for (int step = 0; step < V; step++) {  // 모든 정점을 처리할 때까지 반복
        // 방문하지 않은 정점 중 최단 거리를 가진 정점을 찾음
        int min = INF, u = -1;
        for (int j = 0; j < V; j++) {
            if (!visited[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }

        // 만약 연결된 정점이 더 이상 없을 경우 반복문 종료
        if (u == -1) {
            break;
        }

        // 정점 u를 방문했다고 표시
        visited[u] = 1;
        found_order[found_index++] = u + 1;  // 방문 순서에 해당 정점을 추가

        // u의 인접 정점 v의 거리를 업데이트
        for (int v = 0; v < V; v++) {
            // v가 방문되지 않았고, u에서 v로의 경로가 존재하며, 거리가 더 짧은 경우 업데이트
            if (!visited[v] && g->weight[u][v] != INF && distance[u] != INF
                && distance[u] + g->weight[u][v] < distance[v]) {
                distance[v] = distance[u] + g->weight[u][v];
            }
        }

        // 현재 거리 상태 출력
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

        // 현재 방문 여부 출력
        printf("found:     ");
        for (int i = 0; i < V; i++) {
            printf("%d ", visited[i]);
        }
        printf("\n\n");
    }

    // 방문 순서 출력
    printf("Found Order: ");
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main() {
    // 그래프 초기화
    GraphType g;
    GenerateGraph(&g);

    // 시작 정점을 1번 (인덱스 0)으로 설정하여 다익스트라 실행
    dijkstra(&g, 0);

    return 0;
}
