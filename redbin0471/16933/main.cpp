#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define endl '\n'
#define MAX_N 1001
#define MAX_K 11
#define INF 10000000

struct INFO {
    int r;
    int c;
    int night;
    int cnt;
};

int N, M, K;
char MAP[MAX_N][MAX_N];
int visited[MAX_N][MAX_N][MAX_K][2];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int MinVal(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

bool OutMap(int r, int c) {
    return (r < 0 || N <= r || c < 0 || M <= c);
}

int bfs() {
    // visited 배열을 INF로 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k <= K; k++) {
                visited[i][j][k][0] = INF;
                visited[i][j][k][1] = INF;
            }
        }
    }
    queue<INFO> Q;
    // {r, c, night, cnt} 정보 추가
    Q.push({0, 0, 0, 0});
    visited[0][0][0][0] = 1;
    while (!Q.empty()) {
        int r = Q.front().r;
        int c = Q.front().c;
        int night = Q.front().night;
        int cnt = Q.front().cnt;
        Q.pop();
        // 상하좌우 4방향으로 이동할 때
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (OutMap(nr, nc)) continue;
            if (MAP[nr][nc] == '0' && visited[r][c][cnt][night] + 1 < visited[nr][nc][cnt][1 - night]) {
                // 벽이 없을 경우, 다음 위치의 visited 값이 현재 위치 값 + 1 보다 클 경우 이동 가능
                visited[nr][nc][cnt][1 - night] = visited[r][c][cnt][night] + 1;
                Q.push({nr, nc, 1 - night, cnt});
            } else if (MAP[nr][nc] == '1' && night == 0 && cnt < K && visited[r][c][cnt][night] + 1 < visited[nr][nc][cnt + 1][1 - night]) {
                // 벽이 있을 경우, 다음 위치의 visited 값이 현재 위치 값 + 1 보다 크고, 낮인 상태이고, 벽을 부순 횟수가 충분할 경우 이동 가능
                visited[nr][nc][cnt + 1][1 - night] = visited[r][c][cnt][night] + 1;
                Q.push({nr, nc, 1 - night, cnt + 1});
            }
        }
        // 현재 위치에 가만히 있을 경우
        if (visited[r][c][cnt][night] + 1 < visited[r][c][cnt][1 - night]) {
            visited[r][c][cnt][1 - night] = visited[r][c][cnt][night] + 1;
            Q.push({r, c, 1 - night, cnt});
        }
    }
    // (N - 1, M - 1) 에 도달할 수 있는 모든 경우 비교
    int ans = INF;
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j < 2; j++) {
            ans = MinVal(ans, visited[N - 1][M - 1][i][j]);
        }
    }
    if (ans == INF) {
        return -1;
    } else {
        return ans;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
        }
    }
    cout << bfs() << endl;

    return 0;
}