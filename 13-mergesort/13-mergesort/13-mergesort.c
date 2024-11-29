#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // 배열의 크기를 100으로 설정

int rounds = 0;  // mergeSort의 실행 횟수를 기록하는 변수
int comparisonCount = 0;  // 비교 횟수를 기록하는 변수
int moveCount = 0;  // 데이터 이동 횟수를 기록하는 변수
int totalComparisons = 0;  // 전체 비교 횟수의 총합
int totalMoves = 0;  // 전체 이동 횟수의 총합
int isFirst = 0;  // 첫 번째 실행 여부를 체크하는 변수

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    // SIZE 크기만큼 랜덤 값을 생성하여 배열에 저장합니다.
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0-999 범위의 랜덤 값
    }
}

// 배열 출력 함수
void printArray(int array[], int size) {
    // 배열의 모든 원소를 출력합니다.
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 반복적 합병 정렬 함수
void doMergeSort(int array[]) {
    int temp[SIZE];  // 임시 배열 생성

    // 합병 정렬에서의 '폭'을 1부터 시작하여, 폭이 2배씩 증가하면서 반복합니다.
    for (int width = 1; width < SIZE; width *= 2) {
        // 배열을 '폭' 크기만큼 나누어 두 개의 부분 배열을 병합합니다.
        for (int i = 0; i < SIZE; i += 2 * width) {
            int left = i;  // 왼쪽 부분 배열의 시작 인덱스
            int mid = i + width < SIZE ? i + width : SIZE;  // 가운데 인덱스 (중간 값)
            int right = i + 2 * width < SIZE ? i + 2 * width : SIZE;  // 오른쪽 부분 배열의 끝 인덱스

            int l = left, r = mid, k = left;  // 왼쪽, 오른쪽, 임시 배열의 인덱스

            // 두 배열을 병합하는 과정
            while (l < mid && r < right) {
                comparisonCount++;  // 비교 횟수 증가
                if (array[l] <= array[r]) {
                    temp[k++] = array[l++];  // 왼쪽 배열의 값을 임시 배열에 넣고 왼쪽 인덱스 증가
                    moveCount++;  // 이동 횟수 증가
                }
                else {
                    temp[k++] = array[r++];  // 오른쪽 배열의 값을 임시 배열에 넣고 오른쪽 인덱스 증가
                    moveCount++;  // 이동 횟수 증가
                }
            }

            // 왼쪽 배열에 남은 원소를 임시 배열에 복사
            while (l < mid) {
                temp[k++] = array[l++];
                moveCount++;  // 이동 횟수 증가
            }

            // 오른쪽 배열에 남은 원소를 임시 배열에 복사
            while (r < right) {
                temp[k++] = array[r++];
                moveCount++;  // 이동 횟수 증가
            }

            // 임시 배열에서 원본 배열로 값 복사
            for (int j = left; j < right; j++) {
                array[j] = temp[j];
                moveCount++;  // 이동 횟수 증가
            }

            // 중간 상태 출력 (10번마다 출력)
            if (rounds % 10 == 0 && isFirst == 0) {
                // 처음 10개 원소와 중간 10개 원소를 출력합니다.
                for (int j = 0; j < 10; j++) {
                    printf("%3d ", array[j]);
                }
                printf("! ");
                for (int j = SIZE / 2 - 1; j < SIZE / 2 + 10; j++) {
                    printf("%3d ", array[j]);
                }
                printf("\n");
            }
            rounds++;  // 실행 횟수 증가
        }
    }
}

// 메인 함수
int main() {
    int array[SIZE];  // 배열 선언
    srand((unsigned int)time(NULL));  // 랜덤 시드 설정

    // 20번의 테스트를 실행
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // 랜덤 배열 생성
        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;  // 이동 횟수 초기화

        // 첫 번째 실행 시만 합병 정렬 시작 메시지 출력
        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array);  // 합병 정렬 실행

            // 결과 출력
            printf("Result\n");
            printArray(array, SIZE);  // 정렬된 배열 출력
            isFirst++;  // 첫 번째 실행 표시
        }
        else {
            doMergeSort(array);  // 이후 실행에서는 정렬만 실행
        }

        totalComparisons += comparisonCount;  // 전체 비교 횟수에 추가
        totalMoves += moveCount;  // 전체 이동 횟수에 추가
    }

    // 평균 비교 횟수와 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;  
}
