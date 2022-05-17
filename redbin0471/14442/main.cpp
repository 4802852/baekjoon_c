#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX_N 1001
#define MAX_K 11
#define INF 987654321

struct INFO {
    int r;
    int c;
    int cnt;
};

int N, M, K;
char MAP[MAX_N][MAX_N];
int visited[MAX_N][MAX_N][MAX_K];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

bool OutMap(int r, int c) {
    return (r < 0 || N <= r || c < 0 || M <= c);
}

int bfs() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k <= K; k++) {
                visited[i][j][k] = INF;
            }
        }
    }
    queue<INFO> Q;
    Q.push({0, 0, 0});
    visited[0][0][0] = 1;
    while (!Q.empty()) {
        int r = Q.front().r;
        int c = Q.front().c;
        int cnt = Q.front().cnt;
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (OutMap(nr, nc)) continue;
            if (MAP[nr][nc] == '0' && visited[r][c][cnt] + 1 < visited[nr][nc][cnt]) {
                visited[nr][nc][cnt] = visited[r][c][cnt] + 1;
                Q.push({nr, nc, cnt});
            } else if (MAP[nr][nc] == '1' && visited[r][c][cnt] + 1 < visited[nr][nc][cnt + 1] && cnt < K) {
                visited[nr][nc][cnt + 1] = visited[r][c][cnt] + 1;
                Q.push({nr, nc, cnt + 1});
            }
        }
    }
    int max = INF;
    for (int i = 0; i <= K; i++) {
        if (visited[N - 1][M - 1][i] < max) {
            max = visited[N - 1][M - 1][i];
        }
    }
    if (max == INF) {
        return -1;
    } else {
        return max;
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