#include <iostream>

using namespace std;

#define endl '\n'
#define MAX_N 101
#define INF 987654321

int N, ans;
int MAP[MAX_N][MAX_N];
int Visited[MAX_N][MAX_N];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

bool MapOut(int r, int c) {
    return (r < 0 || N <= r || c < 0 || N <= c);
}

void dfs(int r, int c, int tmpMax, int tmpMin) {
    if (ans < tmpMax - tmpMin) return;
    int val = MAP[r][c];
    if (r == N - 1 && c == N - 1) {
        ans = max(tmpMax, val) - min(tmpMin, val);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (MapOut(nr, nc) || Visited[nr][nc] == 1) continue;
        Visited[nr][nc] = 1;
        dfs(nr, nc, max(tmpMax, val), min(tmpMin, val));
        Visited[nr][nc] = 0;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
        }
    }
    ans = INF;
    Visited[0][0] = 1;
    dfs(0, 0, MAP[0][0], MAP[0][0]);
    cout << ans << endl;

    return 0;
}