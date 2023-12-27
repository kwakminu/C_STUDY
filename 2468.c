#include<stdio.h>
#define SZ 101
 
int N;
int map[SZ][SZ];
int copied_map[SZ][SZ];
int ans = 0;
int max_rain = 0;
 
int vectX[4] = { 0, 0, 1, -1 };
int vectY[4] = { 1, -1, 0, 0 };
 
void do_dfs(int i, int j){
    copied_map[i][j] = 0;
    int nextX; int nextY;
    for (int k = 0; k < 4; k++) {
        nextX = i + vectX[k];
        nextY = j + vectY[k];
        if (nextX >= 0 && nextY >= 0 && nextX < N && nextY < N) {
            if (copied_map[nextX][nextY] != 0) {
                do_dfs(nextX, nextY);
            }
        }
    }
}
 
void solution() {
 
    for (int k = 0 ; k <= max_rain; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                copied_map[i][j] = map[i][j];
                if (copied_map[i][j] <= k) {
                    copied_map[i][j] = 0;
                }
            }
        }
        int safetyzone_cnt = 0;
 
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (copied_map[i][j] != 0) {
                    safetyzone_cnt++;
                    do_dfs(i, j);
                }
            }
        }
 
        if (ans < safetyzone_cnt) {
            ans = safetyzone_cnt;
        }
    }
}
 
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %d", &map[i][j]);
            if (max_rain < map[i][j]) {
                max_rain = map[i][j];
            }
 
        }
    }
    solution();
    printf("%d", ans);
}